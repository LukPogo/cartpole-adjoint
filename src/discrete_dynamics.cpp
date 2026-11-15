#include "discrete_dynamics.hpp"

Vector33d F_vector(const Vector33d &z, const Vector33d &zi,
                   const double &force_value, const double &h,
                   const ModelParameters &params, const ModelGeometry &geom) {
    Vector33d F;
    F.setZero();
    // z1 = qi+1, z2 = vi+1, z3 = ai+1, z4 = lami+1
    auto z1 = z.segment<9>(0);
    auto z2 = z.segment<9>(9);
    auto z3 = z.segment<9>(18);
    auto z4 = z.segment<6>(27);

    auto z1i = zi.segment<9>(0);
    auto z2i = zi.segment<9>(9);

    auto mass = mass_matrix(params);
    auto jacobian = jacobian_matrix(z1, geom);
    auto grav_force = gravitational_forces(params);
    auto appl_force = external_force(force_value);
    auto forces = grav_force + appl_force;
    F.segment<9>(0) = mass * z3 + jacobian.transpose() * z4 - forces;
    F.segment<6>(9) = phi_constraint_vector(z1, geom);
    F.segment<9>(15) = z1 - z1i - h * z2;
    F.segment<9>(24) = z2 - z2i - h * z3;

    return F;
}

Matrix33d Fz_matrix(const Vector33d &z, const double &h,
                    const ModelParameters &params, const ModelGeometry &geom) {
    Matrix33d Fz;
    Fz.setZero();

    auto z1 = z.segment<9>(0);
    auto z4 = z.segment<6>(27);

    auto fiz1Tz4z1 = jacobian_lambda_q(z1, z4, geom);
    auto mass = mass_matrix(params);
    auto jacobian = jacobian_matrix(z1, geom);
    Matrix9d I9;
    I9.setIdentity();

    // F1 row
    Fz.block<9, 9>(0, 0) = fiz1Tz4z1;
    Fz.block<9, 9>(0, 18) = mass;
    Fz.block<9, 6>(0, 27) = jacobian.transpose();

    // F2 row
    Fz.block<6, 9>(9, 0) = jacobian;

    // F3 row
    Fz.block<9, 9>(15, 0) = I9;
    Fz.block<9, 9>(15, 9) = -h * I9;

    // F4 row
    Fz.block<9, 9>(24, 9) = I9;
    Fz.block<9, 9>(24, 18) = -h * I9;

    return Fz;
}

Vector33d newton_rhapson(const Vector33d &zi, const double &force_value,
                         const double &h, const ModelParameters &params,
                         const ModelGeometry &geom) {

    Vector33d dz, z;
    dz.setZero();
    z = zi; // initial guess equal to last iteration
    const int max_iter = 100;
    const double eps = 1e-6; // Lesser than constraint error

    auto Fz = Fz_matrix(z, h, params, geom);
    auto F = F_vector(z, zi, force_value, h, params, geom);

    for (int i = 0; i < max_iter; i++) {
        Fz = Fz_matrix(z, h, params, geom);
        F = F_vector(z, zi, force_value, h, params, geom);
        dz = Fz.partialPivLu().solve(-F);
        z += dz;
        if (dz.norm() < eps && F.norm() < eps)
            break;
    }

    return z;
}

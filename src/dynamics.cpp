#include "dynamics.hpp"

// File containing continuous dynamics solution in absolute coords, that is:
// - mass matrix
// - Jacobian matrix
// - gamma vector
// - gravitational forces
// - external forces
// - (fi_q^T lambda)_q

Eigen::Matrix<double, 9, 9> mass_matrix(const ModelParameters &params) {
    Eigen::Vector<double, 9> diagonal;
    diagonal << params.m1, params.m1, params.J1, params.m2, params.m2,
        params.J2, params.m3, params.m3, params.J3;
    return diagonal.asDiagonal();
}

Eigen::Matrix<double, 6, 9>
jacobian_matrix(const Eigen::Vector<double, 9> &q_vector,
                const ModelGeometry &geom) {

    Eigen::Vector2d r0 = Eigen::Vector2d::Zero();
    double fi0 = 0;
    auto r1 = q_vector.segment<2>(0);
    double fi1 = q_vector(2);
    // auto r2 = q_vector.segment<2>(3);
    double fi2 = q_vector(5);
    // auto r3 = q_vector.segment<2>(6);
    double fi3 = q_vector(8);

    const Eigen::Vector2d &n1 = geom.n_1;
    const Eigen::Vector2d &sA0 = geom.s_A0;
    const Eigen::Vector2d &sA1 = geom.s_A1;
    const Eigen::Vector2d &sA2 = geom.s_A2;
    const Eigen::Vector2d &sB2 = geom.s_B2;
    const Eigen::Vector2d &sB3 = geom.s_B3;

    Eigen::Matrix2d Omega = omega_matrix();
    Eigen::Matrix2d R0 = rotation_matrix(fi0);
    Eigen::Matrix2d R1 = rotation_matrix(fi1);
    Eigen::Matrix2d R2 = rotation_matrix(fi2);
    Eigen::Matrix2d R3 = rotation_matrix(fi3);

    Eigen::RowVector2d a1 = -(R1 * n1).transpose();

    Eigen::Matrix<double, 6, 9> fiq;
    fiq.setZero();

    const Eigen::Matrix2d I = Eigen::Matrix2d::Identity();

    // Translation joint 0 - 1
    fiq.block<1, 3>(0, 0) << -a1, a1 * Omega * (r1 - r0 - R0 * sA0);
    fiq(1, 2) = -1;

    // Revolute joint 1 - 2
    fiq.block<2, 2>(2, 0) = I;
    fiq.block<2, 1>(2, 2) = Omega * R1 * sA1;
    fiq.block<2, 2>(2, 3) = -I;
    fiq.block<2, 1>(2, 5) = -Omega * R2 * sA2;

    // Revolute joint 2 - 3
    fiq.block<2, 2>(4, 3) = I;
    fiq.block<2, 1>(4, 5) = Omega * R2 * sB2;
    fiq.block<2, 2>(4, 6) = -I;
    fiq.block<2, 1>(4, 8) = -Omega * R3 * sB3;

    return fiq;
}

Eigen::Vector<double, 6>
phi_constraint_vector(const Eigen::Vector<double, 9> &q_vector,
                      const ModelGeometry &geom) {
    const Eigen::Vector2d r0 = Eigen::Vector2d::Zero();
    const auto &r1 = q_vector.segment<2>(0);
    const auto &r2 = q_vector.segment<2>(3);
    const auto &r3 = q_vector.segment<2>(6);

    const double fi0 = 0;
    const double &fi1 = q_vector(2);
    const double &fi2 = q_vector(5);
    const double &fi3 = q_vector(8);

    const auto &n1 = geom.n_1;
    const auto &sA0 = geom.s_A0;
    const auto &sA1 = geom.s_A1;
    const auto &sA2 = geom.s_A2;
    const auto &sB2 = geom.s_B2;
    const auto &sB3 = geom.s_B3;

    const auto &R0 = rotation_matrix(fi0);
    const auto &R1 = rotation_matrix(fi1);
    const auto &R2 = rotation_matrix(fi2);
    const auto &R3 = rotation_matrix(fi3);

    Eigen::Vector<double, 6> Fi;
    Fi(0) = (R1 * n1).dot(r1 + R1 * sA1 - r0 - R0 * sA0);
    Fi(1) = fi0 - fi1;
    Fi.segment<2>(2) = r1 + R1 * sA1 - r2 - R2 * sA2;
    Fi.segment<2>(4) = r2 + R2 * sB2 - r3 - R3 * sB3;

    return Fi;
}

Eigen::Vector<double, 6> gamma_vector(const Eigen::Vector<double, 9> &qd_vector,
                                      const Eigen::Vector<double, 9> &q_vector,
                                      const ModelGeometry &geom) {
    double fi2d = qd_vector(5);
    double fi3d = qd_vector(8);

    double fi2 = q_vector(5);
    double fi3 = q_vector(8);

    const auto &sA2 = geom.s_A2;
    const auto &sB2 = geom.s_B2;
    const auto &sB3 = geom.s_B3;

    Eigen::Vector<double, 6> gamma;
    gamma.setZero();

    Eigen::Matrix2d R2 = rotation_matrix(fi2);
    Eigen::Matrix2d R3 = rotation_matrix(fi3);

    gamma.segment<2>(2) = -fi2d * fi2d * R2 * sA2;
    gamma.segment<2>(4) = R2 * sB2 * fi2d * fi2d - R3 * sB3 * fi3d * fi3d;

    return gamma;
}

Eigen::Vector<double, 9> gravitational_forces(const ModelParameters &params) {
    Eigen::Vector<double, 9> grav;
    grav.setZero();

    double m1 = params.m1;
    double m2 = params.m2;
    double m3 = params.m3;
    double g = params.g;

    grav(1) = -m1 * g;
    grav(4) = -m2 * g;
    grav(7) = -m3 * g;

    return grav;
}

Eigen::Vector<double, 9> external_force(const double &force_value) {
    Eigen::Vector<double, 9> force;
    force.setZero();
    force(0) = force_value;

    return force;
}

Eigen::Vector<double, 18> state_dot(const Eigen::Vector<double, 9> &qd_vector,
                                    const Eigen::Vector<double, 9> &q_vector,
                                    const double &force_value,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom) {
    Eigen::Vector<double, 18> yd;
    yd.setZero();
    yd.segment<9>(0) = qd_vector;
    yd.segment<9>(9) =
        solve_dae(qd_vector, q_vector, force_value, params, geom).head<9>();

    return yd;
}

Eigen::Vector<double, 15> solve_dae(const Eigen::Vector<double, 9> &qd_vector,
                                    const Eigen::Vector<double, 9> &q_vector,
                                    const double &force_value,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom) {
    const auto &M = mass_matrix(params);
    const auto &FIq = jacobian_matrix(q_vector, geom);
    const auto &Q = gravitational_forces(params) + external_force(force_value);
    const auto &Gamma = gamma_vector(qd_vector, q_vector, geom);

    Eigen::Matrix<double, 15, 15> A;
    A.setZero();
    A.block<9, 9>(0, 0) = M;
    A.block<9, 6>(0, 9) = FIq.transpose();
    A.block<6, 9>(9, 0) = FIq;

    Eigen::Vector<double, 15> b;
    b << Q, Gamma;

    return A.partialPivLu().solve(b);
}

Eigen::Matrix<double, 9, 9>
jacobian_lambda_q(const Eigen::Vector<double, 9> &q_vector,
                  const Eigen::Vector<double, 6> &lambda,
                  const ModelGeometry &geom) {
    Eigen::Matrix<double, 9, 9> fiqlamq;
    fiqlamq.setZero();

    auto omega = omega_matrix();
    double fi1 = q_vector(2);
    double fi2 = q_vector(5);
    double fi3 = q_vector(8);
    auto R1 = rotation_matrix(fi1);
    auto R2 = rotation_matrix(fi2);
    auto R3 = rotation_matrix(fi3);
    auto n = geom.n_1;
    Eigen::Vector2d r0 = {0, 0};
    auto r1 = q_vector.segment<2>(0);
    auto sp11 = geom.s_A1;
    auto sp22 = geom.s_B2;
    auto sp12 = geom.s_A2;
    auto sp33 = geom.s_B3;
    double lambda1 = lambda(0);
    auto lambda34 = lambda.segment<2>(2);
    auto lambda56 = lambda.segment<2>(4);

    double a = -(R1 * n).dot((r1 + R1 * sp11 - r0)) *
               lambda1; // the rest is 0 ib behalf of sp11 = 0_2x1
    double b = (R2 * sp12).dot(lambda34) - (R2 * sp22).dot(lambda56);
    double c = (R3 * sp33).dot(lambda56);

    fiqlamq.block<2, 1>(0, 2) = omega * R1 * n * lambda1;
    fiqlamq.block<1, 2>(2, 0) = -(R1 * n).transpose() * omega * lambda1;
    fiqlamq(2, 2) = a;
    fiqlamq(5, 5) = b;
    fiqlamq(8, 8) = c;

    return fiqlamq;
}
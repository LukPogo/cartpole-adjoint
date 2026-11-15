#include "kinematics.hpp"

Eigen::Vector<double, 9> forward_kinematics(const Eigen::Vector3d &theta_vector,
                                            const ModelGeometry &g) {
    Eigen::Vector<double, 9> q_vector;

    double x1 = theta_vector(0);
    double fi2 = theta_vector(1);
    double fi3 = theta_vector(2);

    const auto R2 = rotation_matrix(fi2);
    const auto R3 = rotation_matrix(fi3);

    Eigen::Vector2d r1 = {x1, 0};
    Eigen::Vector2d r2 = r1 + R2 * (-g.s_A2);
    Eigen::Vector2d r3 = r2 + R2 * g.s_B2 + R3 * (-g.s_B3);

    q_vector << r1, 0, r2, fi2, r3, fi3;
    return q_vector;
}
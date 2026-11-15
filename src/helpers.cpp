#include "helpers.hpp"

Eigen::Matrix2d rotation_matrix(double fi) {
    Eigen::Matrix2d R;
    double c = std::cos(fi);
    double s = std::sin(fi);
    R << c, -s, s, c;

    return R;
}

Eigen::Matrix2d omega_matrix() {
    Eigen::Matrix2d Omega;
    Omega << 0, -1, 1, 0;
    return Omega;
}
#include "model.hpp"

const ModelGeometry model_geometry(const ModelParameters &params) {
    Eigen::Vector2d s_A0;
    Eigen::Vector2d s_A1;
    Eigen::Vector2d n_1;
    Eigen::Vector2d s_A2;
    Eigen::Vector2d s_B2;
    Eigen::Vector2d s_B3;

    s_A0 << 0, 0;
    s_A1 << 0, 0;
    s_A2 << -params.l2 / 2, 0;
    s_B2 << params.l2 / 2, 0;
    s_B3 << -params.l3 / 2, 0;
    n_1 << 0, 1;

    return ModelGeometry{s_A0, s_A1, n_1, s_A2, s_B2, s_B3};
}

const ModelParameters initialize_parameters() {
    double m1 = 2;
    // Rectangle of width 0.4 and height 0.2, thus
    // J = m/12(a^2+b^2)
    double J1 = 3.33 * 1e-2;
    double m2 = 0.2;
    // Rigid rod of length 0.2m and width 0.02, so roughly
    // J = m/12L^2
    double J2 = 6.67 * 1e-4;
    double l2 = 0.2;
    double m3 = 0.2;
    double J3 = 6.67 * 1e-4;
    double l3 = 0.2;
    double g = 9.81;
    return ModelParameters{m1, J1, m2, J2, l2, m3, J3, l3, g};
}
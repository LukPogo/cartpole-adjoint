#include "discrete_dynamics.hpp"
#include "helpers.hpp"
#include "kinematics.hpp"
#include "model.hpp"
#include <Eigen/Dense>
#include <iostream>

int test_discrete_step() {

    Eigen::Vector<double, 9> q_init;
    Eigen::Vector<double, 9> qd_init;
    q_init.setZero();
    qd_init.setZero();

    const auto &params = initialize_parameters();
    const auto &geom = model_geometry(params);

    auto pi = std::numbers::pi;

    Eigen::Vector3d theta;
    theta << 0.2, -pi / 3, -2 * pi / 3;

    q_init = forward_kinematics(theta, geom);

    Eigen::Vector<double, 33> z_init;
    z_init.setZero();

    z_init.segment<9>(0) = q_init;
    z_init.segment<9>(9) = qd_init;

    auto z = newton_rhapson(z_init, 0.2, 0.01, params, geom);

    auto F = F_vector(z, z_init, 0.2, 0.01, params, geom);

    std::cout << "Whole z_i+1 vector: " << std::endl;
    std::cout << z << std::endl;

    return 0;
}

int main() { test_discrete_step(); }
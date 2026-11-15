#include "dynamics.hpp"
#include "helpers.hpp"
#include "kinematics.hpp"
#include "model.hpp"
#include <Eigen/Dense>
#include <iostream>

int test_geometrical_jacobian() {

    // Make proper initial conditions initalizator
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

    const auto jacobian = jacobian_matrix(q_init, geom);

    // Part where i calculate numerical jacobian
    double h = 1e-5;
    double eps = 1e-9;

    Eigen::Vector<double, 9> q_vector_plus, q_vector_minus;
    q_vector_minus.setZero();
    q_vector_plus.setZero();

    Eigen::Matrix<double, 6, 9> numerical_jacobian;
    numerical_jacobian.setZero();

    for (int i = 0; i < q_init.size(); i++) {
        q_vector_plus = q_init;
        q_vector_minus = q_init;
        q_vector_plus(i) += h;
        q_vector_minus(i) -= h;

        auto jacobian_col = (phi_constraint_vector(q_vector_plus, geom) -
                             phi_constraint_vector(q_vector_minus, geom)) /
                            (2 * h);
        numerical_jacobian.col(i) = jacobian_col;
    }

    Eigen::Matrix<double, 6, 9> E_jacobian = jacobian - numerical_jacobian;

    std::cout << E_jacobian << std::endl;
    std::cout << E_jacobian.cwiseAbs().maxCoeff() << std::endl;

    if (E_jacobian.cwiseAbs().maxCoeff() > eps) {
        return 1;
    }

    std::cout << "Jacobian is proper" << std::endl;

    return 0;
}

int main() { test_geometrical_jacobian(); }
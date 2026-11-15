#pragma once

#include <Eigen/Dense>

#include "helpers.hpp"
#include "model.hpp"

Eigen::Matrix<double, 9, 9> mass_matrix(const ModelParameters &params);
Eigen::Vector<double, 15> solve_dae(const Eigen::Vector<double, 9> &qd_vector,
                                    const Eigen::Vector<double, 9> &q_vector,
                                    const double &force_value,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom);
Eigen::Vector<double, 18> state_dot(const Eigen::Vector<double, 9> &qd_vector,
                                    const Eigen::Vector<double, 9> &q_vector,
                                    const double &force_value,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom);
Eigen::Vector<double, 6>
phi_constraint_vector(const Eigen::Vector<double, 9> &q_vector,
                      const ModelGeometry &geom);
Eigen::Matrix<double, 6, 9>
jacobian_matrix(const Eigen::Vector<double, 9> &q_vector,
                const ModelGeometry &geom);

Eigen::Vector<double, 6> gamma_vector(const Eigen::Vector<double, 9> &qd_vector,
                                      const Eigen::Vector<double, 9> &q_vector,
                                      const ModelGeometry &geom);

Eigen::Matrix<double, 9, 9>
jacobian_lambda_q(const Eigen::Vector<double, 9> &q_vector,
                  const Eigen::Vector<double, 6> &lambda,
                  const ModelGeometry &geom);
Eigen::Vector<double, 9> external_force(const double &force_value);
Eigen::Vector<double, 9> gravitational_forces(const ModelParameters &params);
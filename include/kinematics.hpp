#pragma once

#include "helpers.hpp"
#include "model.hpp"
#include <Eigen/Dense>

Eigen::Vector<double, 9> forward_kinematics(const Eigen::Vector3d &theta_vector,
                                            const ModelGeometry &geom);
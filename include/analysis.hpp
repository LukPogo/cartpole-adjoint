#pragma once

#include "dynamics.hpp"
#include "simulation.hpp"
#include <Eigen/Dense>

struct PhiData {
    Eigen::VectorXd phi_pos;
    Eigen::VectorXd phi_vel;
    Eigen::VectorXd phi_acc;
};

PhiData calculate_phi_data(const DynamicsSimResult &sim,
                           const ModelGeometry &geom);
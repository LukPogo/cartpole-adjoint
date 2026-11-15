#pragma once
#include "helpers.hpp"
#include <Eigen/Dense>

struct ModelParameters {
    double m1;
    double J1;
    double m2;
    double J2;
    double l2;
    double m3;
    double J3;
    double l3;
    double g;
};

struct ModelGeometry {
    Eigen::Vector2d s_A0;
    Eigen::Vector2d s_A1;
    Eigen::Vector2d n_1;
    Eigen::Vector2d s_A2;
    Eigen::Vector2d s_B2;
    Eigen::Vector2d s_B3;
};

const ModelGeometry model_geometry(const ModelParameters &params);

const ModelParameters initialize_parameters();
#pragma once

#include "dynamics.hpp"

#include <Eigen/Dense>

using Vector33d = Eigen::Vector<double, 33>;
using Vector9d = Eigen::Vector<double, 9>;
using Matrix33d = Eigen::Matrix<double, 33, 33>;
using Matrix9d = Eigen::Matrix<double, 9, 9>;

Vector33d newton_rhapson(const Vector33d &zi, const double &force_value,
                         const double &h, const ModelParameters &params,
                         const ModelGeometry &geom);

Vector33d F_vector(const Vector33d &z, const Vector33d &zi,
                   const double &force_value, const double &h,
                   const ModelParameters &params, const ModelGeometry &geom);
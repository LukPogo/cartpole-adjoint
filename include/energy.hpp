#pragma once

#include <Eigen/Dense>

#include "dynamics.hpp"
#include "model.hpp"

double total_energy(const Eigen::Vector<double, 18> &state,
                    const ModelParameters &params);

#pragma once

#include <highfive/eigen.hpp>
#include <highfive/highfive.hpp>

#include <Eigen/Dense>

#include "analysis.hpp"
#include "simulation.hpp"
#include <filesystem>

void save_simulation(const std::filesystem::path &path,
                     const DynamicsSimResult &res, const PhiData &data);
#pragma once

#include "discrete_dynamics.hpp"
#include "dynamics.hpp"
#include "energy.hpp"
#include "kinematics.hpp"
#include "model.hpp"

#include <Eigen/Dense>
#include <boost/numeric/odeint.hpp>

struct SimulationParameters {
    const double t0;
    const double tk;
    const double h;
    const int N;
    Eigen::VectorXd time;

  public:
    SimulationParameters(double t0, double tk, double h)
        : t0(t0), tk(tk), h(h), N(static_cast<int>(std::floor((tk - t0) / h))),
          time(Eigen::VectorXd::LinSpaced(N + 1, t0, tk)) {}
};

struct DynamicsSimResult {
    Eigen::VectorXd time;
    Eigen::MatrixXd states;
    Eigen::VectorXd controls;
    Eigen::MatrixXd qdd_his;
    Eigen::VectorXd energy;
};

DynamicsSimResult simulate_dynamics(const Eigen::Vector<double, 18> &state_init,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom,
                                    const SimulationParameters &sim_params);

DynamicsSimResult simulate_discrete_dynamics(
    const Eigen::Vector<double, 18> &state_init, const ModelParameters &params,
    const ModelGeometry &geom, const SimulationParameters &sim_params);
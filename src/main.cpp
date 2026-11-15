#include "analysis.hpp"
#include "data.hpp"
#include "kinematics.hpp"
#include "simulation.hpp"
#include <Eigen/Dense>

int main() {

    using State = Eigen::Vector<double, 18>;

    State state_vector;
    state_vector.setZero();

    auto params = initialize_parameters();
    auto geom = model_geometry(params);

    // Eigen::Vector3d theta_init = {0, -std::numbers::pi / 2,
    //                               -std::numbers::pi / 2};
    Eigen::Vector3d theta_init = {0, 0, 0};
    // Eigen::Vector3d theta_init = {0, -std::numbers::pi / 4, 0};
    auto q_init = forward_kinematics(theta_init, geom);
    state_vector.segment<9>(0) = q_init;

    const double t0 = 0;
    const double tk = 10;
    const double h = 0.0001;

    auto sim_params = SimulationParameters(t0, tk, h);

    auto sim_res = simulate_dynamics(state_vector, params, geom, sim_params);
    auto phi_data = calculate_phi_data(sim_res, geom);

    save_simulation("../data/continuous/dynamics.h5", sim_res, phi_data);

    sim_res =
        simulate_discrete_dynamics(state_vector, params, geom, sim_params);
    phi_data = calculate_phi_data(sim_res, geom);

    save_simulation("../data/discrete/dynamics.h5", sim_res, phi_data);

    return 0;
}
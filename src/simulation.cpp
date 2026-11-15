#include "simulation.hpp"

DynamicsSimResult simulate_dynamics(const Eigen::Vector<double, 18> &state_init,
                                    const ModelParameters &params,
                                    const ModelGeometry &geom,
                                    const SimulationParameters &sim_params) {
    namespace odeint = boost::numeric::odeint;
    using State = Eigen::Vector<double, 18>;
    odeint::runge_kutta4<State, double, State, double,
                         odeint::vector_space_algebra>
        stepper;
    // Simulation parameters should be given as an input

    const double h = sim_params.h;
    const int N = sim_params.N;

    auto time = sim_params.time;

    Eigen::Vector<double, 18> state;
    state = state_init;

    Eigen::Matrix<double, Eigen::Dynamic, 18> state_history(N + 1, 18);
    Eigen::Vector<double, Eigen::Dynamic> energy_history(N + 1);
    Eigen::Vector<double, Eigen::Dynamic> control_history(N);

    Eigen::Matrix<double, Eigen::Dynamic, 9> qdd_history(N + 1, 9);

    state_history.row(0) = state_init.transpose();

    energy_history(0) = total_energy(state, params);

    double const_force = 0;

    qdd_history.row(0) =
        state_dot(state.tail<9>(), state.head<9>(), const_force, params, geom)
            .tail<9>()
            .transpose();
    auto system = [&](const State &y, State &dydt, double t) {
        auto q_vector = y.segment<9>(0);
        auto qd_vector = y.segment<9>(9);
        dydt = state_dot(qd_vector, q_vector, const_force, params, geom);
    };

    for (int i = 0; i < N; i++) {
        double t = time(i);
        stepper.do_step(system, state, t, h);
        state_history.row(i + 1) = state.transpose();
        energy_history(i + 1) = total_energy(state, params);
        auto dydt = state_dot(state.tail<9>(), state.head<9>(), const_force,
                              params, geom);
        qdd_history.row(i + 1) = dydt.tail<9>().transpose();
        control_history(i) = const_force;
    }

    return DynamicsSimResult{time, state_history, control_history, qdd_history,
                             energy_history};
}

DynamicsSimResult simulate_discrete_dynamics(
    const Eigen::Vector<double, 18> &state_init, const ModelParameters &params,
    const ModelGeometry &geom, const SimulationParameters &sim_params) {

    const double h = sim_params.h;
    const int N = sim_params.N;

    auto time = sim_params.time;

    Eigen::Vector<double, 33> z_init;
    z_init.setZero();
    z_init.segment<18>(0) = state_init;

    Eigen::Vector<double, 33> z;
    z = z_init;

    Eigen::Matrix<double, Eigen::Dynamic, 18> state_history(N + 1, 18);
    Eigen::Vector<double, Eigen::Dynamic> energy_history(N + 1);
    Eigen::Vector<double, Eigen::Dynamic> control_history(N);

    Eigen::Matrix<double, Eigen::Dynamic, 9> qdd_history(N + 1, 9);

    state_history.row(0) = state_init.transpose();

    energy_history(0) = total_energy(state_init, params);

    // Force = input should be given as a function argument in time or as Vector
    double const_force = 0;

    qdd_history.row(0) = z.segment<9>(18).transpose();
    for (int i = 0; i < N; i++) {
        z = newton_rhapson(z, const_force, h, params, geom);
        state_history.row(i + 1) = z.head<18>().transpose();
        energy_history(i + 1) = total_energy(z.head<18>(), params);
        qdd_history.row(i + 1) = z.segment<9>(18).transpose();
        control_history(i) = const_force;
    }
    return DynamicsSimResult{time, state_history, control_history, qdd_history,
                             energy_history};
}
#include "analysis.hpp"

PhiData calculate_phi_data(const DynamicsSimResult &sim,
                           const ModelGeometry &geom) {
    auto states = sim.states;
    auto qdd_history = sim.qdd_his;

    const int N = states.rows();
    Eigen::Vector<double, Eigen::Dynamic> phi_pos(N);
    Eigen::Vector<double, Eigen::Dynamic> phi_vel(N);
    Eigen::Vector<double, Eigen::Dynamic> phi_acc(N);

    for (int i = 0; i < N; i++) {
        auto state = states(i, Eigen::all).transpose();
        auto q_vector = state.segment<9>(0);
        auto qd_vector = state.segment<9>(9);
        auto qdd_vector = qdd_history.row(i).transpose();
        auto phi_vector = phi_constraint_vector(q_vector, geom);
        phi_pos(i) = phi_vector.norm();
        auto phi_q = jacobian_matrix(q_vector, geom);
        phi_vel(i) = (phi_q * qd_vector).norm();
        auto gamma = gamma_vector(qd_vector, q_vector, geom);
        phi_acc(i) = (phi_q * qdd_vector - gamma).norm();
    }

    return PhiData{phi_pos, phi_vel, phi_acc};
}
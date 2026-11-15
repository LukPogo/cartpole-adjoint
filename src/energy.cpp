// Calculate energy vector in time, then save it in SimulationResult

#include "energy.hpp"

double potential_energy(const Eigen::Vector<double, 18> &state,
                        const ModelParameters &params) {
    double y1 = state(1);
    double y2 = state(4);
    double y3 = state(7);

    // 0 level is at y = 0 this on y1 = 0
    double V = 0;
    double g = params.g;

    V += params.m1 * g * y1;
    V += params.m2 * g * y2;
    V += params.m3 * g * y3;

    return V;
}

double kinetic_energy(const Eigen::Vector<double, 18> &state,
                      const ModelParameters &params) {
    auto mass = mass_matrix(params);
    auto qd_vector = state.segment<9>(9);

    return 0.5 * qd_vector.transpose() * mass * qd_vector;
}

double total_energy(const Eigen::Vector<double, 18> &state,
                    const ModelParameters &params) {
    return kinetic_energy(state, params) + potential_energy(state, params);
}
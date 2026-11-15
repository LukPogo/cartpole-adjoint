#include "data.hpp"

void save_dynamics_data(HighFive::File &file, const DynamicsSimResult &res) {

    file.createDataSet("time", res.time);
    file.createDataSet("states", res.states);
    file.createDataSet("controls", res.controls);
    file.createDataSet("energy", res.energy);
}

void save_phi_data(HighFive::File &file, const PhiData &data) {

    file.createDataSet("phi_pos", data.phi_pos);
    file.createDataSet("phi_vel", data.phi_vel);
    file.createDataSet("phi_acc", data.phi_acc);
}

void save_simulation(const std::filesystem::path &path,
                     const DynamicsSimResult &res, const PhiData &data) {
    HighFive::File file(path.string(), HighFive::File::Truncate);

    std::filesystem::create_directories(path.parent_path());

    save_dynamics_data(file, res);
    save_phi_data(file, data);
}
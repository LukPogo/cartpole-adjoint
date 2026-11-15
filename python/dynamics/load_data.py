from dataclasses import dataclass

import h5py
import numpy as np


@dataclass
class SimData:
    time: np.ndarray
    states: np.ndarray
    controls: np.ndarray
    energy: np.ndarray


def load_data(path) -> SimData:

    with h5py.File(path, "r") as file:
        time = np.asarray(file["time"], dtype=np.float64)
        states = np.asarray(file["states"], dtype=np.float64)
        controls = np.asarray(file["controls"], dtype=np.float64)
        energy = np.asarray(file["energy"], dtype=np.float64)

    return SimData(time, states, controls, energy)


@dataclass
class PhiData:
    phi_pos: np.ndarray
    phi_vel: np.ndarray
    phi_acc: np.ndarray


def load_phi_data(path):
    with h5py.File(path, "r") as file:
        phi_pos = np.asarray(file["phi_pos"], dtype=np.float64)
        phi_vel = np.asarray(file["phi_vel"], dtype=np.float64)
        phi_acc = np.asarray(file["phi_acc"], dtype=np.float64)

    return PhiData(phi_pos, phi_vel, phi_acc)

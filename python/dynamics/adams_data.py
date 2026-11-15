import numpy as np


def load_adams_data(path: str):

    cart_q = np.loadtxt(path + "cart_q", dtype=np.float64, skiprows=8)
    cart_qd = np.loadtxt(path + "cart_qd", dtype=np.float64, skiprows=8)
    pole1_q = np.loadtxt(path + "pole1_q", dtype=np.float64, skiprows=8)
    pole1_qd = np.loadtxt(path + "pole1_qd", dtype=np.float64, skiprows=8)
    pole2_q = np.loadtxt(path + "pole2_q", dtype=np.float64, skiprows=8)
    pole2_qd = np.loadtxt(path + "pole2_qd", dtype=np.float64, skiprows=8)

    # In ideal world no conversion needed, i will do it that way in the next iteration

    cart_q[:, 2] -= np.pi / 2
    pole1_q[:, 2] -= np.pi / 2
    pole2_q[:, 2] -= np.pi / 2

    state = np.concatenate(
        [cart_q, pole1_q, pole2_q, cart_qd, pole1_qd, pole2_qd], axis=1
    )

    return state

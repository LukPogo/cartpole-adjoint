import matplotlib.pyplot as plt
import numpy as np

from load_data import PhiData, SimData, load_phi_data, load_data


def plot_phi_time(data: PhiData, sim_data: SimData):
    t = sim_data.time
    phi_pos = data.phi_pos
    phi_vel = data.phi_vel
    phi_acc = data.phi_acc

    fig, ax = plt.subplots()

    ax.plot(t, phi_pos, label=r"$\Phi_q$", color="b")
    ax.plot(t, phi_vel, label=r"$\Phi_v$", color="g")
    ax.plot(t, phi_acc, label=r"$\Phi_a$", color="r")

    ax.set_xlabel("Time [s]")
    ax.set_ylabel(r"$\Phi_q, \Phi_v, \Phi_a$")

    ax.set_title("Constraint residual errors")
    ax.legend()
    ax.grid()

    ax.legend()

    plt.show()


def print_phi_stats(data: PhiData):
    phi_pos = data.phi_pos
    phi_vel = data.phi_vel
    phi_acc = data.phi_acc

    print(
        f"Maximum pos error:\t{np.abs(phi_pos).max()}\nMaximum vel error:\t{np.abs(phi_vel).max()}\nMaximum acc error:\t{np.abs(phi_acc).max()}"
    )


def main():
    cont = "data/continuous/dynamics.h5"
    data = load_data(cont)
    phi_data = load_phi_data(cont)
    print("Continuous:")
    print_phi_stats(phi_data)
    plot_phi_time(phi_data, data)

    disc = "data/discrete/dynamics.h5"
    data = load_data(disc)
    phi_data = load_phi_data(disc)
    print("Discrete:")
    print_phi_stats(phi_data)
    plot_phi_time(phi_data, data)


if __name__ == "__main__":
    main()

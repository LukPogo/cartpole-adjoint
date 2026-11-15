import matplotlib.pyplot as plt
import numpy as np
from load_data import SimData, load_data


def plot_energy_comparison(c_data: SimData, d_data: SimData):
    time = c_data.time
    cont_energy = c_data.energy
    disc_energy = d_data.energy

    fig, ax = plt.subplots()

    ax.set_title("Energy comparison")
    ax.set_xlabel("Time [s]")
    ax.set_ylabel("Energy [J]")

    ax.plot(time, cont_energy, label="RK4", color="r", lw=6, linestyle="dashed")
    ax.plot(time, disc_energy, label="Implicit Euler", color="g", lw=2)

    plt.show()


def print_energy_stats(c_data: SimData, d_data: SimData):
    cont_energy = c_data.energy
    disc_energy = d_data.energy
    print(
        f"Max cont energy:\t{cont_energy.max()}\tMax disc energy:\t{disc_energy.max()}"
    )
    print(
        f"Min cont energy:\t{cont_energy.min()}\tMin disc energy:\t{disc_energy.min()}"
    )
    print(f"Init cont energy:\t{cont_energy[0]}\tInit disc energy:\t{disc_energy[0]}")
    print(f"Last cont energy:\t{cont_energy[-1]}\tLast disc energy:\t{disc_energy[-1]}")


def main():
    cont = "data/continuous/dynamics.h5"
    c_data = load_data(cont)
    disc = "data/discrete/dynamics.h5"
    d_data = load_data(disc)

    print_energy_stats(c_data, d_data)
    plot_energy_comparison(c_data, d_data)


if __name__ == "__main__":
    main()

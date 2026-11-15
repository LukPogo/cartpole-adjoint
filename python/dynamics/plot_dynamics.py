import matplotlib.pyplot as plt
import numpy as np
from adams_data import load_adams_data
from load_data import SimData, load_data


def plot_three_independent(cont_dat: SimData, disc_data: SimData):
    time = cont_dat.time
    x1c = cont_dat.states[:, 0]
    x1d = disc_data.states[:, 0]
    plot_qi_comparison(x1c, x1d, time)

    fi2c = cont_dat.states[:, 5]
    fi2d = disc_data.states[:, 5]
    plot_qi_comparison(fi2c, fi2d, time)

    fi3c = cont_dat.states[:, 8]
    fi3d = disc_data.states[:, 8]
    plot_qi_comparison(fi3c, fi3d, time)


def plot_qi_comparison(qi_cont: np.ndarray, qi_disc: np.ndarray, t: np.ndarray):

    error = np.abs(qi_cont - qi_disc)

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.plot(t, qi_cont, color="r", label=r"$x_{1_c}$")
    ax1.plot(t, qi_disc, color="g", label=r"$x_{1_d}$")
    ax1.set_title("Comparison of discrete and continuous solutions")

    ax1.set_xlabel("Time [s]")
    ax1.set_ylabel(r"$x_{1_c}$ $x_{1_d}$")
    ax1.legend()

    ax2.plot(t, error, color="b")
    ax2.set_title("Absolute error of discrete and continuous solutions")
    ax2.set_xlabel("Time [s]")
    ax2.set_ylabel(r"$e_{abs}$")

    plt.show()


def plot_x1_comparison(data_cont: SimData, data_disc: SimData, adams_data: np.ndarray):

    t = data_cont.time[::100]
    x1c = data_cont.states[::100, 0]
    x1d = data_disc.states[::100, 0]
    x1a = adams_data[:, 0]

    errorc = np.abs(x1a - x1c)
    errord = np.abs(x1a - x1d)

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.plot(t, x1c, color="r", label=r"$x_{1_c}$")
    ax1.plot(t, x1d, color="g", label=r"$x_{1_d}$")
    ax1.plot(t, x1a, color="y", label=r"$x_{1_Adams}$", lw=2)
    ax1.set_title("Comparison of discrete and continuous solutions to reference")

    ax1.set_xlabel("Time [s]")
    ax1.set_ylabel(r"$x_{1_c}$ $x_{1_d}$")
    ax1.legend()

    ax2.plot(t, errorc, color="r", label="Cont. error")
    ax2.plot(t, errord, color="g", label="Disc. error")
    ax2.set_title(
        "Absolute error of discrete and continuous solutions to reference solution"
    )
    ax2.set_xlabel("Time [s]")
    ax2.set_ylabel(r"$e_{abs}$")

    plt.show()


def plot_fi2_comparison(data_cont: SimData, data_disc: SimData, adams_data: np.ndarray):

    t = data_cont.time[:]
    x1c = data_cont.states[:, 5]
    x1d = data_disc.states[:, 5]
    x1a = adams_data[:, 5]

    errorc = np.abs(x1a - x1c)
    errord = np.abs(x1a - x1d)

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.plot(t, x1c, color="r", label=r"$\phi_{2_c}$")
    ax1.plot(t, x1d, color="g", label=r"$\phi_{2_d}$")
    ax1.plot(t, x1a, color="y", label=r"$\phi_{2_Adams}$", lw=5)
    ax1.set_title("Comparison of discrete and continuous solutions to reference")

    ax1.set_xlabel("Time [s]")
    ax1.set_ylabel(r"$\phi_{1_c}$ $\phi_{1_d}$")
    ax1.legend()

    ax2.plot(t, errorc, color="r", label="Cont. error")
    ax2.plot(t, errord, color="g", label="Disc. error")
    ax2.set_title(
        "Absolute error of discrete and continuous solutions to reference solution"
    )
    ax2.set_xlabel("Time [s]")
    ax2.set_ylabel(r"$e_{abs}$")

    plt.show()


def plot_fi3_comparison(data_cont: SimData, data_disc: SimData, adams_data: np.ndarray):

    t = data_cont.time
    x1c = data_cont.states[:, 8]
    x1d = data_disc.states[:, 8]
    x1a = adams_data[:, 8]

    errorc = np.abs(x1a - x1c)
    errord = np.abs(x1a - x1d)

    fig, (ax1, ax2) = plt.subplots(1, 2)

    ax1.plot(t, x1c, color="r", label=r"$\phi_{2_c}$")
    ax1.plot(t, x1d, color="g", label=r"$\phi_{2_d}$")
    ax1.plot(t, x1a, color="y", label=r"$\phi_{2_Adams}$", lw=1, linestyle="-")
    ax1.set_title("Comparison of discrete and continuous solutions to reference")

    ax1.set_xlabel("Time [s]")
    ax1.set_ylabel(r"$\phi_{1_c}$ $\phi_{1_d}$")
    ax1.legend()

    ax2.plot(t, errorc, color="r", label="Cont. error")
    ax2.plot(t, errord, color="g", label="Disc. error")
    ax2.set_title(
        "Absolute error of discrete and continuous solutions to reference solution"
    )
    ax2.set_xlabel("Time [s]")
    ax2.set_ylabel(r"$e_{abs}$")

    plt.show()


def print_sim_stats(c_data: SimData, d_data: SimData):
    x1c = c_data.states[:, 0]
    x1d = d_data.states[:, 0]
    errorx1 = np.abs(x1c - x1d)
    print("x1:")
    print_basic_info(x1c, x1d, errorx1)

    fi2c = c_data.states[:, 5]
    fi2d = d_data.states[:, 5]
    errorfi2 = np.abs(fi2c - fi2d)
    print("fi2:")
    print_basic_info(fi2c, fi2d, errorfi2)

    fi3c = c_data.states[:, 8]
    fi3d = d_data.states[:, 8]
    errorfi3 = np.abs(fi3c - fi3d)
    print("fi3:")
    print_basic_info(fi3c, fi3d, errorfi3)


def print_basic_info(qi_c, qi_d, eqi):
    print(f"First cont value:\t{qi_c[0]}\tFirst disc value:\t{qi_d[0]}")
    print(f"Last cont value:\t{qi_c[-1]}\tLast disc value:\t{qi_d[-1]}")
    print(f"Maximum cont value:\t{qi_c.max()}\tMaximum disc value:\t{qi_d.max()}")
    print(f"First error value:\t{eqi[0]}")
    print(f"Last error value:\t{eqi[-1]}")
    print(f"Maximum error value:\t{eqi.max()}")


def main():
    cont = "data/continuous/dynamics.h5"
    c_data = load_data(cont)
    disc = "data/discrete/dynamics.h5"
    d_data = load_data(disc)
    adams = "data/adams_data/"
    adams_data = load_adams_data(adams)

    plot_x1_comparison(c_data, d_data, adams_data)
    # print_sim_stats(c_data, d_data)
    # plot_three_independent(c_data, d_data)


if __name__ == "__main__":
    main()

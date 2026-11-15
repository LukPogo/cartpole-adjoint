import matplotlib.animation as animation
import matplotlib.pyplot as plt
import numpy as np
from load_data import SimData, load_data
from matplotlib.patches import Rectangle


def animate_cartpole(data: SimData):

    states = data.states
    r1 = states[:, 0:2]
    fi1 = states[:, 2]
    r2 = states[:, 3:5]
    fi2 = states[:, 5]
    r3 = states[:, 6:8]
    fi3 = states[:, 8]

    fig, ax = plt.subplots()

    ax.set_xlim(-0.2, 6)
    ax.set_ylim(-0.5, 0.5)
    ax.set_aspect("equal", adjustable="box")

    cart_w = 0.4
    cart_h = 0.4
    cart = Rectangle(
        (r1[0, 0] - cart_w / 2, r1[0, 1] - cart_h / 2),
        cart_w,
        cart_h,
        angle=np.degrees(fi1[0]),
    )
    ax.add_patch(cart)

    pole_w = 0.05
    pole_h = 0.2
    pole1 = Rectangle(
        (r2[0, 0] - pole_w / 2, r2[0, 1] - pole_h),
        pole_w,
        pole_h,
        angle=np.degrees(fi2[0]) - 90,
        rotation_point="center",
    )
    pole1.set_color("orange")
    ax.add_patch(pole1)

    pole2 = Rectangle(
        (r3[0, 0] - pole_w / 2, r3[0, 1] - pole_h),
        pole_w,
        pole_h,
        angle=np.degrees(fi3[0]) - 90,
        rotation_point="center",
    )
    pole2.set_color("red")
    ax.add_patch(pole2)

    def update(frame):
        camera_w = 2.0
        camera_h = 1.0

        r1_u = r1[frame]
        cart.set_xy((r1_u[0] - cart_w / 2, r1_u[1] - cart_h / 2))

        r2u = r2[frame]
        fi2u = fi2[frame]
        pole1.set_xy((r2u[0] - pole_w / 2, r2u[1] - pole_h / 2))
        pole1.set_angle(np.degrees(fi2u) - 90)

        r3u = r3[frame]
        fi3u = fi3[frame]
        pole2.set_xy((r3u[0] - pole_w / 2, r3u[1] - pole_h / 2))
        pole2.set_angle(np.degrees(fi3u) - 90)

        ax.set_xlim(r1_u[0] - camera_w / 2, r1_u[0] + camera_w / 2)
        ax.set_ylim(r1_u[1] - camera_h / 2, r1_u[1] + camera_h / 2)

        return cart, pole1, pole2

    frames = states.shape[0]

    ani = animation.FuncAnimation(fig=fig, func=update, frames=frames, interval=30)
    plt.show()


def main():
    cont = "data/continuous/dynamics.h5"
    data = load_data(cont)
    animate_cartpole(data)

    disc = "data/discrete/dynamics.h5"
    data = load_data(disc)
    animate_cartpole(data)


if __name__ == "__main__":
    main()

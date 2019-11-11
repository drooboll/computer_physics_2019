import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import numpy as np
import math

fig, ax = plt.subplots()
ln, = plt.plot([], [])

x_num = 1000
t_num = 100
t_max = 0.5
l = 1
xdata = np.linspace(0, l, x_num)
q = (t_max / t_num) / ((l / x_num) ** 2)
d = 2


def calc_simple(a1, b1, c1, d1):
    _a = [x for x in a1]
    _b = [x for x in b1]
    _c = [x for x in c1]
    _d = [x for x in d1]

    for i in range(1, len(_a)):
        xi = _a[i] / _b[i - 1]
        _b[i] -= xi * _c[i - 1]
        _d[i] -= xi * _d[i - 1]
    # print("d: ", _d)
    y = [0] * len(_a)
    y[-1] = _d[-1] / _b[-1]

    for i in range(len(_a) - 2, -1, -1):
        y[i] = 1 / _b[i] * (_d[i] - _c[i] * y[i + 1])
    return y


txt = plt.text(0.85, 0.9, '0.0', horizontalalignment="left", verticalalignment="center", transform=ax.transAxes)


def init():
    ax.set_xlim(0.0, l)
    ax.set_ylim(0, 0.15)
    # plt.yscale("log")
    return ln, txt


count = 0


def update(frame):
    global count
    global txt
    if count != t_num:
        count += 1
    else:
        count = 0
    ydata = frame
    ln.set_data(xdata, ydata)
    txt.set_text("T={}".format(round(count / t_num * t_max, 3)))
    return ln, txt


def Lu(u, j):
    if not j:
        return 0
    if j == (len(u) - 1):
        return 0
    return u[j] + 0.5 * q * d * (u[j - 1] - 2 * u[j] + u[j + 1])


u_list = []
u_max = []
u = [2 * (x * (1 - x / l)) ** 2 for x in xdata]
#u = [1 - math.cos(2 * math.pi * x / l) for x in xdata]
u_max.append(max(u))

a = [-q * d / 2] * x_num
b = [1 + q * d] * x_num
c = [-q * d / 2] * x_num


def set_neuman():
    a[0] = 0
    a[-1] = -b[-1]
    c[0] = -b[0]
    c[-1] = 0


def set_dir():
    global a, b, c, u
    a[0] = c[0] = 0
    a[-1] = c[-1] = 0
    b[0] = b[-1] = 1
    u[0] = 0
    u[1] = 0


def calc_neuman():
    set_neuman()
    global u, a, b, c, ax
    ax.set_ylim(0, 0.15)
    u = [Lu(u, i) for i in range(len(u))]
    u_list.append(u)

    for i in range(t_num):
        u = calc_simple(a, b, c, u)
        u = [Lu(u, i) for i in range(len(u))]
        u[0] = u[-1] = 0
        u_list.append(u)
        u_max.append(max(u))


def calc_dir():
    set_dir()
    global u, a, b, c, ax
    ax.set_ylim(0, 0.15)
    u_list.append(u)

    for i in range(t_num):
        u = calc_simple(a, b, c, u)
        u = [Lu(u, i) for i in range(len(u))]
        u[0] = u[-1] = 0
        u_list.append(u)
        u_max.append(max(u))


def plot_max():
    print(u_max)
    plt.plot([x / t_num * t_max for x in range(t_num + 1)], u_max)
    plt.yscale("log")
    plt.show()


def plot_anim():
    ani = FuncAnimation(fig, update, frames=u_list, init_func=init, blit=True, interval=100)
    plt.show()


calc_neuman()

plot_anim()

import matplotlib.pyplot as plt
import math
import numpy as np

points = 1000
high_point = math.pi * 2
low_point = 0
h = (high_point - low_point) / (points)

x = [h ** 2 * math.sin(h * t) for t in range(0, points)]
t = [h * t1 for t1 in range(0, points)]
a = [1] * (points)
b = [-2] * (points)
c = [1] * (points)

# c0[0] = 0
# b0[0] = 1
# b0[points - 1] = 1
# a0[points - 1] = 0
# #
# x[0] = 0
# x[points - 1] = 0


def calc_simple(a1, b1, c1, d1):
    _a = [a__ for a__ in a1]
    _b = [b__ for b__ in b1]
    _c = [c__ for c__ in c1]
    _d = [d__ for d__ in d1]

    for i in range(1, len(_a)):
        xi = _a[i] / _b[i - 1]
        _b[i] -= xi * _c[i - 1]
        _d[i] -= xi * _d[i - 1]

    y = [0] * len(_a)
    y[len(_a) - 1] = _d[len(_a) - 1] / _b[len(_a) - 1]

    for i in range(len(_a) - 2, -1, -1):
        y[i] = 1 / _b[i] * (_d[i] - _c[i] * y[i + 1])

    return y


def cyclic(a, b, c, d):
    y1 = calc_simple(a[:-1], b[:-1], c[:-1], d[:-1])
    u = [0] * (len(a) - 1)
    u[0] = -a[0]
    u[len(a) - 2] = -c[len(a) - 2]
    v = [0] * (len(a) - 1)
    v[len(a) - 2] = a[len(a) - 1]
    y2 = calc_simple(a[:-1], b[:-1], c[:-1], u)
    k = b[len(a) - 1] + v[0] * y2[0] + v[len(a) - 2] * y2[len(a) - 2]
    if k < 1.0e-7:
        y_n = 42
    else:
        y_n = (d[len(a) - 1] - v[0] * y1[0] - v[len(a) - 2] * y1[len(a) - 2]) / k
    y_real = [y1[i] + y_n * y2[i] for i in range(len(a) - 1)]
    y_real.append(y_n)
    return y_real


def calcDir(x0, x1):
    global a, b, c, x, h
    a[0] = 0
    b[0] = 1
    x[0] = x0
    c[0] = 0
    a[-1] = 0
    c[-1] = 0
    b[-1] = 1
    x[-1] = x1
    y = calc_simple(a, b, c, x)
    plt.plot(t, y, label=r'$y(0)={}, y(2 \pi)={}$'.format(round(x0, 4), round(x1, 4)))


def calc3(y11, y10, x1, y21, y20, x2):
    global a, b, c, x, h
    a[0] = 0
    b[0] = -y11 / h + y10
    x[0] = x1
    c[0] = y11 / h
    a[-1] = -y21 / h
    c[-1] = 0
    b[-1] = y21 / h + y20
    x[-1] = x2
    y = calc_simple(a, b, c, x)
    if y11 == 1:
        y11 = ""
    if y10 == 1:
        y10 = ""
    if y21 == 1:
        y21 = ""
    if y20 == 1:
        y20 = ""

    if y11 == 0:
        firstBlock = "{}y".format(y10)
    else:
        if y10 != 0:
            firstBlock = "{}y' + {}y".format(y11, y10)
        else:
            firstBlock = "{}y'".format(y11)

    if y21 == 0:
        secondBlock = "{}y".format(y20)
    else:
        if y20 != 0:
            secondBlock = "{}y' + {}y".format(y21, y20)
        else:
            secondBlock = "{}y'".format(y21)
    for i in range(len(y)):
        y[i] -= t[i]
    plt.plot(t, y, label=r"$(" + firstBlock + ")(0)={}, (".format(round(x1, 4)) + secondBlock + ")(2 \pi)={}$".format(round(x2, 4)))


calc3(0, 1, 1, 0, 1, 1 + 2*math.pi)
#y = cyclic(a, b, c, x)
#plt.plot(t, y)

plt.legend()
plt.ylabel('y')
plt.xlabel('x')
plt.show()

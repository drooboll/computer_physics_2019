import math
import matplotlib.pyplot as plt

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


def find_eigen(a, b, c):
    d = [1] * len(a)
    for i in range(20):
        d = calc_simple(a, b, c, d)

    temp = calc_simple(a, b, c, d)
    sq1 = 0
    sq2 = 0
    for v in d:
        sq1 += v * v
    for v in temp:
        sq2 += v * v
    eigen = math.sqrt(sq1) / math.sqrt(sq2)
    for i in range(len(a)):
        temp[i] /= math.sqrt(sq2)
    return eigen, temp


def find_by_existing(a, b, c, list):
    if not len(list) % 2:
        d = [1] * len(a)
    else:
        d = [1] * len(a)
        for i in range(round(len(a) / 2), len(a)):
            d[i] = -1
    for i in range(20):
        for v in list:
            scal = 0
            norm = 0
            for j in range(len(a)):
                scal += d[j] * v[j]
                norm += v[j] ** 2
            norm = math.sqrt(norm)
            for j in range(len(a)):
                d[j] -= scal / norm * v[j]
        d = calc_simple(a, b, c, d)

    temp = calc_simple(a, b, c, d)
    sq1 = 0
    sq2 = 0
    for v in d:
        sq1 += v * v
    for v in temp:
        sq2 += v * v
    eigen = math.sqrt(sq1) / math.sqrt(sq2)
    for i in range(len(a)):
        temp[i] /= math.sqrt(sq2)
    return eigen, temp


lowBound = -15
highBound = 15
points = 1000
h = (highBound - lowBound) / points


t = [i / points * (highBound - lowBound) + lowBound for i in range(points)]

a = [-1 / 2 / h**2] * points
b = [1 / h**2] * points
c = [-1 / 2 / h**2] * points

for i in range(points):
    b[i] += t[i] ** 2 / 2 + 4

a[0] = 0
c[-1] = 0
list = []
e_list = []

for i in range(3):
    e, y = find_by_existing(a, b, c, list)
    e_list += [e]
    list += [y]
    line, = plt.plot(t, y)
    line.set_label(e)

plt.legend()
plt.show()
import cmath
import math
import matplotlib.pyplot as plt

a0 = 1
a1 = 0.002
w0 = 5.1
w1 = 25.5
T = 2 * math.pi

num = 100


def signal(t):
    return a0 * math.sin(w0 * t) + a1 * math.sin(w1 * t)


def rect(n):
    if 0 <= n < num:
        return 1
    else:
        return 0


def hann(n):
    return 0.5 * (1 - math.cos(2 * math.pi * n / (num - 1)))


def convolve(fun):
    res = []
    for i in range(num):
        sum = complex(0, 0)
        for j in range(num):
            time = j / num * T
            sum += signal(time) * fun(j) * cmath.exp(complex(0, 2 * math.pi * i * j / (num - 1)))
        res.append(sum.__abs__() ** 2 / num)
    return res


fourier = convolve(rect)
fourier_h = convolve(hann)
freq = range(num)

plt.yscale("log")
plt.plot(freq, fourier, label="Rect")
plt.plot(freq, fourier_h, label="Hann")
plt.legend()
plt.show()


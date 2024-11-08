#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import matplotlib.pyplot as plt
import numpy as np
from scipy import signal
from IIR2Filter import IIR2Filter


def butter_lowpass(lowcut, fs, order):
    nyq = 0.5 * fs
    low = lowcut / nyq
    b, a = signal.butter(4, [low], 'lowpass', analog=False)
    return b, a

def butter_bandpass_filter(data, lowcut, fs, order):
    b, a = butter_lowpass(lowcut, fs, order)
    y = signal.filtfilt(b, a, data, axis=0)
    return y


def main():
    fs = 1000
    # 离线滤波
    data = np.loadtxt('sin.dat')
    data2 = data+10
    data_filter = butter_bandpass_filter(data, 10, fs, 3)
    data2_filter = butter_bandpass_filter(data2, 10, fs, 3)
    # 在线滤波
    FilterMains = IIR2Filter(2, [8], filterType='lowpass', design='butter', fs=fs)
    FilterMains2 = IIR2Filter(2, [8], filterType='lowpass', design='butter', fs=fs)

    # data_filter_on = np.zeros(len(data))
    # data2_filter_on = np.zeros(len(data))
    data_filter_on = []
    data2_filter_on = []
    for i in range(len(data)):
        data_filter_on.append(FilterMains.filter(data[i]))
        data2_filter_on.append(FilterMains2.filter(data2[i]))
    plt.figure(1)
    plt.xlabel("Time [ms]")
    plt.ylabel("Amplitude")
    plt.plot(data)
    plt.plot(data_filter)
    plt.plot(data_filter_on)
    plt.show()

    plt.figure(2)
    plt.xlabel("Time [ms]")
    plt.ylabel("Amplitude")
    plt.plot(data2)
    plt.plot(data2_filter)
    plt.plot(data2_filter_on)
    plt.show()
    return data_filter


if __name__ == '__main__':
    main()

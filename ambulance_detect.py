from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np

rate, data = wavfile.read('amb.wav')
length = data.shape[0] / rate
# print(data.shape[0])
# time = np.linspace(0., length, data.shape[0])
# plt.plot(time, data, label="Audio")
print(len(set(data)))
# plt.legend()
# plt.xlabel("Time [sS]")
# plt.ylabel("Amplitude")
# plt.show()

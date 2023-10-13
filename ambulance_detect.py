from scipy.fft import fft, fftfreq
from scipy.io import wavfile
import matplotlib.pyplot as plt
import numpy as np

sample_rate, data = wavfile.read('amb.wav')
length = data.shape[0] / sample_rate
print(data.shape[0])
time = np.linspace(0., length, data.shape[0])
# plt.plot(time, data, label="Audio")
# plt.legend()
# plt.xlabel("Time [sS]")
# plt.ylabel("Amplitude")
# plt.show()

# filtering signal
N = sample_rate * time
print(N)

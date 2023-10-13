from scipy.fft import fft, fftfreq
from scipy.io import wavfile
from scipy.signal import find_peaks
import matplotlib.pyplot as plt
import numpy as np

sample_rate, audio_data = wavfile.read('amb.wav')
length = audio_data.shape[0] / sample_rate
audio_data = np.abs(audio_data)
# print(audio_data.shape[0])
time = np.linspace(0., length, audio_data.shape[0])
# plt.plot(time, data, label="Audio")
# plt.legend()
# plt.xlabel("Time [sS]")
# plt.ylabel("Amplitude")
# plt.show()

# filtering signal
max_frequency = sample_rate / 2
print(f"max freq : {max_frequency}")


# peaks in audio file
if len(audio_data.shape) > 1:
    audio_data = audio_data.mean(axis=1)
peaks, _ = find_peaks(audio_data, height=0)

# average of peaks
peak_values = audio_data[peaks]
print(peak_values[len(peak_values)//2:])
average_peak_values = np.mean(peak_values)
print(f"average peak values : {average_peak_values}")

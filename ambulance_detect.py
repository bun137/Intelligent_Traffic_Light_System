from scipy.fft import fft, fftfreq
from scipy.io import wavfile
from scipy.signal import find_peaks
import matplotlib.pyplot as plt
import numpy as np
from pydub import AudioSegment

# --------------------------------------------
# converting mp3 to wav format
# mp3_file = "citytraffic.mp3"
# wav_file = "citytraffic.wav"
# audio = AudioSegment.from_mp3(mp3_file)
# audio.export(wav_file, format="wav")
# --------------------------------------------

# file_str -> filename / path to .wav file


def audio_analysis(file_str: str):
    sample_rate, audio_data = wavfile.read(file_str)
    length = audio_data.shape[0] / sample_rate
    audio_data = np.abs(audio_data)
    # print(audio_data.shape[0])
    time = np.linspace(0., length, audio_data.shape[0])
    # plt.plot(time, audio_data, label="Audio")
    # plt.legend()
    # plt.xlabel("Time [sS]")
    # plt.ylabel("Amplitude")
    # plt.show()

    # filtering signal
    max_frequency = sample_rate / 2
    # print(f"max freq : {max_frequency}")

    # peaks in audio file
    if len(audio_data.shape) > 1:
        audio_data = audio_data.mean(axis=1)
    peaks, _ = find_peaks(audio_data, height=0)

    # average of peaks
    mean_wave_value = np.mean(audio_data)
    print(f"mean wave vallue : {mean_wave_value}")
    peak_values = audio_data[peaks]
    print(peak_values[len(peak_values)//2:])
    mean_peak_values = np.mean(peak_values)
    print(f"average peak values : {mean_peak_values}")


audio_analysis('citytraffic.wav')
print('\n\n')
audio_analysis('amb.wav')

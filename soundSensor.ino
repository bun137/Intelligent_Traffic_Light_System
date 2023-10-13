#include "arduinoFFT.h"
 
#define SAMPLES 128            
#define SAMPLING_FREQUENCY 2048 
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; 
double vImag[SAMPLES]; 
 
void setup() 
{
    Serial.begin(115200); 
    samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); 
}
 
void loop() 
{  

    for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();   
     
        vReal[i] = analogRead(0); 
        vImag[i] = 0; 

       
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /Perform FFT on samples/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);


    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    Serial.println(peak);     //most dominant frequency.
    if (peak > 650 && < 1500 && isCNN() || isCNN()){
        Serial.println("Ambulance Detected");
    }

bool isCNN(){
    return true; //placeholder
}

//Add ambulance siren
#include <fftw3.h>
#include <iostream>
#include <fstream>
#include <cmath>

// Function to apply FFT and analyze frequency-domain data
void analyzeAudioData(double* audioData, int dataSize) {
    // Create FFTW plan
    fftw_complex* fftResult = fftw_alloc_complex(dataSize);
    fftw_plan plan = fftw_plan_dft_r2c_1d(dataSize, audioData, fftResult, FFTW_ESTIMATE);
    
    // Execute FFT
    fftw_execute(plan);
    
    // Analyze frequency-domain data
    for (int i = 0; i < dataSize; i++) {
        double real = fftResult[i][0];
        double imag = fftResult[i][1];
        double magnitude = sqrt((real * real) + (imag * imag));
        
        // If the magnitude of a frequency falls within the range of an ambulance siren,
        // print that the siren has been detected
        if (magnitude >= SIREN_MIN_FREQ && magnitude <= SIREN_MAX_FREQ) {
            std::cout << "Ambulance siren detected!" << std::endl;
            break;
        }
    }
    
    // Clean up
    fftw_destroy_plan(plan);
    fftw_free(fftResult);
}

int main() {
    // Load audio data from file
    std::ifstream file("audioData.wav", std::ios::binary | std::ios::in);
    if (!file) {
        std::cerr << "Failed to open audio file!" << std::endl;
        return 1;
    }
    
    // Read audio data into buffer
    file.seekg(0, std::ios::end);
    int dataSize = file.tellg();
    file.seekg(0, std::ios::beg);
    double* audioData = new double[dataSize];
    file.read(reinterpret_cast<char*>(audioData), dataSize);
    file.close();
    
    // Analyze audio data
    analyzeAudioData(audioData, dataSize);
    
    delete[] audioData;
    return 0;
}

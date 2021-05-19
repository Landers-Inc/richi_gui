#pragma once

#include <QDebug>
#include <QObject>
#include <QThread>
#include <iostream>
#include <random>

#include "datawindow.h"
#include "fftw3.h"
#include "qcustomplot.h"

// Class dedicated to process incoming data
class DataProcessor : public QObject {
    Q_OBJECT
   public:
    explicit DataProcessor(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0) : QObject(parent), dataSize(dataSizeArg), sampleFrequency(sampleFrequencyArg) {
        initialize();
    };

    // Struct to save peaks data
    typedef struct Peak {
        double frequency;
        double value;
        int index;
    } Peak;

    // Struct to set frequency bins to search for peaks
    typedef struct FrequencyIndex {
        int begin;
        int end;
    } FrequencyIndex;

   private:
    // Accumulator size
    int accumulatorSize = 10;
    // Pointer to the current value value in the accumulator to overwrite
    int accumulatorPointer = 0;
    // Buffer size for data processing
    int dataSize = 0;
    // Sample frequency
    double sampleFrequency = 0.0;
    // Window applied to time data
    std::vector<double> dataWindow;
    // Window process gain
    double processGain = -2.997;
    // X axis time data
    std::vector<double> timeDomain;
    // X axis frequency data
    std::vector<double> frequencyDomain;
    // Bins used to search for peaks
    std::vector<FrequencyIndex> frequencyBins;
    // FFT accumulator used to get the average of several FFTs
    std::vector<std::vector<double>> fftAccumulator;

    // Function to calculate the FFT of a time serie
    std::vector<std::vector<double>> fftCalculation(std::vector<double> data);
    // Function to calculate the average FFT of the accumulator
    std::vector<double> fftAverage(std::vector<std::vector<double>> data);
    // Function to get the peaks of the instantaneous FFT
    std::vector<DataProcessor::Peak> getPeaks(std::vector<std::vector<double>> fft);
    // Function to get the weighted frequency of the peak
    DataProcessor::Peak getWeightedFrequency(std::vector<std::vector<double>> fft, int index);
    // Function to calculate the entropy of the FFT - Unused right now
    double calculateEntropy(std::vector<std::vector<double>> data);
    // Function to initialize the vector members
    void initialize();
   signals:
    // Qt Signal used to send the FFT data to the GUI thread
    void fftReady(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Signal used to send the time serie data to the GUI thread
    void dataReady(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Signal used to refresh the screen in the GUI thread
    void plotData();

    // Qt Signal used to update the first peak data in the GUI thread
    void peakOneReady(double freq, double power);
    // Qt Signal used to update the second peak data in the GUI thread
    void peakTwoReady(double freq, double power);
    // Qt Signal used to update the third peak data in the GUI thread
    void peakThreeReady(double freq, double power);
   public slots:
    // Qt Slot used to receive the data from the DataAcquisition
    void processData(std::vector<double> amplitudeData);
};

#pragma once

#include <QDebug>
#include <QObject>
#include <QThread>
#include <iostream>
#include <random>

#include "datalogger.h"
#include "datawindow.h"
#include "emlidgps.h"
#include "fftw3.h"
#include "qcustomplot.h"
#include "statemachine.h"
#include "usbadc.h"

// Class dedicated to process incoming data
class DataProcessor : public QObject {
    Q_OBJECT
   private:
    QThread *dataAcquiring;
    QThread *gpsAcquiring;
    DataReader *dataAcquisition;
    GPSReader *gpsAcquisition;

   public:
    explicit DataProcessor(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0) : QObject(parent), dataSize(dataSizeArg), sampleFrequency(sampleFrequencyArg) {
        initialize();
    };
    ~DataProcessor();

    // Struct to save peaks data
    typedef struct Peak {
        double frequency;
        double power;
        int index;
    } Peak;

    // Struct to set frequency bins to search for peaks
    typedef struct FrequencyIndex {
        int begin;
        int end;
    } FrequencyIndex;

   private:
    // GPS object instance
    EMLIDGPS *gpsInstance;
    // Latitude position received from GPS
    double gpsLatitude = 0;
    // Longitude position received from GPS
    double gpsLongitude = 0;
    // Timestamp received from GPS
    unsigned int gpsTime = 0;
    // Number of Space Vehicles used
    unsigned int nSV = 0;
    // Accumulator size
    int accumulatorSize = 5;
    // Pointer to the current value value in the accumulator to overwrite
    int accumulatorPointer = 0;
    // Peaks serie size
    int peakSerieSize = 2048;
    // Peak tracking to display in the GUI size
    int peakToDisplay = 0;
    // Pointer to the current value value in the peak to overwrite
    int peakPointer = 0;
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
    // FFT accumulator used to get the average of several FFTs
    std::vector<std::vector<double>> peakTimeserie;

    // Function to calculate the FFT of a time serie
    std::vector<std::vector<double>> fftCalculation(std::vector<double> data);
    // Function to calculate the average FFT of the accumulator
    std::vector<std::vector<double>> fftAverage(std::vector<std::vector<double>> data);
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
    // Qt Signal used to stop GPS running thread
    void gpsQuit();

    // Qt Signal used to update the first peak data in the GUI thread
    void peakOneReady(double freq, double power);
    // Qt Signal used to update the second peak data in the GUI thread
    void peakTwoReady(double freq, double power);
    // Qt Signal used to update the third peak data in the GUI thread
    void peakThreeReady(double freq, double power);

    // Qt Signal used to log a configuration
    void logConfiguration(DataLogger::Configuration const &conf);
    // Qt Signal used to log a timestamp
    void logTimestamp(DataLogger::TimeData const &time);
    // Qt Signal used to log a beacon
    void logBeacon(DataLogger::BeaconData const &beacon);
    // Qt Signal used to log a spectrum
    void logSpectrum(DataLogger::SpectrumData const &spectrum);
    // Qt Signal used to log a peak
    void logPeaks(DataLogger::PeaksData const &peaks);

   public slots:
    // Qt Slot used to receive the data from DataAcquisition
    void processData(std::vector<double> amplitudeData);
    // Qt Slot used to receive the data from GPSReader
    void processGPS(double const &latitude, double const &longitude);
    // Qt Slot used to select peak timeserie to display
    void setPeakToDisplay(int disp);
};

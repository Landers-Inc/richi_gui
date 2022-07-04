#pragma once

#include <QDebug>
#include <QObject>
#include <QSound>
#include <QThread>
#include <cmath>
#include <iostream>
#include <random>

#include "datalogger.h"
#include "datawindow.h"
#include "emlidgps.h"
#include "fakegps.h"
#include "fftw3.h"
#include "qcustomplot.h"
#include "statemachine.h"
#include "usbadc.h"
#include "utils.h"

// Class dedicated to process incoming data
class DataProcessor : public QObject {
    Q_OBJECT
   private:
    QThread *dataAcquiring;
    QThread *gpsAcquiring;
    QThread *beepPlaying;
    QThread *gpsStatus;
    DataReader *dataAcquisition;
    GPSReader *gpsAcquisition;
    StateMachine *stateInstance;
    QSound *beepWav;
    QTimer *beepTimer;
    QTimer *gpsTimer;

    signed int currentBeepLevel = -120;

   public:
    explicit DataProcessor(int dataSizeArg,
                           double sampleFrequencyArg,
                           int windowOptionArg,
                           float beaconAArg,
                           float beaconBArg,
                           float beaconCArg,
                           QObject *parent = 0) : QObject(parent),
                                                  dataSize(dataSizeArg),
                                                  sampleFrequency(sampleFrequencyArg),
                                                  windowOption(windowOptionArg),
                                                  beaconA(beaconAArg * 1000.0),
                                                  beaconB(beaconBArg * 1000.0),
                                                  beaconC(beaconCArg * 1000.0) {
        std::cout << "Starting DataProcessor instance" << std::endl;
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
    bool startingAxisPosition = false;
    // Time = 0, Distance = 1
    unsigned int timeDistance = 0;
    // Latitude position received from GPS
    double gpsLatitude = 0;
    // Longitude position received from GPS
    double gpsLongitude = 0;
    // Height position received from GPS
    double gpsHeight = 0;
    // Timestamp received from GPS
    unsigned int gpsTime = 0;
    // Number of Space Vehicles used
    unsigned int nSV = 0;
    // Number of Space Vehicles used
    unsigned long long int currentTime = 0;
    // Number of Space Vehicles used
    double currentPositionLatitude = 0;
    double currentPositionLongitude = 0;
    double currentPositionHeight = 0;
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
    // Sample counter
    long unsigned int sampleCount = 0;
    // Sample frequency
    double sampleFrequency = 0.0;
    // Type of windows used when processing data
    int windowOption = 0;
    // Beacon Frequencies
    float beaconA;
    float beaconB;
    float beaconC;
    // Option to log spectrum
    bool logSpectrumOption = false;
    // USB ADC type
    int gpsType = 0;
    // Window applied to time data
    std::vector<double> dataWindow;
    // Window process gain
    double processGain = -2.997;
    // X axis time data
    std::vector<double> timeDomain;
    // X axis time data
    std::vector<double> distanceDomain;
    // X axis frequency data
    std::vector<double> frequencyDomain;
    // Bins used to search for peaks
    std::vector<FrequencyIndex> frequencyBins;
    // FFT accumulator used to get the average of several FFTs
    std::vector<std::vector<double>> fftAccumulator;
    std::vector<std::vector<double>> averageFFT;
    // FFT accumulator used to get the average of several FFTs
    std::vector<Peak> peaksData;
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
    // Function to calculate noise floor of the FFT
    double calculateNoiseFloor(std::vector<double> data);
    // Function to initialize the vector members
    void initialize();
    // Function to reconnect to the GPS
    void reconnectGPS();
   signals:
    // Qt Signal used to send the FFT data to the GUI thread
    void fftReady(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Signal used to send the time serie data to the GUI thread
    void dataReady(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Signal used to refresh the screen in the GUI thread
    void plotData();
    // Qt Signal used to stop GPS running thread
    void gpsQuit();
    // Qt Signal used to start QTimer for beep
    void gpsStatusStart(unsigned int milliseconds);
    // Qt Signal used to start QTimer for beep
    void beepStart(unsigned int milliseconds);
    // Qt Signal used to stop QTimer for beep
    void beepStop();
    // Qt Signal used to update GPS info
    void updateGPSInfo(
        double const &latitude,
        double const &longitude,
        double const &height,
        std::string const &name,
        unsigned char const &type,
        unsigned char const &status,
        unsigned char const &hor,
        unsigned char const &ver);

    // Qt Signal used to update the noise floor in the GUI thread
    void setNoiseFloor(double noiseFloor);
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
    // Qt Signal used to set GPS to disconnected
    void gpsDisconnected();
    // Qt Signal used to set GPS to reconnected
    void gpsReconnected();

   public slots:
    // Qt Slot used to update processor parameters
    void updateParameters(int sampleSizeArg,
                          int sampleFrequencyArg,
                          int accumulatorSizeArg,
                          int windowOptionArg, float beaconA,
                          float beaconB,
                          float beaconC);
    // Qt Slot used to receive the data from DataAcquisition
    void processData(std::vector<double> amplitudeData);
    // Qt Slot used to receive the data from GPSReader
    void processGPS(
        double const &latitude,
        double const &longitude,
        double const &height,
        std::string const &name,
        unsigned char const &type,
        unsigned char const &status,
        unsigned char const &hor,
        unsigned char const &ver);
    // Qt Slot used to select peak timeserie to display
    void setPeakToDisplay(int disp);
    // Qt Slot used to select timeseries axis
    void setViewAxis(int axis);
    // Qt Slot used to select timeseries axis
    void saveBeacon(double distance, double id, int beaconType);
};

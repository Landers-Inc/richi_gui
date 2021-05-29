#pragma once

#include <QObject>
#include <random>

// Abstract class for data acquisition
class DataReader : public QObject {
    Q_OBJECT
   public:
    // Buffer size to process data
    int dataSize;
    // Sample frequency for data acquisition
    double sampleFrequency;
    // Vector to store time data
    std::vector<double> timeData;
    // Vector to store converted data
    std::vector<double> amplitudeData;

    // Class constructor
    explicit DataReader(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0) : QObject(parent), dataSize(dataSizeArg), sampleFrequency(sampleFrequencyArg), amplitudeData(dataSize), timeData(dataSize){};
    // Class destructor
    virtual ~DataReader(){};
    // Buffer size setter
    void setDataSize(int newSize) { dataSize = newSize; };
    // Buffer size getter
    int getDataSize() { return dataSize; };
    // Sample frequency setter
    void setSampleFrequency(double newFrequency) { sampleFrequency = newFrequency; };
    // Sample frequency getter
    double getSampleFrequency() { return sampleFrequency; };
   signals:
    // Qt Signal used to transfer data to DataProcessor thread
    virtual void dataReady(std::vector<double> const &amplitudeData);
   public slots:
    // Qt Slot used to start reading data from converter
    virtual void getData() = 0;
};

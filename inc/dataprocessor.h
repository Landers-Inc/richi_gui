/** author Christopher Muñoz
 * date 07-05-2021
*/


#pragma once

#include <QObject>
#include <QThread>
#include <QDebug>
#include <random>
#include <iostream>

#include "fftw3.h"
#include "qcustomplot.h"
#include "datawindow.h"

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

// Class dedicated to process incoming data
class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0) : QObject(parent){
        dataSize = dataSizeArg;
        sampleFrequency = sampleFrequencyArg;
        initialize();
    };
private:
    double processGain = -2.997;
    int accumulatorPointer = 0;

    int accumulatorSize = 10;

    int dataSize = 0;
    double sampleFrequency = 0.0;
    std::vector<double> hannWindow;
    std::vector<double> timeDomain;
    std::vector<double> frequencyDomain;
    std::vector<FrequencyIndex> frequencyBins;
    std::vector<std::vector<double>> fftAccumulator;

    std::vector<std::vector<double>> fftCalculation(std::vector<double> data);
    std::vector<double> fftAverage(std::vector<std::vector<double>> data);
    std::vector<Peak> getPeaks(std::vector<std::vector<double>> fft);
    Peak getWeightedFrequency(std::vector<std::vector<double>> fft, int index);
    double calculateEntropy(std::vector<std::vector<double>> data);
    void initialize();
signals:
    void fftReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void dataReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void plotData();

    void peakOneReady(double freq, double power);
    void peakTwoReady(double freq, double power);
    void peakThreeReady(double freq, double power);
public slots:
    void processData(std::vector<double> amplitudeData);
};

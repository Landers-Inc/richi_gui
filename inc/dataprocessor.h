#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <random>
#include <iostream>

#include "fftw3.h"
#include "qcustomplot.h"

extern int N_size;
extern double sampleFrequency;

typedef struct Peak {
    double frequency;
    double value;
    int index;
} Peak;

typedef struct FrequencyIndex {
    int begin;
    int end;
} FrequencyIndex;

class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = 0) : QObject(parent), hannWindow(N_size, 0), frequencyBins(3){
        for(int i = 0; i < N_size; i++) {
            //hannWindow[i] = 0.5 * (1 - cos(2*M_PI*i/N_size));
            hannWindow[i] = 0.355768 - 0.487396*cos(2*M_PI*i/N_size) + 0.144232*cos(4*M_PI*i/N_size) - 0.012604*cos(6*M_PI*i/N_size);
            //hannWindow[i] = 1.0;
        }
        frequencyBins[0] = {(int)floor(2048*10500.0/44100.0), (int)ceil(2048*11500.0/44100.0)};
        frequencyBins[1] = {(int)floor(2048*11500.0/44100.0), (int)ceil(2048*12500.0/44100.0)};
        frequencyBins[2] = {(int)floor(2048*12500.0/44100.0), (int)ceil(2048*13500.0/44100.0)};
    };
private:
    double processGain = -2.997;
    std::vector<double> hannWindow;
    std::vector<FrequencyIndex> frequencyBins;
    std::vector<std::vector<double>> fftCalculation(std::vector<double> data);
    std::vector<Peak> getPeaks(std::vector<std::vector<double>> fft);
    Peak getWeightedFrequency(std::vector<std::vector<double>> fft, int index);
    double calculateEntropy(std::vector<std::vector<double>> data);
signals:
    void fftReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void fftOldReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void dataReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void dataOldReady(QVector<double> const &xSeries,QVector<double> const &ySeries);

    void peakOneReady(double freq, double power);
    void peakTwoReady(double freq, double power);
    void peakThreeReady(double freq, double power);
public slots:
    void processData(std::vector<double> timeData, std::vector<double> amplitudeData);
};

#endif // DATAPROCESSOR_H

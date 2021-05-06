#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <random>
#include <iostream>

#include "fftw3.h"

#include "qcustomplot.h"
#include "mainwindow.h"

class DataProcessor : public QObject {
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = 0) : QObject(parent){};
private:
    std::default_random_engine generator_amp_noise;
    std::default_random_engine generator_freq_noise;
    std::vector<std::vector<double>> fftCalculation(std::vector<double> data);
signals:
    void fftReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void dataReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
public slots:
    void doData();
};

#endif // MYOBJECT_H

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

std::vector<std::vector<double>> fftCalculation(std::vector<double> data);

class MyObject : public QObject {
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = 0) : QObject(parent){};
private:
    std::default_random_engine generator_amp_noise;
    std::default_random_engine generator_freq_noise;
signals:
    void fftReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void dataReady(QVector<double> const &xSeries,QVector<double> const &ySeries);
public slots:
    void doData();
    void doFFT(std::vector<std::vector<double>> *in);
};

#endif // MYOBJECT_H

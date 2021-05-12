#include <QtCore>
#include <QObject>
#include <QVector>
#include <QThread>
#include <QPushButton>
#include <cmath>
#include <iterator>
#include <random>
#include <fftw3.h>

#include "qcustomplot.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dataprocessor.h"

int N_size = 4096;
double sampleFrequency = 44100.0;

void MainWindow::updateData(QVector<double> const &xSeries,QVector<double> const &ySeries){
    QCustomPlot *leftPlot = ui->leftPlot;
    leftPlot->graph(0)->setData(xSeries, ySeries);
    leftPlot->replot();
}

void MainWindow::updateFFT(QVector<double> const &xSeries,QVector<double> const &ySeries){
    QCustomPlot *rightPlot = ui->rightPlot;
    rightPlot->graph(0)->setData(xSeries, ySeries);
    rightPlot->replot();
}

void MainWindow::updateOnePeak(double freq, double power){
    QLabel *peakOneFreqValue = ui->peakOneFreqValue;
    QLabel *peakOnePowerValue = ui->peakOnePowerValue;
    peakOneFreqValue->setText(QString::number(freq));
    peakOnePowerValue->setText(QString::number(power));
}

void MainWindow::updateTwoPeak(double freq, double power){
    QLabel *peakTwoFreqValue = ui->peakTwoFreqValue;
    QLabel *peakTwoPowerValue = ui->peakTwoPowerValue;
    peakTwoFreqValue->setText(QString::number(freq));
    peakTwoPowerValue->setText(QString::number(power));
}

void MainWindow::updateThreePeak(double freq, double power){
    QLabel *peakThreeFreqValue = ui->peakThreeFreqValue;
    QLabel *peakThreePowerValue = ui->peakThreePowerValue;
    peakThreeFreqValue->setText(QString::number(freq));
    peakThreePowerValue->setText(QString::number(power));
}

void MainWindow::startThreads(){
    this->dataProcessor = new DataProcessor;
    this->dataAcquisition = new USBADC(N_size, sampleFrequency);
    this->dataProcessor->moveToThread(&this->dataProcessing);
    this->dataAcquisition->moveToThread(&this->dataAcquiring);
    emit peripheralsReady(1.1, 1.2);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    ui->setupUi(this);

    ui->centralWidget->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD),Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->rightPlot->xAxis->setLabel("Frequency");
    ui->rightPlot->yAxis->setLabel("Power");
    ui->rightPlot->xAxis->setRange(0, sampleFrequency/2);
    ui->rightPlot->yAxis->setRange(-80, 4);
    // ui->rightPlot->xAxis->setBasePen(QPen(Qt::white));
    // ui->rightPlot->xAxis->setTickPen(QPen(Qt::white));
    // ui->rightPlot->xAxis->setLabelColor(Qt::white);
    // ui->rightPlot->xAxis->setTickLabelColor(Qt::white);
    // ui->rightPlot->yAxis->setBasePen(QPen(Qt::white));
    // ui->rightPlot->yAxis->setTickPen(QPen(Qt::white));
    // ui->rightPlot->yAxis->setLabelColor(Qt::white);
    // ui->rightPlot->yAxis->setTickLabelColor(Qt::white);

    ui->leftPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD),Qt::SolidPattern));
    ui->leftPlot->addGraph();
    ui->leftPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->leftPlot->xAxis->setLabel("Time");
    ui->leftPlot->yAxis->setLabel("Amplitude");
    ui->leftPlot->xAxis->setRange(0, (double)(N_size/sampleFrequency));
    ui->leftPlot->yAxis->setRange(-0.01, 0.01);

    startPeripherals = new std::thread(&MainWindow::startThreads, this);

    connect(this, &MainWindow::peripheralsReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);
    connectButtons();

    startPeripherals->join();

    connect(&dataProcessing, &QThread::finished, dataProcessor, &QObject::deleteLater);
    connect(&dataAcquiring, &QThread::finished, dataAcquisition, &QObject::deleteLater);
    //TODO Possible Queue infinitely increment
    connect(dataAcquisition, &DataAcquisition::dataReady, dataProcessor, &DataProcessor::processData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::dataReady, this, &MainWindow::updateData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::fftReady, this, &MainWindow::updateFFT, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakOneReady, this, &MainWindow::updateOnePeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakTwoReady, this, &MainWindow::updateTwoPeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakThreeReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);

    dataAcquiring.start();
    dataProcessing.start();
}

void MainWindow::connectButtons(){
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
}

MainWindow::~MainWindow(){
    dataAcquiring.quit();
    dataProcessing.quit();
    dataAcquiring.wait();
    dataProcessing.wait();
    delete ui;
}


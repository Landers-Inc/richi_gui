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

void MainWindow::updateData(QVector<double> const &xSeries, QVector<double> const &ySeries){
    QCustomPlot *leftPlot = ui->leftPlot;
    leftPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries){
    QCustomPlot *rightPlot = ui->rightPlot;
    rightPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateOnePeak(double freq, double power){
    QCustomPlot *rightPlot = ui->rightPlot;
    QLabel *peakOneFreqValue = ui->peakOneFreqValue;
    QLabel *peakOnePowerValue = ui->peakOnePowerValue;
    peakOneFreqValue->setText(QString::number(freq));
    peakOnePowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    rightPlot->graph(1)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateTwoPeak(double freq, double power){
    QCustomPlot *rightPlot = ui->rightPlot;
    QLabel *peakTwoFreqValue = ui->peakTwoFreqValue;
    QLabel *peakTwoPowerValue = ui->peakTwoPowerValue;
    peakTwoFreqValue->setText(QString::number(freq));
    peakTwoPowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    rightPlot->graph(2)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateThreePeak(double freq, double power){
    QCustomPlot *rightPlot = ui->rightPlot;
    QLabel *peakThreeFreqValue = ui->peakThreeFreqValue;
    QLabel *peakThreePowerValue = ui->peakThreePowerValue;
    peakThreeFreqValue->setText(QString::number(freq));
    peakThreePowerValue->setText(QString::number(power));

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    rightPlot->graph(3)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updatePlots(){
    QCustomPlot *rightPlot = ui->rightPlot;
    QCustomPlot *leftPlot = ui->leftPlot;
    rightPlot->replot();
    leftPlot->replot();
}

void MainWindow::startThreads(){
    connect(this, &MainWindow::peripheralsReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);

    dataProcessing.setObjectName("processor thread");
    dataAcquiring.setObjectName("acquiring thread");
    dataProcessor = new DataProcessor(N_size, sampleFrequency);
    dataAcquisition = new USBADC(N_size, sampleFrequency);
    dataProcessor->moveToThread(&dataProcessing);
    dataAcquisition->moveToThread(&dataAcquiring);

    connect(&dataProcessing, &QThread::finished, dataProcessor  , &QObject::deleteLater);
    connect(&dataAcquiring , &QThread::finished, dataAcquisition, &QObject::deleteLater);
    //TODO Possible Queue infinitely increment
    connect(dataAcquisition, &DataAcquisition::dataReady   , dataProcessor, &DataProcessor::processData , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::dataReady     , this         , &MainWindow::updateData     , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::fftReady      , this         , &MainWindow::updateFFT      , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::plotData      , this         , &MainWindow::updatePlots     , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::peakOneReady  , this         , &MainWindow::updateOnePeak  , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::peakTwoReady  , this         , &MainWindow::updateTwoPeak  , Qt::QueuedConnection);
    connect(dataProcessor  , &DataProcessor::peakThreeReady, this         , &MainWindow::updateThreePeak, Qt::QueuedConnection);

    emit peripheralsReady(1.1, 1.2);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    startPeripherals = new std::thread(&MainWindow::startThreads, this);

    connectButtons();

    dataAcquiring.start();
    dataProcessing.start();
}

void MainWindow::openBeaconInput(){
    ui->keyboardWidget->setVisible(!ui->inputBeaconWidget->isVisible());
    ui->inputBeaconWidget->setVisible(!ui->inputBeaconWidget->isVisible());
    if(ui->inputBeaconWidget->isVisible()) {
        ui->inputBeaconWidget->activateWindow();
        ui->inputBeaconOneText->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::connectButtons(){
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
    connect(ui->selectDisplayFreq, &QPushButton::released, this, &MainWindow::openBeaconInput);
}

MainWindow::~MainWindow(){
    dataAcquiring.quit();
    dataProcessing.quit();
    dataAcquiring.wait();
    dataProcessing.wait();
    delete ui;
}

void MainWindow::setupGUI(){
    ui->centralWidget->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD),Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->xAxis->setLabel("Frequency");
    ui->rightPlot->yAxis->setLabel("Power");
    ui->rightPlot->xAxis->setRange(0, sampleFrequency/2);
    ui->rightPlot->yAxis->setRange(-140, 4);
    ui->rightPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->rightPlot->graph(1)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(2)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(3)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));

    // add the text label at the top:
    ui->textLabel = new QCPItemText(ui->rightPlot);
    ui->textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->textLabel->setPadding(QMargins(5, 5, 5, 5));
    ui->textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    ui->textLabel->position->setCoords(0.85, 0); // place position at center/top of axis rect
    ui->textLabel->setFont(QFont(font().family(), 12)); // make font a bit larger
    ui->textLabel->setPen(QPen(Qt::black)); // show black border around text
    ui->textLabel->setBrush(QBrush(Qt::white)); // show black border around text
    ui->textLabel->setText("Window Hanning \nN = 4096\nFs = 44100.0");

    ui->leftPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->leftPlot->addGraph();
    ui->leftPlot->addGraph();
    ui->leftPlot->xAxis->setLabel("Time");
    ui->leftPlot->yAxis->setLabel("Amplitude");
    ui->leftPlot->xAxis->setRange(0, (double)(N_size/sampleFrequency));
    ui->leftPlot->yAxis->setRange(-1.0, 1.0);
    ui->leftPlot->graph(0)->setPen(QPen(Qt::blue));
}
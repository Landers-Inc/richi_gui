#include "mainwindow.h"

#include <fftw3.h>

#include <QObject>
#include <QPushButton>
#include <QThread>
#include <QVector>
#include <QtCore>
#include <cmath>
#include <iterator>
#include <random>

#include "dataprocessor.h"
#include "qcustomplot.h"
#include "ui_mainwindow.h"

int N_size = 4096;
double sampleFrequency = 44100.0;

void MainWindow::warningStatus(QString message) {
    ui->statusLabel->setText(message);
    QTimer::singleShot(3000, [this]() {
        ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    });
}

void MainWindow::switchView() {
    simpleView = !simpleView;
    if (simpleView) {
        ui->barsPlot->setVisible(true);
        ui->peakOneFreqValue->setVisible(false);
        ui->peakOneFreqUnit->setVisible(false);
        ui->peakOnePowerValue->setVisible(false);
        ui->peakOnePowerUnit->setVisible(false);
        ui->peakTwoFreqValue->setVisible(false);
        ui->peakTwoFreqUnit->setVisible(false);
        ui->peakTwoPowerValue->setVisible(false);
        ui->peakTwoPowerUnit->setVisible(false);
        ui->peakThreeFreqValue->setVisible(false);
        ui->peakThreeFreqUnit->setVisible(false);
        ui->peakThreePowerValue->setVisible(false);
        ui->peakThreePowerUnit->setVisible(false);
        ui->rightPlot->setVisible(false);
        ui->selectOneFreq->setText(QCoreApplication::translate("MainWindow", "Baliza A", nullptr));
        ui->selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "Baliza B", nullptr));
        ui->selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "Baliza C", nullptr));
        ui->saveLog->setText(QCoreApplication::translate("MainWindow", "Vista simple", nullptr));
        warningStatus("Status: Vista simple seleccionada");
    } else {
        ui->barsPlot->setVisible(false);
        ui->peakOneFreqValue->setVisible(true);
        ui->peakOneFreqUnit->setVisible(true);
        ui->peakOnePowerValue->setVisible(true);
        ui->peakOnePowerUnit->setVisible(true);
        ui->peakTwoFreqValue->setVisible(true);
        ui->peakTwoFreqUnit->setVisible(true);
        ui->peakTwoPowerValue->setVisible(true);
        ui->peakTwoPowerUnit->setVisible(true);
        ui->peakThreeFreqValue->setVisible(true);
        ui->peakThreeFreqUnit->setVisible(true);
        ui->peakThreePowerValue->setVisible(true);
        ui->peakThreePowerUnit->setVisible(true);
        ui->rightPlot->setVisible(true);
        ui->selectOneFreq->setText(QCoreApplication::translate("MainWindow", "13.75 kHz", nullptr));
        ui->selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "14.00 kHz", nullptr));
        ui->selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "14.25 kHz", nullptr));
        ui->saveLog->setText(QCoreApplication::translate("MainWindow", "Vista avanzada", nullptr));
        warningStatus("Status: Vista avanzada seleccionada");
    }
}

void MainWindow::updateData(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    ui->leftPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    if (!simpleView) ui->rightPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateOnePeak(double freq, double power) {
    ui->peakOneFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakOnePowerValue->setText(QString::number(power, 'f', 2));

    peakValues[0] = power + 150;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(1)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateTwoPeak(double freq, double power) {
    ui->peakTwoFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakTwoPowerValue->setText(QString::number(power, 'f', 2));

    peakValues[1] = power + 150;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(2)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateThreePeak(double freq, double power) {
    ui->peakThreeFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakThreePowerValue->setText(QString::number(power, 'f', 2));

    peakValues[2] = power + 150;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(3)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updatePlots() {
    if (!simpleView) {
        ui->rightPlot->replot();
    } else {
        ui->peaksBars->setData(ui->ticks, peakValues);
        ui->barsPlot->replot();
    }
    ui->leftPlot->replot();
}

void MainWindow::startThreads() {
    stateInstance->startingPeripherals();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);

    dataLogging = new QThread();
    dataProcessing = new QThread();

    dataLogging->setObjectName("logging thread");
    dataProcessing->setObjectName("processor thread");

    dataLogger = DataLogger::getInstance();
    dataProcessor = new DataProcessor(N_size, sampleFrequency);

    dataLogger->moveToThread(dataLogging);
    dataProcessor->moveToThread(dataProcessing);

    connect(dataProcessing, &QThread::finished, dataProcessor, &QObject::deleteLater);
    connect(dataLogging, &QThread::finished, dataLogger, &QObject::deleteLater);
    //TODO Possible Queue infinitely increment
    connect(dataProcessor, &DataProcessor::dataReady, this, &MainWindow::updateData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::fftReady, this, &MainWindow::updateFFT, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::plotData, this, &MainWindow::updatePlots, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakOneReady, this, &MainWindow::updateOnePeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakTwoReady, this, &MainWindow::updateTwoPeak, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::peakThreeReady, this, &MainWindow::updateThreePeak, Qt::QueuedConnection);

    connect(dataProcessor, &DataProcessor::logConfiguration, dataLogger, &DataLogger::insertConfiguration, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logBeacon, dataLogger, &DataLogger::insertBeaconData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logTimestamp, dataLogger, &DataLogger::insertTimeData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logPeaks, dataLogger, &DataLogger::insertPeaksData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::logSpectrum, dataLogger, &DataLogger::insertSpectrumData, Qt::QueuedConnection);

    connect(this, &MainWindow::logConfiguration, dataLogger, &DataLogger::insertConfiguration, Qt::QueuedConnection);
    connect(this, &MainWindow::logBeacon, dataLogger, &DataLogger::insertBeaconData, Qt::QueuedConnection);
    connect(this, &MainWindow::logTimestamp, dataLogger, &DataLogger::insertTimeData, Qt::QueuedConnection);
    connect(this, &MainWindow::logPeaks, dataLogger, &DataLogger::insertPeaksData, Qt::QueuedConnection);
    connect(this, &MainWindow::logSpectrum, dataLogger, &DataLogger::insertSpectrumData, Qt::QueuedConnection);

    connect(this, &MainWindow::setPeakTimeserie, dataProcessor, &DataProcessor::setPeakToDisplay, Qt::QueuedConnection);

    stateInstance->peripheralsReady();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    peakValues = QVector<double>(3);

    stateInstance = StateMachine::getInstance();

    startPeripherals = new std::thread(&MainWindow::startThreads, this);

    connectButtons();

    startPeripherals->join();

    dataProcessing->start();
    dataLogging->start();
}

void MainWindow::openBeaconInput() {
    if (stateInstance->getState() == PREBLAST) {
        if (!ui->inputBeaconWidget->dialogWidget->isVisible()) {
            ui->inputBeaconWidget->dialogWidget->setVisible(true);
            ui->inputBeaconWidget->inputBeaconWidget->setVisible(true);
            ui->inputBeaconWidget->keyboardWidget->setVisible(true);
            ui->inputBeaconWidget->inputBeaconWidget->activateWindow();
            ui->inputBeaconWidget->inputBeaconWidget->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
}

void MainWindow::beaconFoundLog() {
    if (stateInstance->getState() == POSTBLAST) {
    }
}

void MainWindow::beaconAccept() {
    if (ui->inputBeaconWidget->dialogWidget->isVisible()) {
        ui->inputBeaconWidget->dialogWidget->setVisible(false);
        ui->inputBeaconWidget->inputBeaconWidget->setVisible(false);
        ui->inputBeaconWidget->keyboardWidget->setVisible(false);
    }
}

void MainWindow::beaconCancel() {
    if (ui->inputBeaconWidget->dialogWidget->isVisible()) {
        ui->inputBeaconWidget->dialogWidget->setVisible(false);
        ui->inputBeaconWidget->inputBeaconWidget->setVisible(false);
        ui->inputBeaconWidget->keyboardWidget->setVisible(false);
    }
}

void MainWindow::warningAccept() {
    if (ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(false);
        ui->warningWidget->warningWidget->setVisible(false);
    }
    DataLogger::Configuration conf = {N_size, sampleFrequency};
    emit logConfiguration(conf);
    stateInstance->newLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
}

void MainWindow::warningCancel() {
    if (ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(false);
        ui->warningWidget->warningWidget->setVisible(false);
    }
}

void MainWindow::dispFrequencyOne() {
    emit setPeakTimeserie(0);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}

void MainWindow::dispFrequencyTwo() {
    emit setPeakTimeserie(1);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}

void MainWindow::dispFrequencyThree() {
    emit setPeakTimeserie(2);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
}

void MainWindow::startNewLog() {
    if (!ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(true);
        ui->warningWidget->warningWidget->setVisible(true);
        ui->warningWidget->warningWidget->activateWindow();
        ui->warningWidget->warningWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::startNewPreblastLog() {
    stateInstance->preblastLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
}

void MainWindow::startNewPostblastLog() {
    stateInstance->postblastLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
}

void MainWindow::connectButtons() {
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
    connect(ui->saveLog, &QPushButton::released, this, &MainWindow::switchView);
    //
    connect(ui->selectBeacon, &QPushButton::released, this, &MainWindow::openBeaconInput);
    connect(ui->beaconFound, &QPushButton::released, this, &MainWindow::openBeaconInput);
    connect(ui->selectOneFreq, &QPushButton::released, this, &MainWindow::dispFrequencyOne);
    connect(ui->selectTwoFreq, &QPushButton::released, this, &MainWindow::dispFrequencyTwo);
    connect(ui->selectThreeFreq, &QPushButton::released, this, &MainWindow::dispFrequencyThree);

    connect(ui->startLog, &QPushButton::released, this, &MainWindow::startNewLog);
    connect(ui->preblastLog, &QPushButton::released, this, &MainWindow::startNewPreblastLog);
    connect(ui->postblastLog, &QPushButton::released, this, &MainWindow::startNewPostblastLog);

    connect(ui->inputBeaconWidget->inputBeaconAccept, &QPushButton::released, this, &MainWindow::beaconAccept);
    connect(ui->inputBeaconWidget->inputBeaconCancel, &QPushButton::released, this, &MainWindow::beaconCancel);

    connect(ui->warningWidget->warningAccept, &QPushButton::released, this, &MainWindow::warningAccept);
    connect(ui->warningWidget->warningCancel, &QPushButton::released, this, &MainWindow::warningCancel);
}

MainWindow::~MainWindow() {
    dataProcessing->quit();
    dataLogging->quit();
    dataProcessing->wait();
    dataLogging->wait();
    delete stateInstance;
    delete ui;
}

void MainWindow::setupGUI() {
    QFont pfont("Newyork", 8);
    pfont.setStyleHint(QFont::SansSerif);
    pfont.setPointSize(8);

    ui->centralWidget->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD), Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->xAxis->setLabel("Frequency");
    ui->rightPlot->yAxis->setLabel("Power");
    ui->rightPlot->xAxis->setRange(0, sampleFrequency / 2);
    ui->rightPlot->yAxis->setRange(-140, 4);
    ui->rightPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->rightPlot->graph(1)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(2)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(3)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));

    ui->textLabel = new QCPItemText(ui->rightPlot);
    ui->textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->textLabel->setPadding(QMargins(5, 5, 5, 5));
    ui->textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    ui->textLabel->position->setCoords(0.75, 0);
    ui->textLabel->setFont(QFont(font().family(), 10));
    ui->textLabel->setPen(QPen(Qt::black));
    ui->textLabel->setBrush(QBrush(Qt::white));
    ui->textLabel->setText("Window Hanning \nN = 4096\nFs = 44100.0");

    ui->leftPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->leftPlot->addGraph();
    ui->leftPlot->xAxis->setLabel("Time");
    ui->leftPlot->yAxis->setLabel("Amplitude");
    ui->leftPlot->xAxis->setRange(0, (double)(N_size / 2.0 / sampleFrequency));
    ui->leftPlot->yAxis->setRange(-140, 4);
    ui->leftPlot->graph(0)->setPen(QPen(Qt::blue));

    ui->barsPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->barsPlot->setStyleSheet("border: 1px solid #000;");
    ui->peaksBars = new QCPBars(ui->barsPlot->xAxis, ui->barsPlot->yAxis);
    ui->peaksBars->setAntialiased(false);
    ui->peaksBars->setPen(QPen(Qt::blue));
    ui->peaksBars->setBaseValue(-150.0);
    ui->ticks << 1 << 2 << 3;
    ui->labels << "Baliza A"
               << "Baliza B"
               << "Baliza C";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ui->ticks, ui->labels);
    ui->barsPlot->xAxis->setTicker(textTicker);
    ui->barsPlot->xAxis->setSubTicks(false);
    ui->barsPlot->xAxis->setTickLength(0, 3);
    ui->barsPlot->xAxis->setRange(0, 4);
    ui->barsPlot->xAxis->grid()->setVisible(false);

    ui->barsPlot->yAxis->setRange(-140, 0);
    ui->barsPlot->yAxis->setPadding(5);
    ui->barsPlot->yAxis->setLabel("Potencia");
    ui->barsPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->barsPlot->yAxis->grid()->setVisible(false);
    ui->barsPlot->yAxis->grid()->setSubGridVisible(false);

    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 204, 113, 0.4); border: none;");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(204, 46, 113, 0.4); border: none;");
}

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

int N_size = 4096;
double sampleFrequency = 44100.0;

void MainWindow::warningStatus(QString message) {
    ui->statusLabel->setText(message);
    QTimer::singleShot(3000, [this]() {
        ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    });
}

void MainWindow::switchView() {
    ui->simpleView = !ui->simpleView;
    if (ui->simpleView) {
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
        ui->selectDistanceAxis->setVisible(false);
        ui->selectTimeAxis->setVisible(false);
        ui->beaconLayout->setStretch(0, 0);
        ui->selectOneFreq->setText(QCoreApplication::translate("MainWindow", "Baliza A"));
        ui->selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "Baliza B"));
        ui->selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "Baliza C"));
        ui->saveLog->setText(QCoreApplication::translate("MainWindow", "Vista simple"));
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Vista simple seleccionada"));
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
        ui->selectDistanceAxis->setVisible(true);
        ui->selectTimeAxis->setVisible(true);
        ui->beaconLayout->setStretch(0, 1);
        ui->selectOneFreq->setText(QCoreApplication::translate("MainWindow", "13.75 kHz"));
        ui->selectTwoFreq->setText(QCoreApplication::translate("MainWindow", "14.00 kHz"));
        ui->selectThreeFreq->setText(QCoreApplication::translate("MainWindow", "14.25 kHz"));
        ui->saveLog->setText(QCoreApplication::translate("MainWindow", "Vista avanzada"));
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Vista avanzada seleccionada"));
    }
}

void MainWindow::updateData(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    ui->leftPlot->graph(0)->setData(xSeries, ySeries);
    ui->leftPlot->xAxis->rescale();
}

void MainWindow::updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    if (!ui->simpleView) ui->rightPlot->graph(0)->setData(xSeries, ySeries);
}

void MainWindow::updateNoiseFloor(double newNoiseFloor) {
    noiseFloor = newNoiseFloor;
}

void MainWindow::updateOnePeak(double freq, double power) {
    ui->peakOneFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakOnePowerValue->setText(QString::number(power, 'f', 2));

    peakValues[0] = power - noiseFloor;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(1)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateTwoPeak(double freq, double power) {
    ui->peakTwoFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakTwoPowerValue->setText(QString::number(power, 'f', 2));

    peakValues[1] = power - noiseFloor;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(2)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateThreePeak(double freq, double power) {
    ui->peakThreeFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakThreePowerValue->setText(QString::number(power, 'f', 2));

    peakValues[2] = power - noiseFloor;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {-140, 4};
    ui->rightPlot->graph(3)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updatePlots() {
    if (!ui->simpleView) {
        ui->rightPlot->replot();
    } else {
        ui->peaksBars->setData(ui->ticks, peakValues);
        ui->peaksBars->setBaseValue(noiseFloor);
        ui->barsPlot->yAxis->setRange(noiseFloor, 0);
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
    connect(this, &MainWindow::setPeakTimeserie, dataProcessor, &DataProcessor::setPeakToDisplay, Qt::QueuedConnection);
    connect(this, &MainWindow::setViewAxis, dataProcessor, &DataProcessor::setViewAxis, Qt::QueuedConnection);
    connect(this, &MainWindow::logBeacon, dataProcessor, &DataProcessor::saveBeacon, Qt::QueuedConnection);

    stateInstance->peripheralsReady();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    appLanguage = new Ui::Language;
    *appLanguage = Ui::Language::SPANISH;

    ui->translator_es = new QTranslator;
    ui->translator_en = new QTranslator;

    ui->translator_es->load(":/richigui_es");
    ui->translator_en->load(":/richigui_en");

    switch (*appLanguage) {
        case Ui::Language::ENGLISH:
            QCoreApplication::installTranslator(ui->translator_en);
            break;
        case Ui::Language::SPANISH:
            QCoreApplication::installTranslator(ui->translator_es);
            break;
    }

    ui->retranslateUi(this);
    StateMachine::updateString();

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
        if (!ui->inputBeaconWidget->dialogInputWidget->isVisible()) {
            ui->inputBeaconWidget->dialogInputWidget->setVisible(true);
            ui->inputBeaconWidget->beaconInputWidget->setVisible(true);
            ui->inputBeaconWidget->beaconTopInputLabel->setText(QCoreApplication::translate("MainWindow", "Ingreso Nueva Baliza") + ": " + QString::number(dataLogger->getPreblastCount() + 1));
            ui->keyboardInputWidget->setVisible(true);
            ui->inputBeaconWidget->beaconInputWidget->activateWindow();
            ui->inputBeaconWidget->beaconInputWidget->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
}

void MainWindow::openBeaconFound() {
    if (stateInstance->getState() == POSTBLAST) {
        if (!ui->foundBeaconWidget->dialogFoundWidget->isVisible()) {
            ui->foundBeaconWidget->dialogFoundWidget->setVisible(true);
            ui->foundBeaconWidget->beaconFoundWidget->setVisible(true);
            ui->keyboardInputWidget->setVisible(true);
            ui->foundBeaconWidget->beaconFoundWidget->activateWindow();
            ui->foundBeaconWidget->beaconFoundWidget->setFocus(Qt::ActiveWindowFocusReason);
        }
    }
}

void MainWindow::beaconFoundAccept() {
    if (ui->foundBeaconWidget->dialogFoundWidget->isVisible()) {
        QString id = ui->foundBeaconWidget->beaconOneFoundText->text();
        emit logBeacon(id.toDouble());
        ui->foundBeaconWidget->beaconOneFoundText->setText("");
        ui->foundBeaconWidget->dialogFoundWidget->setVisible(false);
        ui->foundBeaconWidget->beaconFoundWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Nueva baliza post-tronadura registrada"));
    }
}

void MainWindow::beaconFoundNotFound() {
    if (ui->foundBeaconWidget->dialogFoundWidget->isVisible()) {
        emit logBeacon(-1);
        ui->foundBeaconWidget->beaconOneFoundText->setText("");
        ui->foundBeaconWidget->dialogFoundWidget->setVisible(false);
        ui->foundBeaconWidget->beaconFoundWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Nueva baliza post-tronadura registrada"));
    }
}

void MainWindow::beaconFoundCancel() {
    if (ui->foundBeaconWidget->dialogFoundWidget->isVisible()) {
        ui->foundBeaconWidget->beaconOneFoundText->setText("");
        ui->foundBeaconWidget->dialogFoundWidget->setVisible(false);
        ui->foundBeaconWidget->beaconFoundWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::beaconInputAccept() {
    if (ui->inputBeaconWidget->dialogInputWidget->isVisible()) {
        QString distance = ui->inputBeaconWidget->beaconOneInputText->text();
        emit logBeacon(distance.toDouble());
        ui->inputBeaconWidget->beaconOneInputText->setText("");
        ui->inputBeaconWidget->dialogInputWidget->setVisible(false);
        ui->inputBeaconWidget->beaconInputWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Nueva baliza pre-tronadura registrada"));
    }
}

void MainWindow::beaconInputCancel() {
    if (ui->inputBeaconWidget->dialogInputWidget->isVisible()) {
        ui->inputBeaconWidget->beaconOneInputText->setText("");
        ui->inputBeaconWidget->dialogInputWidget->setVisible(false);
        ui->inputBeaconWidget->beaconInputWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::warningAccept() {
    if (ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(false);
        ui->warningWidget->warningWidget->setVisible(false);
    }
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentDatetime = std::chrono::system_clock::to_time_t(currentTime);

    char datetimeString[40];
    std::strftime(datetimeString, sizeof(datetimeString), "%Y-%m-%d %H:%M:%S", std::gmtime(&currentDatetime));
    DataLogger::Configuration conf = {datetimeString, N_size, sampleFrequency};
    emit logConfiguration(conf);
    stateInstance->newLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectBeacon->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->postblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->beaconFound->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

void MainWindow::warningCancel() {
    if (ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(false);
        ui->warningWidget->warningWidget->setVisible(false);
    }
}

void MainWindow::dispFrequencyOne() {
    emit setPeakTimeserie(0);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

void MainWindow::dispFrequencyTwo() {
    emit setPeakTimeserie(1);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

void MainWindow::dispFrequencyThree() {
    emit setPeakTimeserie(2);
    ui->selectOneFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
}

void MainWindow::startNewLog() {
    if (!ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(true);
        ui->warningWidget->warningWidget->setVisible(true);
        ui->warningWidget->warningWidget->activateWindow();
        ui->warningWidget->warningWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::switchLanguage() {
    switch (*appLanguage) {
        case Ui::Language::ENGLISH:
            *appLanguage = Ui::Language::SPANISH;
            QCoreApplication::removeTranslator(ui->translator_en);
            QCoreApplication::installTranslator(ui->translator_es);
            break;

        case Ui::Language::SPANISH:
            *appLanguage = Ui::Language::ENGLISH;
            QCoreApplication::removeTranslator(ui->translator_es);
            QCoreApplication::installTranslator(ui->translator_en);
            break;
    }
    ui->retranslateUi(this);
    StateMachine::updateString();
    updateGUI();
    updatePlots();
}

void MainWindow::startNewPreblastLog() {
    stateInstance->preblastLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->selectBeacon->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->postblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->beaconFound->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->standbyLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

void MainWindow::startNewPostblastLog() {
    stateInstance->postblastLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectBeacon->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->postblastLog->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->beaconFound->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->standbyLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

void MainWindow::standbyLog() {
    stateInstance->gotoIdle();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectBeacon->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->postblastLog->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->beaconFound->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->standbyLog->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
}

void MainWindow::selectTimeAxis() {
    ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Time [seconds]"));
    ui->selectTimeAxis->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->selectDistanceAxis->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    emit setViewAxis(0);
    ui->timeDistance = 0;
}

void MainWindow::selectDistanceAxis() {
    ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Distance [meters]"));
    ui->selectTimeAxis->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectDistanceAxis->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    emit setViewAxis(1);
    ui->timeDistance = 1;
}

void MainWindow::connectButtons() {
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
    connect(ui->switchLanguage, &QPushButton::released, this, &MainWindow::switchLanguage);
    connect(ui->saveLog, &QPushButton::released, this, &MainWindow::switchView);
    //
    connect(ui->selectTimeAxis, &QPushButton::released, this, &MainWindow::selectTimeAxis);
    connect(ui->selectDistanceAxis, &QPushButton::released, this, &MainWindow::selectDistanceAxis);

    connect(ui->selectBeacon, &QPushButton::released, this, &MainWindow::openBeaconInput);
    connect(ui->beaconFound, &QPushButton::released, this, &MainWindow::openBeaconFound);
    connect(ui->selectOneFreq, &QPushButton::released, this, &MainWindow::dispFrequencyOne);
    connect(ui->selectTwoFreq, &QPushButton::released, this, &MainWindow::dispFrequencyTwo);
    connect(ui->selectThreeFreq, &QPushButton::released, this, &MainWindow::dispFrequencyThree);

    connect(ui->startLog, &QPushButton::released, this, &MainWindow::startNewLog);
    connect(ui->preblastLog, &QPushButton::released, this, &MainWindow::startNewPreblastLog);
    connect(ui->postblastLog, &QPushButton::released, this, &MainWindow::startNewPostblastLog);
    connect(ui->standbyLog, &QPushButton::released, this, &MainWindow::standbyLog);

    connect(ui->inputBeaconWidget->beaconInputAccept, &QPushButton::released, this, &MainWindow::beaconInputAccept);
    connect(ui->inputBeaconWidget->beaconInputCancel, &QPushButton::released, this, &MainWindow::beaconInputCancel);

    connect(ui->foundBeaconWidget->beaconFoundAccept, &QPushButton::released, this, &MainWindow::beaconFoundAccept);
    connect(ui->foundBeaconWidget->beaconFoundNotFound, &QPushButton::released, this, &MainWindow::beaconFoundNotFound);
    connect(ui->foundBeaconWidget->beaconFoundCancel, &QPushButton::released, this, &MainWindow::beaconFoundCancel);

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

void MainWindow::updateGUI() {
    ui->rightPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Frequency"));
    ui->rightPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Power"));
    ui->textLabel->setText(QCoreApplication::translate("MainWindow", "Window Hanning\nN = 4096\nFs = 44100.0"));
    if (ui->timeDistance == 0) {
        ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Time [seconds]"));
    } else if (ui->timeDistance == 1) {
        ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Distance [meters]"));
    }
    ui->leftPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Amplitude"));
    ui->labels = {QCoreApplication::translate("MainWindow", "Baliza A"),
                  QCoreApplication::translate("MainWindow", "Baliza B"),
                  QCoreApplication::translate("MainWindow", "Baliza C")};
    ui->barsPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Potencia"));
}

void MainWindow::setupGUI() {
    ui->centralWidget->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD), Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Frequency"));
    ui->rightPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Power"));
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
    ui->textLabel->setText(QCoreApplication::translate("MainWindow", "Window Hanning\nN = 4096\nFs = 44100.0"));

    ui->leftPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->leftPlot->addGraph();
    if (ui->timeDistance == 0)
        ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Time [seconds]"));
    else if (ui->timeDistance == 1)
        ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Distance [meters]"));
    ui->leftPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Amplitude"));
    ui->leftPlot->xAxis->setRange(0, 1);
    ui->leftPlot->yAxis->setRange(-140, 4);
    ui->leftPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->leftPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 2));

    ui->barsPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD)));
    ui->barsPlot->setStyleSheet("border: 1px solid #000;");
    ui->peaksBars = new QCPBars(ui->barsPlot->xAxis, ui->barsPlot->yAxis);
    ui->peaksBars->setAntialiased(false);
    ui->peaksBars->setPen(QPen(Qt::blue));
    ui->peaksBars->setBaseValue(noiseFloor);
    ui->ticks = {1, 2, 3};
    ui->labels = {QCoreApplication::translate("MainWindow", "Baliza A"),
                  QCoreApplication::translate("MainWindow", "Baliza B"),
                  QCoreApplication::translate("MainWindow", "Baliza C")};
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ui->ticks, ui->labels);
    ui->barsPlot->xAxis->setTicker(textTicker);
    ui->barsPlot->xAxis->setSubTicks(false);
    ui->barsPlot->xAxis->setTickLength(0, 3);
    ui->barsPlot->xAxis->setRange(0, 4);
    ui->barsPlot->xAxis->grid()->setVisible(false);

    ui->barsPlot->yAxis->setRange(noiseFloor, 0);
    ui->barsPlot->yAxis->setPadding(5);
    ui->barsPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Potencia"));
    // ui->barsPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->barsPlot->yAxis->grid()->setVisible(true);
    ui->barsPlot->yAxis->grid()->setSubGridVisible(true);

    ui->selectOneFreq->setStyleSheet("background-color: rgba(46, 154, 93, 0.4);");
    ui->selectTwoFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
    ui->selectThreeFreq->setStyleSheet("background-color: rgba(154, 46, 93, 0.4);");
}

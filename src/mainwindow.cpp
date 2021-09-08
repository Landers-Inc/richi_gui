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

unsigned int N_size = 4096;
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
        ui->inputBeaconWidget->beaconTypeA->setText(QCoreApplication::translate("MainWindow", "Baliza A"));
        ui->inputBeaconWidget->beaconTypeB->setText(QCoreApplication::translate("MainWindow", "Baliza B"));
        ui->inputBeaconWidget->beaconTypeC->setText(QCoreApplication::translate("MainWindow", "Baliza C"));
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
        ui->inputBeaconWidget->beaconTypeA->setText(QCoreApplication::translate("MainWindow", "13.75 kHz"));
        ui->inputBeaconWidget->beaconTypeB->setText(QCoreApplication::translate("MainWindow", "14.05 kHz"));
        ui->inputBeaconWidget->beaconTypeC->setText(QCoreApplication::translate("MainWindow", "14.25 kHz"));
        ui->saveLog->setText(QCoreApplication::translate("MainWindow", "Vista avanzada"));
        warningStatus(QCoreApplication::translate("MainWindow", "Status: Vista avanzada seleccionada"));
    }
}

void MainWindow::updateData(QVector<double> const &xSeries, QVector<double> const &ySeries) {
    ui->leftPlot->graph(0)->setData(xSeries, ySeries);
    ui->leftPlot->xAxis->rescale();
}

void MainWindow::updateGPS(
    double const &latitude,
    double const &longitude,
    double const &height,
    std::string const &name,
    unsigned char const &type,
    unsigned char const &status,
    unsigned char const &hor,
    unsigned char const &ver) {
    ui->gpsWidget->gpsName->setText(QString::fromStdString(name));
    ui->gpsWidget->gpsStatus->setText(QString::number(status));
    ui->gpsWidget->gpsMode->setText(QString::number(type));
    ui->gpsWidget->gpsCoordX->setText(QString::number(latitude, 'f', 10));
    ui->gpsWidget->gpsCoordY->setText(QString::number(longitude, 'f', 10));
    ui->gpsWidget->gpsCoordZ->setText(QString::number(height, 'f', 10));
    ui->gpsWidget->gpsAccHor->setText(QString::number(hor));
    ui->gpsWidget->gpsAccVer->setText(QString::number(ver));
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
    QVector<double> peakOneLineY = {power - 5, power + 5};
    ui->rightPlot->graph(1)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateTwoPeak(double freq, double power) {
    ui->peakTwoFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakTwoPowerValue->setText(QString::number(power, 'f', 2));

    peakValues[1] = power - noiseFloor;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {power - 5, power + 5};
    ui->rightPlot->graph(2)->setData(peakOneLineX, peakOneLineY);
}

void MainWindow::updateThreePeak(double freq, double power) {
    ui->peakThreeFreqValue->setText(QString::number(freq, 'f', 1));
    ui->peakThreePowerValue->setText(QString::number(power, 'f', 2));

    peakValues[2] = power - noiseFloor;

    QVector<double> peakOneLineX = {freq, freq};
    QVector<double> peakOneLineY = {power - 5, power + 5};
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

    connect(dataProcessor, &DataProcessor::updateGPSInfo, this, &MainWindow::updateGPS, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::dataReady, this, &MainWindow::updateData, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::fftReady, this, &MainWindow::updateFFT, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::plotData, this, &MainWindow::updatePlots, Qt::QueuedConnection);
    connect(dataProcessor, &DataProcessor::setNoiseFloor, this, &MainWindow::updateNoiseFloor, Qt::QueuedConnection);
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
}

void MainWindow::startProcessing() {
    dataProcessing->start();
    dataLogging->start();
}

void MainWindow::openGPSStatus() {
    if (!ui->gpsWidget->dialogWidget->isVisible()) {
        ui->gpsWidget->dialogWidget->setVisible(true);
        ui->gpsWidget->statusWidget->setVisible(true);
        ui->gpsWidget->statusWidget->activateWindow();
        ui->gpsWidget->statusWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::closeGPSStatus() {
    if (ui->gpsWidget->dialogWidget->isVisible()) {
        ui->gpsWidget->dialogWidget->setVisible(false);
        ui->gpsWidget->statusWidget->setVisible(false);
    }
}

void MainWindow::openBeaconInput() {
    if (stateInstance->getState() == PREBLAST) {
        if (!ui->inputBeaconWidget->dialogInputWidget->isVisible()) {
            ui->inputBeaconWidget->dialogInputWidget->setVisible(true);
            ui->inputBeaconWidget->beaconInputWidget->setVisible(true);
            ui->inputBeaconWidget->beaconTopInputLabel->setText(QCoreApplication::translate("MainWindow", "Ingreso Nueva Baliza") + ": " + QString::number(dataLogger->beaconPreCount + 1));
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
        if (id.toUInt() > dataLogger->beaconPreCount) {
            warningStatus(QCoreApplication::translate("MainWindow", "Status: No puede ingresar baliza no existente"));
        } else {
            bool notRepeated = true;
            for (auto beaconPost : dataLogger->beaconPostData) {
                if ((unsigned int)beaconPost.distance == id.toUInt()) {
                    notRepeated = false;
                    break;
                }
            }
            if (notRepeated) {
                emit logBeacon(id.toDouble(), 0, 0);
                warningStatus(QCoreApplication::translate("MainWindow", "Status: Nueva baliza post-tronadura registrada"));
            } else {
                warningStatus(QCoreApplication::translate("MainWindow", "Status: La baliza ya fue ingresada"));
            }
        }
        ui->foundBeaconWidget->beaconOneFoundText->setText("");
        ui->foundBeaconWidget->dialogFoundWidget->setVisible(false);
        ui->foundBeaconWidget->beaconFoundWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::beaconFoundNotFound() {
    if (ui->foundBeaconWidget->dialogFoundWidget->isVisible()) {
        QString id = ui->foundBeaconWidget->beaconOneFoundText->text();
        if (id.toUInt() > dataLogger->beaconPreCount) {
            warningStatus(QCoreApplication::translate("MainWindow", "Status: No puede ingresar baliza no existente"));
        } else {
            bool notRepeated = true;
            for (auto beaconPost : dataLogger->beaconPostData) {
                if ((unsigned int)beaconPost.distance == id.toUInt()) {
                    notRepeated = false;
                    break;
                }
            }
            if (notRepeated) {
                emit logBeacon(-1, id.toUInt(), 0);
                warningStatus(QCoreApplication::translate("MainWindow", "Status: Nueva baliza post-tronadura registrada"));
            } else {
                warningStatus(QCoreApplication::translate("MainWindow", "Status: La baliza ya fue ingresada"));
            }
        }
        ui->foundBeaconWidget->beaconOneFoundText->setText("");
        ui->foundBeaconWidget->dialogFoundWidget->setVisible(false);
        ui->foundBeaconWidget->beaconFoundWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
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
        emit logBeacon(distance.toDouble(), 0, ui->inputBeaconWidget->beaconTypeSelect);
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
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentDatetime = std::chrono::system_clock::to_time_t(currentTime);

    QString name = ui->nameInputDialog->nameOneInputText->text();
    ui->inputBeaconWidget->beaconOneInputText->setText("");
    QByteArray nameBA = name.toLocal8Bit();
    char *confName = nameBA.data();
    char datetimeString[40];
    std::strftime(datetimeString, sizeof(datetimeString), "%Y-%m-%d %H:%M:%S", std::gmtime(&currentDatetime));
    DataLogger::Configuration conf = {confName, datetimeString, N_size, sampleFrequency};
    emit logConfiguration(conf);
    stateInstance->newLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet(RED_BUTTON);
    ui->selectBeacon->setStyleSheet(RED_BUTTON);
    ui->postblastLog->setStyleSheet(RED_BUTTON);
    ui->beaconFound->setStyleSheet(RED_BUTTON);
}

void MainWindow::warningCancel() {
    if (ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(false);
        ui->warningWidget->warningWidget->setVisible(false);
    }
}

void MainWindow::openAdjust() {
    if (!ui->adjustSpectrum->dialogInputWidget->isVisible()) {
        ui->adjustSpectrum->dialogInputWidget->setVisible(true);
        ui->adjustSpectrum->adjustInputWidget->setVisible(true);
        ui->keyboardInputWidget->setVisible(true);
        ui->adjustSpectrum->adjustInputWidget->activateWindow();
        ui->adjustSpectrum->adjustInputWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::adjustAccept() {
    if (ui->adjustSpectrum->dialogInputWidget->isVisible()) {
        QString max = ui->adjustSpectrum->adjustOneInputText->text();
        QString min = ui->adjustSpectrum->adjustTwoInputText->text();
        double maxVal = max.toDouble();
        double minVal = min.toDouble();
        maxSpectrum = maxVal;
        minSpectrum = minVal;
        ui->rightPlot->yAxis->setRange(minSpectrum, maxSpectrum);
        ui->leftPlot->yAxis->setRange(minSpectrum, maxSpectrum);
        ui->adjustSpectrum->adjustOneInputText->setText(QString::number(maxSpectrum, 'f', 1));
        ui->adjustSpectrum->adjustTwoInputText->setText(QString::number(minSpectrum, 'f', 1));
        ui->adjustSpectrum->dialogInputWidget->setVisible(false);
        ui->adjustSpectrum->adjustInputWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::adjustCancel() {
    if (ui->adjustSpectrum->dialogInputWidget->isVisible()) {
        ui->adjustSpectrum->adjustOneInputText->setText(QString::number(maxSpectrum, 'f', 1));
        ui->adjustSpectrum->adjustTwoInputText->setText(QString::number(minSpectrum, 'f', 1));
        ui->adjustSpectrum->dialogInputWidget->setVisible(false);
        ui->adjustSpectrum->adjustInputWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::dispFrequencyOne() {
    emit setPeakTimeserie(0);
    ui->selectOneFreq->setStyleSheet(GREEN_BUTTON);
    ui->selectTwoFreq->setStyleSheet(RED_BUTTON);
    ui->selectThreeFreq->setStyleSheet(RED_BUTTON);
}

void MainWindow::dispFrequencyTwo() {
    emit setPeakTimeserie(1);
    ui->selectOneFreq->setStyleSheet(RED_BUTTON);
    ui->selectTwoFreq->setStyleSheet(GREEN_BUTTON);
    ui->selectThreeFreq->setStyleSheet(RED_BUTTON);
}

void MainWindow::dispFrequencyThree() {
    emit setPeakTimeserie(2);
    ui->selectOneFreq->setStyleSheet(RED_BUTTON);
    ui->selectTwoFreq->setStyleSheet(RED_BUTTON);
    ui->selectThreeFreq->setStyleSheet(GREEN_BUTTON);
}

void MainWindow::selectBeaconTypeA() {
    ui->inputBeaconWidget->beaconTypeSelect = 0;
    ui->inputBeaconWidget->beaconTypeA->setStyleSheet(GREEN_BUTTON);
    ui->inputBeaconWidget->beaconTypeB->setStyleSheet(RED_BUTTON);
    ui->inputBeaconWidget->beaconTypeC->setStyleSheet(RED_BUTTON);
}

void MainWindow::selectBeaconTypeB() {
    ui->inputBeaconWidget->beaconTypeSelect = 1;
    ui->inputBeaconWidget->beaconTypeA->setStyleSheet(RED_BUTTON);
    ui->inputBeaconWidget->beaconTypeB->setStyleSheet(GREEN_BUTTON);
    ui->inputBeaconWidget->beaconTypeC->setStyleSheet(RED_BUTTON);
}

void MainWindow::selectBeaconTypeC() {
    ui->inputBeaconWidget->beaconTypeSelect = 2;
    ui->inputBeaconWidget->beaconTypeA->setStyleSheet(RED_BUTTON);
    ui->inputBeaconWidget->beaconTypeB->setStyleSheet(RED_BUTTON);
    ui->inputBeaconWidget->beaconTypeC->setStyleSheet(GREEN_BUTTON);
}

void MainWindow::startNewLog() {
    if (!ui->warningWidget->dialogWidget->isVisible()) {
        ui->warningWidget->dialogWidget->setVisible(true);
        ui->warningWidget->warningWidget->setVisible(true);
        ui->warningWidget->warningWidget->activateWindow();
        ui->warningWidget->warningWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::tableLog() {
    if (!ui->beaconTable->dialogInputWidget->isVisible()) {
        unsigned int rowsCount = std::max(dataLogger->beaconPreCount, dataLogger->beaconPostCount);
        for (unsigned int i = 0; i < rowsCount; i++) {
            BeaconTableItem *itemLayout = new BeaconTableItem(ui->beaconTable->tableWidget);
            ui->beaconTable->beaconListLayout->addLayout(itemLayout);
            beaconList.push_back(itemLayout);
        }
        for (unsigned int i = 0; i < dataLogger->beaconPreCount; i++) {
            beaconList[i]->id->setText(QString::number(i + 1));
            beaconList[i]->beaconType->setText(QString((char)(dataLogger->beaconPreData[i].beaconType + 'A')));
            beaconList[i]->preDistance->setText(QString::number(dataLogger->beaconPreData[i].distance, 'f', 1));
            beaconList[i]->prePower->setText(QString::number(20.0 * log10(dataLogger->beaconPreData[i].power), 'f', 1));
            beaconList[i]->preLongitude->setText(QString::number(dataLogger->beaconPreData[i].lngPosition, 'f', 10));
            beaconList[i]->preLatitude->setText(QString::number(dataLogger->beaconPreData[i].latPosition, 'f', 10));
        }
        for (unsigned int i = 0; i < dataLogger->beaconPostCount; i++) {
            int idPost = (int)dataLogger->beaconPostData[i].distance;
            if (idPost != -1) {
                beaconList[idPost - 1]->postId->setText(QString::number(i + 1));
                beaconList[idPost - 1]->assignedId->setText(QString::number(idPost));
                beaconList[idPost - 1]->postPower->setText(QString::number(20.0 * log10(dataLogger->beaconPostData[i].power), 'f', 1));
                beaconList[idPost - 1]->diffNorthDistance->setText(
                    QString::number(
                        measureDistance(dataLogger->beaconPreData[idPost - 1].latPosition,
                                        dataLogger->beaconPreData[idPost - 1].lngPosition,
                                        dataLogger->beaconPostData[i].latPosition,
                                        dataLogger->beaconPostData[i].lngPosition),
                        'f', 1));
                beaconList[idPost - 1]->diffEastDistance->setText(
                    QString::number(
                        measureBearing(dataLogger->beaconPreData[idPost - 1].latPosition,
                                       dataLogger->beaconPreData[idPost - 1].lngPosition,
                                       dataLogger->beaconPostData[i].latPosition,
                                       dataLogger->beaconPostData[i].lngPosition),
                        'f', 1));
                beaconList[idPost - 1]->diffHeight->setText(
                    QString::number(
                        measureHeight(dataLogger->beaconPreData[idPost - 1].hgtPosition,
                                      dataLogger->beaconPostData[i].hgtPosition),
                        'f', 1));
                beaconList[idPost - 1]->postLongitude->setText(QString::number(dataLogger->beaconPostData[i].lngPosition, 'f', 10));
                beaconList[idPost - 1]->postLatitude->setText(QString::number(dataLogger->beaconPostData[i].latPosition, 'f', 10));
            } else {
                int idNotFound = (int)dataLogger->beaconPostData[i].power;
                beaconList[idNotFound - 1]->postId->setText(QString::number(i + 1));
                beaconList[idNotFound - 1]->assignedId->setText(QString::number(-1));
            }
        }
        ui->beaconTable->dialogInputWidget->setVisible(true);
        ui->beaconTable->tableWidget->setVisible(true);
        ui->keyboardInputWidget->setVisible(true);
        ui->beaconTable->tableWidget->activateWindow();
        ui->beaconTable->tableWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::openInputName() {
    if (!ui->nameInputDialog->dialogInputWidget->isVisible()) {
        ui->nameInputDialog->dialogInputWidget->setVisible(true);
        ui->nameInputDialog->nameInputWidget->setVisible(true);
        ui->keyboardInputWidget->setVisible(true);
        ui->nameInputDialog->nameInputWidget->activateWindow();
        ui->nameInputDialog->nameInputWidget->setFocus(Qt::ActiveWindowFocusReason);
    }
}

void MainWindow::closeInputName() {
    if (ui->nameInputDialog->dialogInputWidget->isVisible()) {
        warningAccept();
        ui->nameInputDialog->dialogInputWidget->setVisible(false);
        ui->nameInputDialog->nameInputWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
        if (ui->warningWidget->dialogWidget->isVisible()) {
            ui->warningWidget->dialogWidget->setVisible(false);
            ui->warningWidget->warningWidget->setVisible(false);
        }
    }
}

void MainWindow::tableCancel() {
    if (ui->beaconTable->dialogInputWidget->isVisible()) {
        for (unsigned int i = 0; i < beaconList.size(); i++) {
            ui->beaconTable->beaconListLayout->removeItem(beaconList[i]);
            QLayoutItem *child;
            while ((child = beaconList[i]->takeAt(0)) != 0) {
                beaconList[i]->removeItem(child);
                child->widget()->hide();
                delete child;
            }
            delete beaconList[i];
        }
        ui->beaconTable->beaconListLayout->update();

        beaconList.clear();
        ui->beaconTable->dialogInputWidget->setVisible(false);
        ui->beaconTable->tableWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
    }
}

void MainWindow::tableGenerate() {
    if (ui->beaconTable->dialogInputWidget->isVisible()) {
        auto currentTime = std::chrono::system_clock::now();
        std::time_t currentDatetime = std::chrono::system_clock::to_time_t(currentTime);

        // char datetimeString[100];
        QString name = ui->nameInputDialog->nameOneInputText->text();
        ui->inputBeaconWidget->beaconOneInputText->setText("");
        QByteArray nameBA = name.toLocal8Bit();
        const char *path = "/home/pi/";
        char filename[200] = {0};
        dataLogger->getConfigurationName(filename);
        const char *extension = ".csv";
        char completeName[200] = {0};
        strcpy(completeName, path);
        strcat(completeName, filename);
        strcat(completeName, extension);
        // std::strftime(datetimeString, sizeof(datetimeString), "/home/pi/table_%Y%m%d_%H%M%S.csv", std::gmtime(&currentDatetime));
        // std::strftime(datetimeString, sizeof(datetimeString), completeName, std::gmtime(&currentDatetime));
        std::ofstream file(completeName);
        QLayoutItem *child;
        // We write the headers row
        for (int i = 0; i < ui->beaconTable->beaconLabelsLayout->count(); ++i) {
            child = ui->beaconTable->beaconLabelsLayout->itemAt(i);
            QLabel *labelTemp = (QLabel *)child->widget();
            file << labelTemp->text().toStdString() << ",";
        }
        file << "Altura Pre,";
        file << "Altura Post";
        file << std::endl;
        for (unsigned int j = 0; j < beaconList.size(); j++) {
            for (int i = 0; i < beaconList[j]->count(); ++i) {
                child = beaconList[j]->itemAt(i);
                QObject *objTemp = (QObject *)child->widget();
                if (QLabel *labelTemp = qobject_cast<QLabel *>(objTemp)) {
                    file << labelTemp->text().toStdString() << ",";
                } else if (QLineEdit *lineTemp = qobject_cast<QLineEdit *>(objTemp)) {
                    file << lineTemp->text().toStdString() << ",";
                }
            }
            file << std::fixed << std::setprecision(10) << dataLogger->beaconPreData[j].hgtPosition << ",";
            int iId = beaconList[j]->postId->text().toInt();
            if (iId != 0) {
                file << std::fixed << std::setprecision(10) << dataLogger->beaconPostData[iId - 1].hgtPosition;
            }
            file << std::endl;
        }
        file.close();
    }
}

void MainWindow::tableUpdate() {
    if (ui->beaconTable->dialogInputWidget->isVisible()) {
        bool checkRepeated = false;
        for (unsigned int i = 0; i < dataLogger->beaconPreCount; i++) {
            for (unsigned int j = 0; j < dataLogger->beaconPreCount; j++) {
                int iId = beaconList[i]->postId->text().toInt();
                int jId = beaconList[j]->postId->text().toInt();
                if (i != j && iId != 0 && jId != 0) {
                    int iAssignedId = beaconList[i]->assignedId->text().toInt();
                    int jAssignedId = beaconList[j]->assignedId->text().toInt();
                    if (iAssignedId == jAssignedId && iAssignedId != -1) checkRepeated = true;
                }
            }
        }

        bool checkGreater = false;
        for (unsigned int i = 0; i < dataLogger->beaconPreCount; i++) {
            signed int iId = beaconList[i]->assignedId->text().toInt();
            if (iId >= (signed int)dataLogger->beaconPreCount) checkGreater = true;
        }

        bool checkNegative = false;
        for (unsigned int i = 0; i < dataLogger->beaconPreCount; i++) {
            double depth = beaconList[i]->preDistance->text().toDouble();
            if (depth < 0) checkNegative = true;
        }

        if (!checkRepeated && !checkGreater && !checkNegative) {
            for (unsigned int i = 0; i < dataLogger->beaconPreCount; i++) {
                double depth = beaconList[i]->preDistance->text().toDouble();
                if (depth != 0.0) {
                    dataLogger->beaconPreData[i].distance = depth;
                } else {
                    dataLogger->deleteBeaconData(dataLogger->beaconPreData[i]);
                    bool ok;
                    int postId = beaconList[i]->postId->text().toInt(&ok, 10);
                    if (ok) {
                        dataLogger->deleteBeaconData(dataLogger->beaconPostData[postId - 1]);
                    }
                }
            }
            for (unsigned int i = 0; i < beaconList.size(); i++) {
                bool ok;
                int postId = beaconList[i]->postId->text().toInt(&ok, 10);
                if (ok) {
                    if (postId > 0) {
                        double assignedId = beaconList[i]->assignedId->text().toDouble();
                        if (assignedId == 0.0) {
                            dataLogger->deleteBeaconData(dataLogger->beaconPostData[postId - 1]);
                        } else if (dataLogger->beaconPostData[postId - 1].distance == -1.0 && assignedId != -1.0) {
                            dataLogger->beaconPostData[postId - 1].power = assignedId;
                            dataLogger->beaconPostData[postId - 1].frequency = assignedId;
                        } else {
                            if (dataLogger->beaconPostData[postId - 1].distance != -1.0 && assignedId == -1.0) {
                                dataLogger->beaconPostData[postId - 1].power = dataLogger->beaconPostData[postId - 1].distance;
                                dataLogger->beaconPostData[postId - 1].frequency = dataLogger->beaconPostData[postId - 1].distance;
                                dataLogger->beaconPostData[postId - 1].distance = -1;
                            } else {
                                dataLogger->beaconPostData[postId - 1].distance = assignedId;
                            }
                        }
                    }
                }
            }
            dataLogger->updateBeaconData();
        }

        for (unsigned int i = 0; i < beaconList.size(); i++) {
            ui->beaconTable->beaconListLayout->removeItem(beaconList[i]);
            QLayoutItem *child;
            while ((child = beaconList[i]->takeAt(0)) != 0) {
                beaconList[i]->removeItem(child);
                child->widget()->hide();
                delete child;
            }
            delete beaconList[i];
        }
        ui->beaconTable->beaconListLayout->update();

        beaconList.clear();
        ui->beaconTable->dialogInputWidget->setVisible(false);
        ui->beaconTable->tableWidget->setVisible(false);
        ui->keyboardInputWidget->setVisible(false);
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
    ui->preblastLog->setStyleSheet(GREEN_BUTTON);
    ui->selectBeacon->setStyleSheet(GREEN_BUTTON);
    ui->postblastLog->setStyleSheet(RED_BUTTON);
    ui->beaconFound->setStyleSheet(RED_BUTTON);
    ui->standbyLog->setStyleSheet(RED_BUTTON);
    ui->standbyLog->setText(QCoreApplication::translate("MainWindow", "Registro activo"));
}

void MainWindow::startNewPostblastLog() {
    stateInstance->postblastLog();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet(RED_BUTTON);
    ui->selectBeacon->setStyleSheet(RED_BUTTON);
    ui->postblastLog->setStyleSheet(GREEN_BUTTON);
    ui->beaconFound->setStyleSheet(GREEN_BUTTON);
    ui->standbyLog->setStyleSheet(RED_BUTTON);
    ui->standbyLog->setText(QCoreApplication::translate("MainWindow", "Registro activo"));
}

void MainWindow::standbyLog() {
    stateInstance->gotoIdle();
    ui->statusLabel->setText(stateInstance->stateString[stateInstance->getState()]);
    ui->preblastLog->setStyleSheet(RED_BUTTON);
    ui->selectBeacon->setStyleSheet(RED_BUTTON);
    ui->postblastLog->setStyleSheet(RED_BUTTON);
    ui->beaconFound->setStyleSheet(RED_BUTTON);
    ui->standbyLog->setStyleSheet(GREEN_BUTTON);
    ui->standbyLog->setText(QCoreApplication::translate("MainWindow", "Registro inactivo"));
}

void MainWindow::selectTimeAxis() {
    ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Time [seconds]"));
    ui->selectTimeAxis->setStyleSheet(GREEN_BUTTON);
    ui->selectDistanceAxis->setStyleSheet(RED_BUTTON);
    emit setViewAxis(0);
    ui->timeDistance = 0;
}

void MainWindow::selectDistanceAxis() {
    ui->leftPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Distance [meters]"));
    ui->selectTimeAxis->setStyleSheet(RED_BUTTON);
    ui->selectDistanceAxis->setStyleSheet(GREEN_BUTTON);
    emit setViewAxis(1);
    ui->timeDistance = 1;
}

void MainWindow::connectButtons() {
    // Close and Shutdown button
    connect(ui->closeShutdown, &QPushButton::released, this, &QMainWindow::close);
    connect(ui->switchLanguage, &QPushButton::released, this, &MainWindow::switchLanguage);
    connect(ui->adjustButton, &QPushButton::released, this, &MainWindow::openAdjust);
    connect(ui->saveLog, &QPushButton::released, this, &MainWindow::switchView);
    //
    connect(ui->selectTimeAxis, &QPushButton::released, this, &MainWindow::selectTimeAxis);
    connect(ui->selectDistanceAxis, &QPushButton::released, this, &MainWindow::selectDistanceAxis);

    connect(ui->gpsStatus, &QPushButton::released, this, &MainWindow::openGPSStatus);
    connect(ui->gpsWidget->statusClose, &QPushButton::released, this, &MainWindow::closeGPSStatus);

    connect(ui->selectBeacon, &QPushButton::released, this, &MainWindow::openBeaconInput);
    connect(ui->beaconFound, &QPushButton::released, this, &MainWindow::openBeaconFound);
    connect(ui->selectOneFreq, &QPushButton::released, this, &MainWindow::dispFrequencyOne);
    connect(ui->selectTwoFreq, &QPushButton::released, this, &MainWindow::dispFrequencyTwo);
    connect(ui->selectThreeFreq, &QPushButton::released, this, &MainWindow::dispFrequencyThree);

    connect(ui->startLog, &QPushButton::released, this, &MainWindow::startNewLog);
    connect(ui->preblastLog, &QPushButton::released, this, &MainWindow::startNewPreblastLog);
    connect(ui->postblastLog, &QPushButton::released, this, &MainWindow::startNewPostblastLog);
    connect(ui->standbyLog, &QPushButton::released, this, &MainWindow::standbyLog);
    connect(ui->tableLog, &QPushButton::released, this, &MainWindow::tableLog);

    connect(ui->inputBeaconWidget->beaconInputAccept, &QPushButton::released, this, &MainWindow::beaconInputAccept);
    connect(ui->inputBeaconWidget->beaconInputCancel, &QPushButton::released, this, &MainWindow::beaconInputCancel);
    connect(ui->inputBeaconWidget->beaconTypeA, &QPushButton::released, this, &MainWindow::selectBeaconTypeA);
    connect(ui->inputBeaconWidget->beaconTypeB, &QPushButton::released, this, &MainWindow::selectBeaconTypeB);
    connect(ui->inputBeaconWidget->beaconTypeC, &QPushButton::released, this, &MainWindow::selectBeaconTypeC);

    connect(ui->foundBeaconWidget->beaconFoundAccept, &QPushButton::released, this, &MainWindow::beaconFoundAccept);
    connect(ui->foundBeaconWidget->beaconFoundNotFound, &QPushButton::released, this, &MainWindow::beaconFoundNotFound);
    connect(ui->foundBeaconWidget->beaconFoundCancel, &QPushButton::released, this, &MainWindow::beaconFoundCancel);

    connect(ui->warningWidget->warningAccept, &QPushButton::released, this, &MainWindow::openInputName);
    connect(ui->warningWidget->warningCancel, &QPushButton::released, this, &MainWindow::warningCancel);

    connect(ui->adjustSpectrum->adjustInputAccept, &QPushButton::released, this, &MainWindow::adjustAccept);
    connect(ui->adjustSpectrum->adjustInputCancel, &QPushButton::released, this, &MainWindow::adjustCancel);

    connect(ui->beaconTable->updateButton, &QPushButton::released, this, &MainWindow::tableUpdate);
    connect(ui->beaconTable->generateButton, &QPushButton::released, this, &MainWindow::tableGenerate);
    connect(ui->beaconTable->cancelButton, &QPushButton::released, this, &MainWindow::tableCancel);

    connect(ui->nameInputDialog->nameInputAccept, &QPushButton::released, this, &MainWindow::closeInputName);
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
    ui->inputBeaconWidget->setCursor(Qt::BlankCursor);
    ui->foundBeaconWidget->setCursor(Qt::BlankCursor);
    ui->warningWidget->setCursor(Qt::BlankCursor);
    ui->beaconTable->setCursor(Qt::BlankCursor);

    ui->rightPlot->setBackground(QBrush(QColor(0xDD, 0xDD, 0xDD), Qt::SolidPattern));
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->addGraph();
    ui->rightPlot->xAxis->setLabel(QCoreApplication::translate("MainWindow", "Frequency"));
    ui->rightPlot->yAxis->setLabel(QCoreApplication::translate("MainWindow", "Power"));
    ui->rightPlot->xAxis->setRange(0, sampleFrequency / 2);
    ui->rightPlot->yAxis->setRange(minSpectrum, maxSpectrum);
    ui->rightPlot->graph(0)->setPen(QPen(Qt::blue));
    ui->rightPlot->graph(1)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(2)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));
    ui->rightPlot->graph(3)->setPen(QPen(Qt::black, 1.0, Qt::DashLine));

    ui->textLabel = new QCPItemText(ui->rightPlot);
    ui->textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignHCenter);
    ui->textLabel->setPadding(QMargins(5, 5, 5, 5));
    ui->textLabel->position->setType(QCPItemPosition::ptAxisRectRatio);
    ui->textLabel->position->setCoords(0.25, 0);
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
    ui->leftPlot->yAxis->setRange(minSpectrum, maxSpectrum);
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

    ui->selectOneFreq->setStyleSheet(GREEN_BUTTON);
    ui->selectTwoFreq->setStyleSheet(RED_BUTTON);
    ui->selectThreeFreq->setStyleSheet(RED_BUTTON);
}

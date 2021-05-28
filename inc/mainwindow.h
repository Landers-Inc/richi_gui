#pragma once

#include <QDebug>
#include <QMainWindow>
#include <QThread>
#include <QVirtualKeyboardInputEngine>

#include "datalogger.h"
#include "dataprocessor.h"
#include "datareader.h"
#include "qcustomplot.h"
#include "statemachine.h"
#include "usbadc.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupGUI();

   private:
    void connectButtons();
    Ui::MainWindow *ui;
    QThread dataProcessing;
    QThread dataAcquiring;
    QThread dataLogging;
    std::thread *startPeripherals;
    DataProcessor *dataProcessor;
    DataReader *dataAcquisition;
    DataLogger *dataLogger;
    void startThreads();
    int dispFreqPlot;
    bool simpleView = false;
   signals:
    void peripheralsReady(double freq, double power);
    void setPeakTimeserie(int disp);
    // Qt Signal used to log a configuration
    void logConfiguration(DataLogger::Configuration const &conf);
    // Qt Signal used to log a timestamp
    void logTimestamp(DataLogger::TimeData const &time);
    // Qt Signal used to log a beacon
    void logBeacon(DataLogger::BeaconData const &beacon);
    // Qt Signal used to log a spectrum
    void logSpectrum(DataLogger::SpectrumData const &spectrum);
    // Qt Signal used to log a peak
    void logPeaks(DataLogger::PeaksData const &peaks);
   public slots:
    void warningStatus(QString message);
    void warningDialog(QString message);
    void updateData(QVector<double> const &xSeries, QVector<double> const &ySeries);
    void updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries);
    void updateOnePeak(double freq, double power);
    void updateTwoPeak(double freq, double power);
    void updateThreePeak(double freq, double power);
    void updatePlots();
    void openBeaconInput();
    void beaconFoundLog();
    void beaconAccept();
    void beaconCancel();
    void dispFrequencyOne();
    void dispFrequencyTwo();
    void dispFrequencyThree();
    void startNewLog();
    void startNewPreblastLog();
    void startNewPostblastLog();
    void switchView();
};

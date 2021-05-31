#pragma once

#include <QMainWindow>
#include <QThread>
#include <QVector>

#include "datalogger.h"
#include "dataprocessor.h"
#include "qcustomplot.h"
#include "statemachine.h"

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
    QThread *dataProcessing;
    QThread *dataLogging;
    std::thread *startPeripherals;
    DataProcessor *dataProcessor;
    DataLogger *dataLogger;
    StateMachine *stateInstance;
    void startThreads();
    int dispFreqPlot;
    bool simpleView = false;
    QVector<double> peakValues;
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
    // Qt Slot used to change Status label
    void warningStatus(QString message);
    // Qt Slot used to update timeserie data
    void updateData(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Slot used to update FFT data
    void updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Slot used to update Peak
    void updateOnePeak(double freq, double power);
    // Qt Slot used to
    void updateTwoPeak(double freq, double power);
    // Qt Slot used to
    void updateThreePeak(double freq, double power);
    // Qt Slot used to
    void updatePlots();
    // Qt Slot used to;
    void openBeaconInput();
    // Qt Slot used to
    void beaconFoundLog();
    // Qt Slot used to
    void beaconAccept();
    // Qt Slot used to
    void beaconCancel();
    // Qt Slot used to
    void warningAccept();
    // Qt Slot used to
    void warningCancel();
    // Qt Slot used to
    void dispFrequencyOne();
    // Qt Slot used to
    void dispFrequencyTwo();
    // Qt Slot used to
    void dispFrequencyThree();
    // Qt Slot used to
    void startNewLog();
    // Qt Slot used to
    void startNewPreblastLog();
    // Qt Slot used to
    void startNewPostblastLog();
    // Qt Slot used to
    void switchView();
};

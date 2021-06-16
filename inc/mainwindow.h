#pragma once

#include <QMainWindow>
#include <QThread>
#include <QVector>

#include "datalogger.h"
#include "dataprocessor.h"
#include "qcustomplot.h"
#include "statemachine.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
typedef enum Language {
    ENGLISH = 0,
    SPANISH
} Language;
class MainWindow;
}  // namespace Ui
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupGUI();
    void updateGUI();

   private:
    void connectButtons();
    Ui::Language *appLanguage;
    Ui::MainWindow *ui;
    QThread *dataProcessing;
    QThread *dataLogging;
    std::thread *startPeripherals;
    DataProcessor *dataProcessor;
    DataLogger *dataLogger;
    StateMachine *stateInstance;
    void startThreads();
    QVector<double> peakValues;
    double noiseFloor = -120.0;
   signals:
    void peripheralsReady(double freq, double power);
    void setPeakTimeserie(int disp);
    void setViewAxis(int axis);
    // Qt Signal used to log a configuration
    void logConfiguration(DataLogger::Configuration const &conf);
    // Qt Signal used to log a beacon
    void logBeacon(double distance);
   public slots:
    // Qt Slot used to change Status label
    void warningStatus(QString message);
    // Qt Slot used to update timeserie data
    void updateData(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Slot used to update FFT data
    void updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries);
    // Qt Slot used to update Noise Floor
    void updateNoiseFloor(double noiseFloor);
    // Qt Slot used to update Peak
    void updateOnePeak(double freq, double power);
    // Qt Slot used to
    void updateTwoPeak(double freq, double power);
    // Qt Slot used to
    void updateThreePeak(double freq, double power);
    // Qt Slot used to
    void updatePlots();
    // Qt Slot used to
    void selectTimeAxis();
    // Qt Slot used to
    void selectDistanceAxis();
    // Qt Slot used to;
    void openBeaconInput();
    // Qt Slot used to;
    void openBeaconFound();
    // Qt Slot used to
    void beaconFoundAccept();
    // Qt Slot used to
    void beaconFoundNotFound();
    // Qt Slot used to
    void beaconFoundCancel();
    // Qt Slot used to
    void beaconInputAccept();
    // Qt Slot used to
    void beaconInputCancel();
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
    void standbyLog();
    // Qt Slot used to
    void switchView();
    // Qt Slot used to
    void switchLanguage();
};

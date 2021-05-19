#pragma once

#include <QDebug>
#include <QMainWindow>
#include <QThread>

#include "dataprocessor.h"
#include "datareader.h"
#include "qcustomplot.h"
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
    std::thread *startPeripherals;
    DataProcessor *dataProcessor;
    DataReader *dataAcquisition;
    void startThreads();
   signals:
    void peripheralsReady(double freq, double power);
   public slots:
    void updateData(QVector<double> const &xSeries, QVector<double> const &ySeries);
    void updateFFT(QVector<double> const &xSeries, QVector<double> const &ySeries);
    void updateOnePeak(double freq, double power);
    void updateTwoPeak(double freq, double power);
    void updateThreePeak(double freq, double power);
    void updatePlots();
    void openBeaconInput();
};

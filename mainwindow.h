#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include "qcustomplot.h"
#include "myobject.h"

static int N_size = 44100;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QThread cThread;
signals:
    void operate();
public slots:
    void plotData(QVector<double> const &xSeries,QVector<double> const &ySeries);
    void plotFFT(QVector<double> const &xSeries,QVector<double> const &ySeries);
};

#endif // MAINWINDOW_H

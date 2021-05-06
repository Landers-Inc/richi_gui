#include <QtCore>
#include <QObject>
#include <QVector>
#include <QThread>
#include <QPushButton>
#include <cmath>
#include <iterator>
#include <random>

#include "qcustomplot.h"
#include "fftw3.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myobject.h"

void MainWindow::plotData(QVector<double> const &xSeries,QVector<double> const &ySeries){
    QCustomPlot *leftPlot = ui->leftPlot;
    leftPlot->graph(0)->setData(xSeries, ySeries);
    leftPlot->xAxis->setLabel("x");
    leftPlot->yAxis->setLabel("y");
    leftPlot->xAxis->setRange(0, 1);
    leftPlot->yAxis->setRange(-1, 1);
    leftPlot->replot();
}

void MainWindow::plotFFT(QVector<double> const &xSeries,QVector<double> const &ySeries){
    QCustomPlot *rightPlot = ui->rightPlot;
    rightPlot->graph(0)->setData(xSeries, ySeries);
    rightPlot->xAxis->setLabel("x");
    rightPlot->yAxis->setLabel("y");
    rightPlot->xAxis->setRange(0, N_size/2);
    rightPlot->yAxis->setRange(-75, 50);
    rightPlot->replot();
    emit operate();
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow){
    qRegisterMetaType<QVector<double>>( "QVector<double>" );
    ui->setupUi(this);
    ui->rightPlot->addGraph();
    ui->leftPlot->addGraph();

    MyObject *cObject = new MyObject;
    cObject->moveToThread(&cThread);
    connect(&cThread, &QThread::finished, cObject, &QThread::deleteLater);
    connect(this, &MainWindow::operate, cObject, &MyObject::doData);
    connect(cObject, &MyObject::dataReady, this, &MainWindow::plotData);
    connect(cObject, &MyObject::fftReady, this, &MainWindow::plotFFT);
    connect(ui->select_disp_freq, &QPushButton::clicked, cObject, &MyObject::doData);
    cThread.start();
}

MainWindow::~MainWindow(){
    cThread.quit();
    cThread.wait();
    delete ui;
}


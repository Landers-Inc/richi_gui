#include <errno.h>    // Error integer and strerror() function
#include <fcntl.h>    // Contains file controls like O_RDWR
#include <termios.h>  // Contains POSIX terminal control definitions
#include <unistd.h>   // write(), read(), close()
#include <wiringSerial.h>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "mainwindow.h"

int main(int argc, char* argv[]) {
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "richikb");
    qputenv("QT_QPA_EGLFS_HIDECURSOR", "1");

    QApplication a(argc, argv);

    QQmlApplicationEngine engine;
    engine.addImportPath(":/resources");

    qRegisterMetaType<std::string>("std::string");
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<std::vector<double>>("std::vector<double>");
    qRegisterMetaType<DataLogger::TimeData>("DataLogger::TimeData");
    qRegisterMetaType<DataLogger::PeaksData>("DataLogger::PeaksData");
    qRegisterMetaType<DataLogger::BeaconData>("DataLogger::BeaconData");
    qRegisterMetaType<DataLogger::SpectrumData>("DataLogger::SpectrumData");
    qRegisterMetaType<DataLogger::Configuration>("DataLogger::Configuration");

    MainWindow w;
    w.show();
    w.setupGUI();
    w.startProcessing();
    return a.exec();
}

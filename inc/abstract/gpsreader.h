#pragma once

#include <QObject>
#include <iostream>
#include <string>

// Abstract class for gps acquisition
class GPSReader : public QObject {
    Q_OBJECT
   public:
    //
    std::string gpsName;
    // Device descriptor
    int fd;
    // Vector to store time data
    double latValue;
    // Vector to store converted data
    double lngValue;
    // Vector to store converted data
    double hgtValue;
    // Vector to store time data
    double gpsTime;
    // Vector to store converted data
    double gpsSV;
    //
    unsigned char gpsNumSV = 0;
    //
    unsigned char gpsFixType = 0;
    //
    unsigned char gpsFixStatus = 0;
    //
    unsigned int gpsAccHor = 0;
    //
    unsigned int gpsAccVer = 0;
    // Loop boolean control
    bool running = true;
    // Class constructor
    explicit GPSReader(QObject *parent = 0) : QObject(parent) {
        std::cout << "Starting GPSReader instance" << std::endl;
    };
    // Class destructor
    virtual ~GPSReader() {
        std::cout << "Closing GPSReader instance" << std::endl;
    };
   signals:
    // Qt Signal used to transfer data to DataProcessor thread
    virtual void dataReady(
        double const &latitude,
        double const &longitude,
        double const &height,
        std::string const &name,
        unsigned char const &type,
        unsigned char const &status,
        unsigned char const &hor,
        unsigned char const &ver);
   public slots:
    // Qt Slot used to
    virtual void run() = 0;
    void quit() {
        running = false;
    };
};

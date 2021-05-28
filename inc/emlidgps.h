#pragma once

#include <wiringSerial.h>

#include <QThread>
#include <chrono>
#include <iostream>

class EMLIDGPS : public QThread {
    Q_OBJECT
   public:
    // Static object to store the singleton instance
    static EMLIDGPS *instance;
    // Class constructor
    EMLIDGPS();
    // Class destructor
    ~EMLIDGPS();
    // Device descriptor
    int fd;
    // Vector to store time data
    double latValue;
    // Vector to store converted data
    double lngValue;
    // Vector to store time data
    double gpsTime;
    // Vector to store converted data
    double gpsSV;
    // The GPSReader object is created when getting the object's instance
    static EMLIDGPS *getInstance(){
        if (!instance) instance = new EMLIDGPS;
        return instance;
    };
    void run() override;
   signals:
    // Qt Signal used to transfer data to DataProcessor thread
    virtual void dataReady(double const &latitude, double const &longitude);
   public slots:
    void getData();
};
#pragma once

#include <wiringSerial.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "abstract/gpsreader.h"

class EMLIDGPS : public GPSReader {
    Q_OBJECT
   public:
    enum ERBID {
        VER = 1,
        POS,
        STAT,
        DOPS,
        VEL,
        SVI,
        RTK
    };
    // Class constructor
    EMLIDGPS();
    // Class destructor
    ~EMLIDGPS() override;
   public slots:
    // Qt Slot used to run GPS reading process
    void run() override;
};
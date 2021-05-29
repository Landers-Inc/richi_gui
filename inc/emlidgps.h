#pragma once

#include <wiringSerial.h>

#include <chrono>
#include <iostream>
#include <thread>

#include "abstract/gpsreader.h"

class EMLIDGPS : public GPSReader {
    Q_OBJECT
   public:
    // Class constructor
    EMLIDGPS();
    // Class destructor
    ~EMLIDGPS();
   public slots:
    // Qt Slot used to run GPS reading process
    void run() override;
};
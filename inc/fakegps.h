#pragma once

#include <QThread>
#include <QTimer>
#include <chrono>
#include <iostream>
#include <thread>

#include "abstract/gpsreader.h"

class FakeGPS : public GPSReader {
    Q_OBJECT
   private:
    QTimer *fakeTimer;
    QThread *fakeThread;

   public:
    // Class constructor
    FakeGPS();
    // Class destructor
    ~FakeGPS() override;
   public slots:
    // Qt Slot used to run GPS reading process
    void run() override;
};
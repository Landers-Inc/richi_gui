#include "fakegps.h"

FakeGPS::FakeGPS() {
    latValue = 0;
    lngValue = 0;
    fakeTimer = new QTimer;
    fakeTimer->setInterval(1000);
    fakeThread = new QThread();
    fakeTimer->moveToThread(fakeThread);
    connect(fakeTimer, &QTimer::timeout, this, [this] { emit dataReady(latValue, lngValue); });
    connect(fakeThread, &QThread::started, fakeTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
};

FakeGPS::~FakeGPS() {
    std::cout << "Closed GPS Serial connection" << std::endl;
};

void FakeGPS::run() {
    fakeThread->start();
}
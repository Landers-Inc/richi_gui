#include "fakegps.h"

FakeGPS::FakeGPS() {
    distribution = std::normal_distribution<double>(0.0, 0.000002);
    latValue = 0;
    lngValue = 0;
    hgtValue = 0;
    fakeTimer = new QTimer;
    fakeTimer->setInterval(1000);
    fakeThread = new QThread();
    fakeTimer->moveToThread(fakeThread);
    connect(fakeTimer, &QTimer::timeout, this,
            [this] {
                latValue = distribution(generator);
                lngValue = distribution(generator);
                hgtValue = distribution(generator);
                emit dataReady(latValue, lngValue, hgtValue);
            });
    connect(fakeThread, &QThread::started, fakeTimer, static_cast<void (QTimer::*)()>(&QTimer::start));
};

FakeGPS::~FakeGPS() {
    std::cout << "Closed GPS Serial connection" << std::endl;
};

void FakeGPS::run() {
    fakeThread->start();
}
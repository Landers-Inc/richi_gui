#pragma once

#include <portaudio.h>

#include <QObject>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

class AudioPlayer : public QObject {
    Q_OBJECT
   private:
    // Buffer size to process data
    int dataSize;
    // Sample frequency for data acquisition
    double sampleFrequency;

    double period;
    PaStream *stream;

    bool open();
    bool close();
    bool start();
    bool stop();

    int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                         unsigned long framesPerBuffer,
                         const PaStreamCallbackTimeInfo *timeInfo,
                         PaStreamCallbackFlags statusFlags);
    void paStreamFinishedMethod();

   public:
    AudioPlayer(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0);
    ~AudioPlayer();

    static int paCallback(const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo *timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData);

    static void paStreamFinished(void *userData);
   public slots:
    void changePeriod(double newPeriod);
    void startStream();
};

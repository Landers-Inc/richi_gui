//
// Created by lander on 08-01-20.
//

#pragma once

#include <iostream>
#include <random>

#include <portaudio.h>
#include "dataacquisition.h"

class USBADC : public DataAcquisition{
    Q_OBJECT
private:
    std::default_random_engine generator_amp_noise;
    std::default_random_engine generator_freq_noise;
    PaStream * stream;

    bool open();
    bool close();
    bool start();
    bool stop();

    int paCallbackMethod(const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags);
    void paStreamFinishedMethod();
public:
    USBADC(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0);
    ~USBADC();

    static int paCallback( const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData );

    static void paStreamFinished(void* userData);
public slots:
    void getData() Q_DECL_OVERRIDE;
};

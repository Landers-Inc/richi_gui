//
// Created by lander on 08-01-20.
//

#include "usbadc.h"

USBADC::USBADC(int dataSizeArg, double sampleFrequencyArg, QObject *parent) : DataAcquisition(dataSizeArg, sampleFrequencyArg, parent){
    this->open();
    this->start();
};

USBADC::~USBADC(){
    this->stop();
    this->close();
};

bool USBADC::open(){
    PaError err;
    std::cout
        << "PortAudio Test: output sine wave. SR = " << sampleFrequency
        << ", BufSize = " << dataSize
        << std::endl;

    err = Pa_Initialize();
    if( err != paNoError ) return false;

    PaStreamParameters outputParameters;

    int numDevices;
    numDevices = Pa_GetDeviceCount();
    if( numDevices < 0 ) {
        printf( "ERROR: Pa_CountDevices returned 0x%x\n", numDevices );
        err = numDevices;
    }

    const PaDeviceInfo *deviceInfo;
    int deviceIndex = 0;

    for(deviceIndex = 0; deviceIndex < numDevices; deviceIndex++ ) {
        deviceInfo = Pa_GetDeviceInfo(deviceIndex);
        const std::string name(deviceInfo->name);
        if(name.find("USB") != std::string::npos) break;
    }

    outputParameters.device = deviceIndex;
    if (outputParameters.device == paNoDevice) return false;

    outputParameters.channelCount = 1;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    // In case Alsa fails at the beginning, try several times
    do{
        err = Pa_OpenStream(
            &stream,
            &outputParameters,
            nullptr,
            sampleFrequency,
            dataSize,
            paClipOff,
            &USBADC::paCallback,
            this
        );
    }while(err != paNoError);

    err = Pa_SetStreamFinishedCallback(stream, &USBADC::paStreamFinished);
    if (err != paNoError){
        Pa_CloseStream( stream );
        stream = nullptr;
        return false;
    }
    return true;
}

bool USBADC::close(){
    if (stream == nullptr)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = nullptr;

    return (err == paNoError);
}

bool USBADC::start(){
    if (stream == nullptr)
        return false;
    PaError err = Pa_StartStream(stream);

    return (err == paNoError);
}

bool USBADC::stop(){
    if (stream == nullptr)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

int USBADC::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags){
    float *out = (float*)outputBuffer;
    float *in = (float*)inputBuffer;
    unsigned long i;

    (void) timeInfo;
    (void) statusFlags;
    (void) inputBuffer;

    for(i = 0; i < framesPerBuffer; i++) amplitudeData[i] = *in++;

    this->getData();

    return paContinue;
}

int USBADC::paCallback(const void *inputBuffer, void *outputBuffer,
                     unsigned long framesPerBuffer,
                     const PaStreamCallbackTimeInfo* timeInfo,
                     PaStreamCallbackFlags statusFlags,
                     void *userData ){
    return ((USBADC*)userData)->paCallbackMethod(inputBuffer, outputBuffer,
        framesPerBuffer,
        timeInfo,
        statusFlags);
}

void USBADC::paStreamFinishedMethod(){
    printf( "Stream Completed.\n");
}

void USBADC::paStreamFinished(void* userData){
    return ((USBADC*)userData)->paStreamFinishedMethod();
}

void USBADC::getData() {
    // Let's generate a cosine wave with white gaussian noise and a small frequency variation
    emit dataReady(amplitudeData);
}
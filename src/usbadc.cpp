#include "usbadc.h"

USBADC::USBADC(int dataSizeArg, double sampleFrequencyArg, QObject *parent) : DataReader(dataSizeArg, sampleFrequencyArg, parent) {
    this->open();
};

USBADC::~USBADC() {
    this->stop();
    this->close();
};

bool USBADC::open() {
    PaError err;

    std::cout << "PortAudio initialization" << std::endl;
    err = Pa_Initialize();
    if (err != paNoError)
        return false;

    PaStreamParameters inputParameters;

    int numDevices;
    numDevices = Pa_GetDeviceCount();
    std::cout << "PortAudio devices " << numDevices << std::endl;
    if (numDevices < 0) {
        std::cout << "ERROR: Pa_CountDevices returned " << numDevices << std::endl;
        err = numDevices;
    }

    const PaDeviceInfo *deviceInfo;
    int deviceIndex = 0;
    bool usbDetected = false;
    unsigned int tryCount = 0;
    // do {
    std::cout << "Trying to detect USB device " << ++tryCount << std::endl;
    for (deviceIndex = 0; deviceIndex < numDevices; deviceIndex++) {
        deviceInfo = Pa_GetDeviceInfo(deviceIndex);
        std::cout << "Checking " << deviceInfo->name << " device" << std::endl;
        const std::string name(deviceInfo->name);
        if (name.find("USB") != std::string::npos) {
            usbDetected = true;
            break;
        }
    }
    // } while (!usbDetected);

    std::cout << "Device " << deviceInfo->name << " selected" << std::endl;

    deviceIndex = 0;
    deviceInfo = Pa_GetDeviceInfo(deviceIndex);
    inputParameters.device = deviceIndex;
    if (inputParameters.device == paNoDevice)
        return false;

    inputParameters.channelCount = 1;
    inputParameters.sampleFormat = paFloat32;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = nullptr;

    // In case Alsa fails at the beginning, try several times
    tryCount = 0;
    do {
        std::cout << "Trying to open stream " << ++tryCount << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        err = Pa_OpenStream(
            &stream,
            &inputParameters,
            nullptr,
            sampleFrequency,
            dataSize,
            paClipOff,
            &USBADC::paCallback,
            this);
    } while (err != paNoError);

    err = Pa_SetStreamFinishedCallback(stream, &USBADC::paStreamFinished);
    if (err != paNoError) {
        Pa_CloseStream(stream);
        stream = nullptr;
        return false;
    }
    return true;
}

bool USBADC::close() {
    if (stream == nullptr)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = nullptr;

    return (err == paNoError);
}

bool USBADC::start() {
    if (stream == nullptr)
        return false;
    PaError err = Pa_StartStream(stream);

    return (err == paNoError);
}

bool USBADC::stop() {
    if (stream == nullptr)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

int USBADC::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                             unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo *timeInfo,
                             PaStreamCallbackFlags statusFlags) {
    float *in = (float *)inputBuffer;
    unsigned long i;

    (void)timeInfo;
    (void)statusFlags;
    (void)outputBuffer;

    for (i = 0; i < framesPerBuffer; i++)
        amplitudeData[i] = *in++;

    this->getData();

    return paContinue;
}

int USBADC::paCallback(const void *inputBuffer, void *outputBuffer,
                       unsigned long framesPerBuffer,
                       const PaStreamCallbackTimeInfo *timeInfo,
                       PaStreamCallbackFlags statusFlags,
                       void *userData) {
    return ((USBADC *)userData)->paCallbackMethod(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}

void USBADC::paStreamFinishedMethod() {
    std::cout << "Stream Completed" << std::endl;
}

void USBADC::paStreamFinished(void *userData) {
    return ((USBADC *)userData)->paStreamFinishedMethod();
}

void USBADC::getData() {
    emit dataReady(amplitudeData);
}

void USBADC::startStream() {
    std::cout << "USBADC stream started" << std::endl;
    this->start();
}
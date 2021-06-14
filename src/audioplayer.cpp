#include "audioplayer.h"

AudioPlayer::AudioPlayer(int dataSizeArg, double sampleFrequencyArg, QObject *parent) : QObject(parent), dataSize(dataSizeArg), sampleFrequency(sampleFrequencyArg) {
    period = 0.0;
    this->open();
};

AudioPlayer::~AudioPlayer() {
    this->stop();
    this->close();
};

bool AudioPlayer::open() {
    PaError err;

    err = Pa_Initialize();
    if (err != paNoError)
        return false;

    PaStreamParameters outputParameters;

    int numDevices;
    numDevices = Pa_GetDeviceCount();
    if (numDevices < 0) {
        std::cout << "ERROR: Pa_CountDevices returned " << numDevices << std::endl;
        err = numDevices;
    }

    const PaDeviceInfo *deviceInfo;
    int deviceIndex = 0;

    for (deviceIndex = 0; deviceIndex < numDevices; deviceIndex++) {
        deviceInfo = Pa_GetDeviceInfo(deviceIndex);
        const std::string name(deviceInfo->name);
        if (name.find("HDMI") != std::string::npos)
            break;
    }

    outputParameters.device = deviceIndex;
    if (outputParameters.device == paNoDevice)
        return false;

    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = deviceInfo->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = nullptr;

    // In case Alsa fails at the beginning, try several times
    do {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        err = Pa_OpenStream(
            &stream,
            nullptr,
            &outputParameters,
            sampleFrequency,
            dataSize,
            paClipOff,
            &AudioPlayer::paCallback,
            this);
    } while (err != paNoError);

    err = Pa_SetStreamFinishedCallback(stream, &AudioPlayer::paStreamFinished);
    if (err != paNoError) {
        Pa_CloseStream(stream);
        stream = nullptr;
        return false;
    }
    return true;
}

bool AudioPlayer::close() {
    if (stream == nullptr)
        return false;

    PaError err = Pa_CloseStream(stream);
    stream = nullptr;

    return (err == paNoError);
}

bool AudioPlayer::start() {
    if (stream == nullptr)
        return false;
    PaError err = Pa_StartStream(stream);

    return (err == paNoError);
}

bool AudioPlayer::stop() {
    if (stream == nullptr)
        return false;

    PaError err = Pa_StopStream(stream);

    return (err == paNoError);
}

int AudioPlayer::paCallbackMethod(const void *inputBuffer, void *outputBuffer,
                                  unsigned long framesPerBuffer,
                                  const PaStreamCallbackTimeInfo *timeInfo,
                                  PaStreamCallbackFlags statusFlags) {
    float *out = (float *)outputBuffer;
    float *in = (float *)inputBuffer;
    unsigned long i;

    (void)timeInfo;
    (void)statusFlags;
    (void)inputBuffer;

    for (i = 0; i < framesPerBuffer; i++) {
        *out++ = std::sin(2.0 * M_PI * 100.0 / sampleFrequency * i);
        *out++ = std::sin(2.0 * M_PI * 100.0 / sampleFrequency * i);
    }

    return paContinue;
}

int AudioPlayer::paCallback(const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo *timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData) {
    std::cout << "Playiiing" << std::endl;
    return ((AudioPlayer *)userData)->paCallbackMethod(inputBuffer, outputBuffer, framesPerBuffer, timeInfo, statusFlags);
}

void AudioPlayer::paStreamFinishedMethod() {
    std::cout << "Stream Completed" << std::endl;
}

void AudioPlayer::paStreamFinished(void *userData) {
    return ((AudioPlayer *)userData)->paStreamFinishedMethod();
}

void AudioPlayer::changePeriod(double newPeriod) {
    period = newPeriod;
}

void AudioPlayer::startStream() {
    this->start();
}
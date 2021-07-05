#include "emlidgps.h"

EMLIDGPS::EMLIDGPS() {
    fd = serialOpen("/dev/ttyUSB-GPSLink", 38400);
    if (fd < 0) {
        fprintf(stderr, "Unable to open serial device /dev/ttyUSB-GPSLink: %s\n", strerror(errno));
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    fd = serialOpen("/dev/ttyUSB-GPSLink", 38400);
    if (fd < 0) {
        fprintf(stderr, "Unable to open serial device /dev/ttyUSB-GPSLink: %s\n", strerror(errno));
        throw 1;
    }
};

EMLIDGPS::~EMLIDGPS() {
    serialClose(fd);
    std::cout << "Closed GPS Serial connection" << std::endl;
};

void EMLIDGPS::run() {
    char buff[100] = {0};
    char headerIdentifier[3] = {0};
    unsigned int id = 0;
    unsigned int sizeA = 0;
    unsigned int sizeB = 0;
    unsigned char length = 0;
    while (running) {
        headerIdentifier[0] = headerIdentifier[1];
        headerIdentifier[1] = serialGetchar(fd);
        if (strcmp(headerIdentifier, "ER") == 0) {
            id = serialGetchar(fd);
            sizeA = serialGetchar(fd);
            sizeB = serialGetchar(fd);
            length = (sizeB << 8) + sizeA;
            for (unsigned char i = 0; i < length + 2; i++) buff[i] = serialGetchar(fd);
            switch (id) {
                case ERBID::VER: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    unsigned char* verH = reinterpret_cast<unsigned char*>(buff + 4);
                    unsigned char* verM = reinterpret_cast<unsigned char*>(buff + 5);
                    unsigned char* verL = reinterpret_cast<unsigned char*>(buff + 6);
                } break;
                case ERBID::POS: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    double* latVal = reinterpret_cast<double*>(buff + 4);
                    double* lngVal = reinterpret_cast<double*>(buff + 12);
                    double* altEl = reinterpret_cast<double*>(buff + 20);
                    double* altMsl = reinterpret_cast<double*>(buff + 28);
                    unsigned int* accHor = reinterpret_cast<unsigned int*>(buff + 36);
                    unsigned int* accVer = reinterpret_cast<unsigned int*>(buff + 40);
                    latValue = *latVal;
                    lngValue = *lngVal;
                    emit dataReady(latValue, lngValue);
                } break;
                case ERBID::STAT: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    unsigned short* weekGPS = reinterpret_cast<unsigned short*>(buff + 4);
                    unsigned char* fixType = reinterpret_cast<unsigned char*>(buff + 6);
                    unsigned char* fixStatus = reinterpret_cast<unsigned char*>(buff + 7);
                    unsigned char* numSV = reinterpret_cast<unsigned char*>(buff + 8);
                } break;
                case ERBID::DOPS: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    unsigned short* dopGeo = reinterpret_cast<unsigned short*>(buff + 4);
                    unsigned short* dopPos = reinterpret_cast<unsigned short*>(buff + 6);
                    unsigned short* dopVer = reinterpret_cast<unsigned short*>(buff + 8);
                    unsigned short* dopHor = reinterpret_cast<unsigned short*>(buff + 10);
                } break;
                case ERBID::VEL: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    signed int* velN = reinterpret_cast<signed int*>(buff + 4);
                    signed int* velE = reinterpret_cast<signed int*>(buff + 8);
                    signed int* velD = reinterpret_cast<signed int*>(buff + 12);
                    unsigned int* speed = reinterpret_cast<unsigned int*>(buff + 16);
                    signed int* heading = reinterpret_cast<signed int*>(buff + 20);
                    unsigned int* accS = reinterpret_cast<unsigned int*>(buff + 24);
                } break;
                case ERBID::SVI: {
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 0);
                    unsigned char* nSV = reinterpret_cast<unsigned char*>(buff + 4);
                    for (unsigned char i = 0; i < *nSV; i++) {
                        unsigned char* idSV = reinterpret_cast<unsigned char*>(buff + 20 * i + 5);
                        unsigned char* typeSV = reinterpret_cast<unsigned char*>(buff + 20 * i + 6);
                        signed int* carPh = reinterpret_cast<signed int*>(buff + 20 * i + 7);
                        signed int* psRan = reinterpret_cast<signed int*>(buff + 20 * i + 11);
                        signed int* freqD = reinterpret_cast<signed int*>(buff + 20 * i + 15);
                        unsigned short* snr = reinterpret_cast<unsigned short*>(buff + 20 * i + 19);
                        unsigned short* azim = reinterpret_cast<unsigned short*>(buff + 20 * i + 21);
                        unsigned short* elev = reinterpret_cast<unsigned short*>(buff + 20 * i + 23);
                    }
                } break;
                case ERBID::RTK: {
                    unsigned char* numSV = reinterpret_cast<unsigned char*>(buff + 0);
                    unsigned short* age = reinterpret_cast<unsigned short*>(buff + 1);
                    signed int* baselineN = reinterpret_cast<signed int*>(buff + 3);
                    signed int* baselineE = reinterpret_cast<signed int*>(buff + 7);
                    signed int* baselineD = reinterpret_cast<signed int*>(buff + 11);
                    unsigned short* arRatio = reinterpret_cast<unsigned short*>(buff + 15);
                    unsigned short* weekGPS = reinterpret_cast<unsigned short*>(buff + 17);
                    unsigned int* timeGPS = reinterpret_cast<unsigned int*>(buff + 19);
                } break;
            }
        }
    }
}
#include "emlidgps.h"

EMLIDGPS* EMLIDGPS::instance = nullptr;

EMLIDGPS::EMLIDGPS() {
    fd = serialOpen("/dev/ttyACM0", 115200);
    if (fd < 0) {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        exit(1);
    }
};

EMLIDGPS::~EMLIDGPS() {
    serialClose(fd);
};

void EMLIDGPS::getData() {
    emit dataReady(latValue, lngValue);
};

void EMLIDGPS::run() {
    char buff[100] = {0};
    char headerIdentifier[3] = {0};
    unsigned int id = 0;
    unsigned int sizeA = 0;
    unsigned int sizeB = 0;
    unsigned int length = 0;
    while (true) {
        headerIdentifier[0] = headerIdentifier[1];
        headerIdentifier[1] = serialGetchar(fd);
        if (strcmp(headerIdentifier, "ER") == 0) {
            id = serialGetchar(fd);
            sizeA = serialGetchar(fd);
            sizeB = serialGetchar(fd);
            length = (sizeB << 8) + sizeA;
            for (int i = 0; i < length + 2; i++) buff[i] = serialGetchar(fd);
            if (id == 0x01) {
                unsigned int* timeGPS = (unsigned int*)(buff + 0);
                unsigned int verH = buff[4];
                unsigned int verM = buff[5];
                unsigned int verL = buff[6];
            } else if (id == 0x02) {
                unsigned int* timeGPS = (unsigned int*)(buff + 0);
                double* lng = (double*)(buff + 4);
                double* lat = (double*)(buff + 12);
                double* altEl = (double*)(buff + 20);
                double* altMsl = (double*)(buff + 28);
                unsigned int* accHor = (unsigned int*)(buff + 36);
                unsigned int* accVer = (unsigned int*)(buff + 40);
                lngValue = *lng;
                latValue = *lat;
            } else if (id == 0x07) {
                unsigned char* numSV = (unsigned char*)(buff + 0);
                unsigned short* age = (unsigned short*)(buff + 1);
                signed int* baselineN = (signed int*)(buff + 3);
                signed int* baselineE = (signed int*)(buff + 7);
                signed int* baselineD = (signed int*)(buff + 11);
                unsigned short* arRatio = (unsigned short*)(arRatio + 15);
                unsigned short* weekGPS = (unsigned short*)(weekGPS + 17);
                unsigned int* timeGPS = (unsigned int*)(buff + 19);
            }
        }
    }
}
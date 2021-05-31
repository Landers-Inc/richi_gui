#include "emlidgps.h"

EMLIDGPS::EMLIDGPS() {
    do {
        fd = serialOpen("/dev/ttyACM0", 115200);
        if (fd < 0) {
            fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
            fd = serialOpen("/dev/ttyACM1", 115200);
            if (fd < 0) {
                fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (fd < 0);
};

EMLIDGPS::~EMLIDGPS() {
    serialClose(fd);
};

void EMLIDGPS::run() {
    char buff[100] = {0};
    char headerIdentifier[3] = {0};
    unsigned int id = 0;
    unsigned int sizeA = 0;
    unsigned int sizeB = 0;
    unsigned int length = 0;
    while (running) {
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
                unsigned char* verH = (unsigned char*)(buff + 4);
                unsigned char* verM = (unsigned char*)(buff + 5);
                unsigned char* verL = (unsigned char*)(buff + 6);
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
                emit dataReady(latValue, lngValue);
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
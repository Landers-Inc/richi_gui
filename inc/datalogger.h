#pragma once

#include <chrono>
#include <string>
#include <vector>

// This is singleton DataLogger class to write everything to database
class DataLogger {
   private:
    // Static object to store the singleton instance
    static DataLogger *instance;
    // Static member to save filename
    static std::string filename;

    // Private constructor so that no objects can be created.
    DataLogger() {
        auto timeNow = std::chrono::system_clock::now();
        time_t timeNowT = std::chrono::system_clock::to_time_t(timeNow);
        char qwer[100];
        std::strftime(qwer, sizeof(qwer), "datalogger_%Y_%m_%d_%H-%M-%S.csv", std::gmtime(&timeNowT));
        filename = std::string(qwer);
    }

   public:
    // The DataLogger object is created when getting the object's instance
    static DataLogger *getInstance() {
        if (!instance) {
            instance = new DataLogger;
        }
        return instance;
    }

    // We define an structure to save the current configuration
    typedef struct Configuration {
        int id;                  // Identifier
        double dataSize;         // Buffer used to process Spectrum
        double sampleFrequency;  // Frequency sampling for this configuration
    } Configuration;

    // We define an structure to save the data from one beacon
    typedef struct BeaconData {
        int id;              // Identifier
        double distance;     // Distance from surface
        double frequency;    // Frequency of the beacon
        double latPosition;  // Latitude GPS position
        double lonPosition;  // Longitude GPS Position
    } BeaconData;

    // We define an structure to save the timestamp and position
    typedef struct TimeData {
        int id;              // Identifier
        int timestamp;       // Timestamp with respect to UTC
        double latPosition;  // Latitude GPS position
        double lonPosition;  // Longitude GPS Position
    } TimeData;

    // We define an structure to save the peaks data (frequency and power)
    typedef struct PeaksData {
        int id;                // Identifier
        long int timedata_id;  // TimeData identifier
        double frequency;      // Frequency of the peak
        double power;          // Power of the peak
    } PeaksData;

    // We define an structure to save the actual spectrum
    typedef struct SpectrumData {
        int id;                        // Identifier
        int timedata_id;               // Timestamp with respect to UTC
        int configuration_id;          // SpectrumData identifier
        std::vector<double> spectrum;  // Here we save the complete spectrum
    } SpectrumData;
};
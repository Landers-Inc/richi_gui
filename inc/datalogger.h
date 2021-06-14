#pragma once

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtSql>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

// This is singleton DataLogger class to write everything to database
class DataLogger : public QObject {
    Q_OBJECT
   private:
    // Static object to store the singleton instance
    static DataLogger *instance;
    // Static member to save filename
    QSqlDatabase loggerDatabase = QSqlDatabase::addDatabase("QMYSQL");
    // Current timestamp id
    unsigned int timestampId = 0;
    // Current configuration id
    unsigned int configurationId = 0;
    // Current beacon preblast count
    unsigned int beaconPreCount = 0;
    // Current beacon postblast count
    unsigned int beaconPostCount = 0;

    // Private constructor so that no other objects can be created.
    DataLogger() {
        // Set MariaDB database
        loggerDatabase.setHostName("127.0.0.1");
        loggerDatabase.setDatabaseName("datalog");
        loggerDatabase.setUserName("admin");
        loggerDatabase.setPassword("password");
        if (loggerDatabase.open()) {
            setDatabaseTables();
            getLastIDs();
        }
    };

    ~DataLogger() {
        std::cout << "Closing DataLogger instance" << std::endl;
    };

    void setDatabaseTables();
    void getLastIDs();

   public:
    // The DataLogger object is created when getting the object's instance
    static DataLogger *getInstance() {
        if (!instance) instance = new DataLogger;
        return instance;
    }

    unsigned int getPreblastCount() { return beaconPreCount; };
    unsigned int getPostblastCount() { return beaconPostCount; };

    // We define an structure to save the current configuration
    typedef struct Configuration {
        char *datetime;
        unsigned int dataSize;   // Buffer used to process Spectrum
        double sampleFrequency;  // Frequency sampling for this configuration
    } Configuration;

    // We define an structure to save the data from one beacon
    typedef struct BeaconData {
        unsigned int registerType;  // Register type for beacon (Pre or Post blast)
        double distance;            // Distance from surface
        double frequency;           // Frequency of the beacon
        double power;               // Frequency of the beacon
    } BeaconData;

    // We define an structure to save the timestamp and position
    typedef struct TimeData {
        unsigned long long timestamp;  // Timestamp with respect to UTC
        double latPosition;            // Latitude GPS position
        double lngPosition;            // Longitude GPS Position
    } TimeData;

    // We define an structure to save the peaks data (frequency and power)
    typedef struct PeaksData {
        unsigned int peakId;  // Frequency of the peak
        double frequency;     // Frequency of the peak
        double power;         // Power of the peak
    } PeaksData;

    // We define an structure to save the actual spectrum
    typedef struct SpectrumData {
        std::vector<double> spectrum;  // Here we save the complete spectrum
    } SpectrumData;
   public slots:
    void insertConfiguration(Configuration const &conf);
    void insertBeaconData(BeaconData const &beacon);
    void insertTimeData(TimeData const &time);
    void insertPeaksData(PeaksData const &peak);
    void insertSpectrumData(SpectrumData const &spectrum);
};
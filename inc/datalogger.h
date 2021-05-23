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
    std::string filename;
    // Static member to save filename
    QSqlDatabase loggerDatabase = QSqlDatabase::addDatabase("QMYSQL");
    // Current timestamp id
    unsigned int timestampId = 0;
    // Current configuration id
    unsigned int configurationId = 1;

    // Private constructor so that no other objects can be created.
    DataLogger() {
        // Read actual time to save datalogger file
        auto timeNow = std::chrono::system_clock::now();
        time_t timeNowT = std::chrono::system_clock::to_time_t(timeNow);
        char temp[100];
        std::strftime(temp, sizeof(temp), "datalogger_%Y_%m_%d_%H-%M-%S.csv", std::gmtime(&timeNowT));
        filename = std::string(temp);

        // Set MySQL database
        loggerDatabase.setHostName("127.0.0.1");
        loggerDatabase.setDatabaseName("datalog");
        loggerDatabase.setUserName("admin");
        loggerDatabase.setPassword("password");
        if (loggerDatabase.open()) setDatabaseTables();
    };

    void setDatabaseTables();

   public:
    // The DataLogger object is created when getting the object's instance
    static DataLogger *getInstance() {
        if (!instance) instance = new DataLogger;
        return instance;
    }

    // We define an structure to save the current configuration
    typedef struct Configuration {
        unsigned int id;         // Identifier
        unsigned int dataSize;   // Buffer used to process Spectrum
        double sampleFrequency;  // Frequency sampling for this configuration
    } Configuration;

    // We define an structure to save the data from one beacon
    typedef struct BeaconData {
        double distance;     // Distance from surface
        double frequency;    // Frequency of the beacon
        double power;        // Frequency of the beacon
        double latPosition;  // Latitude GPS position
        double lonPosition;  // Longitude GPS Position
    } BeaconData;

    // We define an structure to save the timestamp and position
    typedef struct TimeData {
        unsigned long long timestamp;  // Timestamp with respect to UTC
        double latPosition;            // Latitude GPS position
        double lonPosition;            // Longitude GPS Position
    } TimeData;

    // We define an structure to save the peaks data (frequency and power)
    typedef struct PeaksData {
        double frequency;  // Frequency of the peak
        double power;      // Power of the peak
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
#include "datalogger.h"

DataLogger *DataLogger::instance = nullptr;

void DataLogger::setDatabaseTables() {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "CREATE TABLE IF NOT EXISTS Configuration ("
        "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"
        "dataSize INT UNSIGNED NOT NULL,"
        "sampleFrequency DOUBLE NOT NULL"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS TimeData ("
        "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"
        "timestamp BIGINT UNSIGNED NOT NULL,"
        "latPosition DOUBLE NOT NULL,"
        "lonPosition DOUBLE NOT NULL"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS BeaconData ("
        "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,"
        "timedata_id INT UNSIGNED NOT NULL, "
        "configuration_id INT UNSIGNED NOT NULL, "
        "registerType INT UNSIGNED NOT NULL, "
        "distance DOUBLE NOT NULL,"
        "frequency DOUBLE NOT NULL,"
        "power DOUBLE NOT NULL,"
        "CONSTRAINT fk_beacon_timedata "
        "FOREIGN KEY (timedata_id) REFERENCES TimeData (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT, "
        "CONSTRAINT fk_beacon_configuration "
        "FOREIGN KEY (configuration_id) REFERENCES Configuration (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS PeaksData ("
        "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, "
        "timedata_id INT UNSIGNED NOT NULL, "
        "configuration_id INT UNSIGNED NOT NULL, "
        "frequency DOUBLE NOT NULL, "
        "power DOUBLE NOT NULL, "
        "CONSTRAINT fk_peaks_timedata "
        "FOREIGN KEY (timedata_id) REFERENCES TimeData (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT, "
        "CONSTRAINT fk_peaks_configuration "
        "FOREIGN KEY (configuration_id) REFERENCES Configuration (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS SpectrumData ("
        "id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY, "
        "timedata_id INT UNSIGNED NOT NULL, "
        "configuration_id INT UNSIGNED NOT NULL, "
        "spectrum BLOB, "
        "CONSTRAINT fk_spectrum_timedata "
        "FOREIGN KEY (timedata_id) REFERENCES TimeData (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT, "
        "CONSTRAINT fk_spectrum_configuration "
        "FOREIGN KEY (configuration_id) REFERENCES Configuration (id) "
        "ON DELETE CASCADE "
        "ON UPDATE RESTRICT"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();
}

void DataLogger::getLastIDs() {
    QSqlQuery query(loggerDatabase);
    query.prepare("SELECT MAX(id) FROM TimeData");
    if (query.exec())
        if (query.next())
            timestampId = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    query.clear();
    query.prepare("SELECT MAX(id) FROM Configuration");
    if (query.exec())
        if (query.next())
            configurationId = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    query.clear();
    query.prepare(
        "SELECT COUNT(*) "
        "FROM BeaconData "
        "WHERE configuration_id=:configuration_id "
        "AND registerType=0");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPreCount = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    query.clear();
    query.prepare(
        "SELECT COUNT(*) "
        "FROM BeaconData "
        "WHERE configuration_id=:configuration_id "
        "AND registerType=1");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPostCount = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();
}

void DataLogger::insertConfiguration(Configuration const &conf) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "INSERT INTO Configuration ("
        "dataSize,"
        "sampleFrequency"
        ") VALUES ("
        ":dataSize,"
        ":sampleFrequency"
        ")");
    query.bindValue(":dataSize", conf.dataSize);
    query.bindValue(":sampleFrequency", conf.sampleFrequency);
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare("SELECT MAX(id) FROM Configuration");
    if (query.exec())
        if (query.next())
            configurationId = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();
}

void DataLogger::insertTimeData(TimeData const &time) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "INSERT INTO TimeData ("
        "timestamp,"
        "latPosition,"
        "lonPosition"
        ") VALUES ("
        ":timestamp,"
        ":latPosition,"
        ":lonPosition"
        ")");
    query.bindValue(":timestamp", time.timestamp);
    query.bindValue(":latPosition", time.latPosition);
    query.bindValue(":lonPosition", time.lonPosition);
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare("SELECT MAX(id) FROM TimeData");
    if (query.exec())
        if (query.next())
            timestampId = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();
}

void DataLogger::insertBeaconData(BeaconData const &beacon) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "INSERT INTO BeaconData ("
        "timedata_id,"
        "configuration_id,"
        "registerType,"
        "distance,"
        "frequency,"
        "power,"
        "latPosition,"
        "lonPosition"
        ") VALUES ("
        ":timedata_id,"
        ":configuration_id,"
        ":registerType,"
        ":dataSize,"
        ":frequency,"
        ":power"
        ")");
    query.bindValue(":timedata_id", timestampId);
    query.bindValue(":configuration_id", configurationId);
    query.bindValue(":registerType", beacon.registerType);
    query.bindValue(":distance", beacon.distance);
    query.bindValue(":frequency", beacon.frequency);
    query.bindValue(":power", beacon.power);
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "SELECT COUNT(*)"
        "FROM BeaconData"
        "WHERE configuration_id=:configuration_id"
        "AND registerType=0");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPreCount = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    query.prepare(
        "SELECT COUNT(*)"
        "FROM BeaconData"
        "WHERE configuration_id=:configuration_id"
        "AND registerType=1");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPostCount = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();
}

void DataLogger::insertPeaksData(PeaksData const &peak) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "INSERT INTO PeaksData ("
        "timedata_id,"
        "configuration_id,"
        "frequency,"
        "power"
        ") VALUES ("
        ":timedata_id,"
        ":configuration_id,"
        ":frequency,"
        ":power"
        ")");
    query.bindValue(":timedata_id", timestampId);
    query.bindValue(":configuration_id", configurationId);
    query.bindValue(":frequency", peak.frequency);
    query.bindValue(":power", peak.power);
    if (!query.exec())
        qDebug() << query.lastError();
}

void DataLogger::insertSpectrumData(SpectrumData const &spectrum) {
    QSqlQuery query(loggerDatabase);

    query.prepare("SELECT dataSize FROM Configuration WHERE id=:configuration_id");
    query.bindValue(":configuration_id", configurationId);
    unsigned int bufferSize;
    if (query.exec())
        if (query.next())
            bufferSize = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    QByteArray binarySpectrum(16384, 0x00);
    unsigned int n = 0;

    for (unsigned int i = 0; i < bufferSize / 2; i++) {
        unsigned char *spectraCast = (unsigned char *)&spectrum.spectrum[i];
        for (unsigned int j = 0; j < 8; j++) {
            binarySpectrum[n++] = *(spectraCast + j);
        }
    }

    query.prepare(
        "INSERT INTO SpectrumData ("
        "timedata_id,"
        "configuration_id,"
        "spectrum"
        ") VALUES ("
        ":timedata_id,"
        ":configuration_id,"
        ":spectrum"
        ")");
    query.bindValue(":timedata_id", timestampId);
    query.bindValue(":configuration_id", configurationId);
    query.bindValue(":spectrum", binarySpectrum);
    if (!query.exec())
        qDebug() << query.lastError();
}
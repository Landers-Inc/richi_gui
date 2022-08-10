#include "datalogger.h"

DataLogger *DataLogger::instance = nullptr;

void DataLogger::setDatabaseTables() {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "CREATE TABLE IF NOT EXISTS Configuration ("
        "id INTEGER AUTO_INCREMENT PRIMARY KEY,"
        "name VARCHAR(256) NOT NULL,"
        "date_start DATETIME NOT NULL,"
        "data_size INT UNSIGNED NOT NULL,"
        "sample_frequency DOUBLE NOT NULL"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS TimeData ("
        "id INTEGER AUTO_INCREMENT PRIMARY KEY,"
        "timestamp BIGINT UNSIGNED NOT NULL,"
        "lat_position DOUBLE NOT NULL,"
        "lng_position DOUBLE NOT NULL,"
        "hgt_position DOUBLE NOT NULL"
        ")");
    if (!query.exec())
        qDebug() << query.lastError();

    query.prepare(
        "CREATE TABLE IF NOT EXISTS BeaconData ("
        "id INTEGER AUTO_INCREMENT PRIMARY KEY,"
        "timedata_id INT UNSIGNED NOT NULL, "
        "configuration_id INT UNSIGNED NOT NULL, "
        "register_type INT UNSIGNED NOT NULL, "
        "beacon_type INT UNSIGNED NOT NULL, "
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
        "id INTEGER AUTO_INCREMENT PRIMARY KEY, "
        "timedata_id INT UNSIGNED NOT NULL, "
        "configuration_id INT UNSIGNED NOT NULL, "
        "peak_id INT UNSIGNED NOT NULL, "
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
        "id INTEGER AUTO_INCREMENT PRIMARY KEY, "
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

void DataLogger::getLastBeacons() {
    QSqlQuery query(loggerDatabase);

    query.clear();
    query.prepare(
        "SELECT t1.id, "
        "t1.beacon_type, "
        "t1.distance, "
        "t1.frequency, "
        "t1.power, "
        "t2.lat_position, "
        "t2.lng_position, "
        "t2.hgt_position "
        "FROM BeaconData t1 "
        "JOIN TimeData t2 ON t1.timedata_id = t2.id "
        "WHERE configuration_id=:configuration_id "
        "AND register_type=0 "
        "ORDER BY id ASC");
    query.bindValue(":configuration_id", configurationId);
    beaconPreCount = 0;
    beaconPreData.clear();
    if (query.exec()) {
        while (query.next()) {
            ++beaconPreCount;
            BeaconItem tmp;
            tmp.id = query.value(0).toUInt();
            tmp.beaconType = query.value(1).toUInt();
            tmp.distance = query.value(2).toDouble();
            tmp.frequency = query.value(3).toDouble();
            tmp.power = query.value(4).toDouble();
            tmp.latPosition = query.value(5).toDouble();
            tmp.lngPosition = query.value(6).toDouble();
            tmp.hgtPosition = query.value(7).toDouble();
            beaconPreData.push_back(tmp);
        }
    } else {
        qDebug() << query.lastError();
    }

    query.clear();
    query.prepare(
        "SELECT t1.id, "
        "t1.beacon_type, "
        "t1.distance, "
        "t1.frequency, "
        "t1.power, "
        "t2.lat_position, "
        "t2.lng_position, "
        "t2.hgt_position "
        "FROM BeaconData t1 "
        "JOIN TimeData t2 ON t1.timedata_id = t2.id "
        "WHERE configuration_id=:configuration_id "
        "AND register_type=1 "
        "ORDER BY id ASC");
    query.bindValue(":configuration_id", configurationId);
    beaconPostCount = 0;
    beaconPostData.clear();
    if (query.exec()) {
        while (query.next()) {
            ++beaconPostCount;
            BeaconItem tmp;
            tmp.id = query.value(0).toUInt();
            tmp.beaconType = query.value(1).toUInt();
            tmp.distance = query.value(2).toDouble();
            tmp.frequency = query.value(3).toDouble();
            tmp.power = query.value(4).toDouble();
            tmp.latPosition = query.value(5).toDouble();
            tmp.lngPosition = query.value(6).toDouble();
            tmp.hgtPosition = query.value(7).toDouble();
            beaconPostData.push_back(tmp);
        }
    } else
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
}

void DataLogger::getConfigurationName(char *name) {
    QSqlQuery query(loggerDatabase);

    std::string configurationName;

    query.prepare(
        "SELECT name "
        "FROM Configuration "
        "WHERE id = :id");
    query.bindValue(":id", configurationId);
    if (query.exec())
        if (query.next()) {
            configurationName = query.value(0).toString().toStdString();
            strcpy(name, configurationName.c_str());
        } else {
            qDebug() << query.lastError();
        }
    else
        qDebug() << query.lastError();
}

void DataLogger::insertConfiguration(Configuration const &conf) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
            "INSERT INTO Configuration ("
        "name,"
        "date_start,"
        "data_size,"
        "sample_frequency"
        ") VALUES ("
        ":name,"
        ":date_start,"
        ":data_size,"
        ":sample_frequency"
        ")");
    query.bindValue(":name", conf.name);
    query.bindValue(":date_start", conf.datetime);
    query.bindValue(":data_size", conf.dataSize);
    query.bindValue(":sample_frequency", conf.sampleFrequency);
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

    query.prepare(
        "SELECT COUNT(*) "
        "FROM BeaconData "
        "WHERE configuration_id=:configuration_id "
        "AND register_type=0");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPreCount = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    query.prepare(
        "SELECT COUNT(*) "
        "FROM BeaconData "
        "WHERE configuration_id=:configuration_id "
        "AND register_type=1");
    query.bindValue(":configuration_id", configurationId);
    if (query.exec())
        if (query.next())
            beaconPostCount = query.value(0).toUInt();
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
        "lat_position,"
        "lng_position,"
        "hgt_position"
        ") VALUES ("
        ":timestamp,"
        ":lat_position,"
        ":lng_position,"
        ":hgt_position"
        ")");
    query.bindValue(":timestamp", time.timestamp);
    query.bindValue(":lat_position", time.latPosition);
    query.bindValue(":lng_position", time.lngPosition);
    query.bindValue(":hgt_position", time.hgtPosition);
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
        "register_type,"
        "beacon_type,"
        "distance,"
        "frequency,"
        "power"
        ") VALUES ("
        ":timedata_id,"
        ":configuration_id,"
        ":register_type,"
        ":beacon_type,"
        ":distance,"
        ":frequency,"
        ":power"
        ")");
    query.bindValue(":timedata_id", timestampId);
    query.bindValue(":configuration_id", configurationId);
    query.bindValue(":register_type", beacon.registerType);
    query.bindValue(":beacon_type", beacon.beaconType);
    query.bindValue(":distance", beacon.distance);
    query.bindValue(":frequency", beacon.frequency);
    query.bindValue(":power", beacon.power);
    if (!query.exec())
        qDebug() << query.lastError();

    getLastBeacons();
}

void DataLogger::deleteBeaconData(BeaconData const &beacon) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "DELETE FROM BeaconData "
        "WHERE id ="
        ":id");
    query.bindValue(":id", beacon.id);
    if (!query.exec())
        qDebug() << query.lastError();

    getLastBeacons();
}

void DataLogger::deleteBeaconData(BeaconItem const &beacon) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "DELETE FROM BeaconData "
        "WHERE id ="
        ":id");
    query.bindValue(":id", beacon.id);
    if (!query.exec())
        qDebug() << query.lastError();

    getLastBeacons();
}

void DataLogger::updateBeaconData() {
    QSqlQuery query(loggerDatabase);

    for (auto beacon : beaconPreData) {
        query.prepare(
            "UPDATE BeaconData "
            "SET distance = :distance, "
            "power = :power, "
            "frequency = :frequency "
            "WHERE "
            "id = :id");
        query.bindValue(":id", beacon.id);
        query.bindValue(":distance", beacon.distance);
        query.bindValue(":power", beacon.power);
        query.bindValue(":frequency", beacon.frequency);
        if (!query.exec())
            qDebug() << query.lastError();
    }

    for (auto beacon : beaconPostData) {
        query.prepare(
            "UPDATE BeaconData "
            "SET distance = :distance, "
            "power = :power, "
            "frequency = :frequency "
            "WHERE "
            "id = :id");
        query.bindValue(":id", beacon.id);
        query.bindValue(":distance", beacon.distance);
        query.bindValue(":power", beacon.power);
        query.bindValue(":frequency", beacon.frequency);
        if (!query.exec())
            qDebug() << query.lastError();
    }
}

void DataLogger::insertPeaksData(PeaksData const &peak) {
    QSqlQuery query(loggerDatabase);

    query.prepare(
        "INSERT INTO PeaksData ("
        "timedata_id,"
        "configuration_id,"
        "peak_id,"
        "frequency,"
        "power"
        ") VALUES ("
        ":timedata_id,"
        ":configuration_id,"
        ":peak_id,"
        ":frequency,"
        ":power"
        ")");
    query.bindValue(":timedata_id", timestampId);
    query.bindValue(":configuration_id", configurationId);
    query.bindValue(":peak_id", peak.peakId);
    query.bindValue(":frequency", peak.frequency);
    query.bindValue(":power", peak.power);
    if (!query.exec())
        qDebug() << query.lastError();
}

void DataLogger::insertSpectrumData(SpectrumData const &spectrum) {
    QSqlQuery query(loggerDatabase);

    query.prepare("SELECT data_size FROM Configuration WHERE id=:configuration_id");
    query.bindValue(":configuration_id", configurationId);
    unsigned int bufferSize;
    if (query.exec())
        if (query.next())
            bufferSize = query.value(0).toUInt();
        else
            qDebug() << query.lastError();
    else
        qDebug() << query.lastError();

    QByteArray binarySpectrum(8192, 0x00);
    unsigned int n = 0;

    for (unsigned int i = 0; i < bufferSize / 2; i++) {
        float tempSpectra = spectrum.spectrum[i];
        unsigned char *spectraCast = (unsigned char *)&tempSpectra;
        for (unsigned int j = 0; j < 4; j++) {
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

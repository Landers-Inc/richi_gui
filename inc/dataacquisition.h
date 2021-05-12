#ifndef DATAACQUISITION_H
#define DATAACQUISITION_H

#include <QObject>
#include <random>

/**
 * @brief Abstract class for data acquisition
 */
class DataAcquisition : public QObject{
    Q_OBJECT
public:
    int dataSize; /**< Buffer size to process data */
    double sampleFrequency; /**< Sample frequency for data acquisition*/

    std::vector<double> timeData; /**< Vector to store time data */
    std::vector<double> amplitudeData; /**< Vector to store converted data */

    explicit DataAcquisition(int dataSizeArg, double sampleFrequencyArg, QObject *parent = 0) : QObject(parent){
        dataSize = dataSizeArg;
        sampleFrequency = sampleFrequencyArg;
        amplitudeData = std::vector<double>(dataSize);
        timeData = std::vector<double>(dataSize);
    }; /**< Class constructor */

    virtual ~DataAcquisition() {}; /**< Class destructor */

    void setDataSize(int newSize) {dataSize = newSize;}; /**< Buffer size setter */
    int getDataSize(){return dataSize;}; /**< Buffer size getter */
    void setSampleFrequency(double newFrequency){sampleFrequency = newFrequency;}; /**< Sample frequency setter */
    double getSampleFrequency(){return sampleFrequency;}; /**< Sample frequency getter */
signals:
    virtual void dataReady(std::vector<double> const &timeData, std::vector<double> const &amplitudeData); /**< Qt Signal signal to transfer data to processor thread */
public slots:
    virtual void getData() = 0; /**< Qt Object slot function to acquire data from converter */
};

#endif // DATAACQUISITION_H

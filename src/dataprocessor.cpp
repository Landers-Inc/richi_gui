#include "dataprocessor.h"

std::vector<std::vector<double>> DataProcessor::fftCalculation(std::vector<double> data){
    std::vector<std::vector<double>> out = {
        std::vector<double>(N_size/2),
        std::vector<double>(N_size/2),
        std::vector<double>(N_size/2),
        std::vector<double>(N_size/2)
    };
    std::vector<fftw_complex> fft_out(N_size);
    fftw_plan p = fftw_plan_dft_r2c_1d(N_size, data.data(), fft_out.data(), FFTW_ESTIMATE);
    fftw_execute(p);
    for(auto i = 0; i < N_size/2; i++){
        out[0][i] = (double)sampleFrequency * i/N_size;
        out[1][i] = pow(10, -processGain/10.0)/N_size*(std::sqrt(pow(fft_out[i][0], 2.0) + pow(fft_out[i][1], 2.0)));
        out[2][i] = 10.0*log10(out[1][i]);
    }
    fftw_destroy_plan(p);
    fftw_cleanup();
    return out;
}

std::vector<Peak> DataProcessor::getPeaks(std::vector<std::vector<double>> fft){
    std::vector<Peak> out;
    int max_index = 0;
    double max_val = -__DBL_MAX__;
    for(unsigned int i = 0; i < fft[1].size(); i++) {
        if(fft[1][i] > max_val) {
            max_index = i;
            max_val = fft[1][i];
        }
    }

    Peak peakData = getWeightedFrequency(fft, max_index);
    out.push_back(peakData);
    return out;
}

Peak DataProcessor::getWeightedFrequency(std::vector<std::vector<double>> fft, int index){
    double weightedFrequency = 0.0;
    double powerIntegral = 0.0;
    for(int i = -51; i <= 51; i++){
        if(index + i >= 0 && index + i < N_size){
            powerIntegral     += fft[1][index + i];
            weightedFrequency += fft[1][index + i] * fft[0][index + i];
        }
    }

    Peak out = {weightedFrequency/powerIntegral, powerIntegral, index};
    return out;
}

double DataProcessor::calculateEntropy(std::vector<std::vector<double>> data){
    double out = 0.0;
    double normalizeData = 0.0;
    for(int i = 0; i < N_size/2; i++) normalizeData += data[1][i];
    for(int i = 0; i < N_size/2; i++) out -= data[1][i]/normalizeData * log2(data[1][i]/normalizeData);
    return out;
}

void DataProcessor::processData(std::vector<double> timeData, std::vector<double> amplitudeData){
    // Cast data from std::vector to QVector. Necessary to plot data on QCustomPlot
    QVector<double> Qoutx = QVector<double>(timeData.begin(), timeData.end());
    QVector<double> Qouty = QVector<double>(amplitudeData.begin(), amplitudeData.end());
    // Emit signal to MainWindow to plot time data
    emit dataReady(Qoutx, Qouty);

    // Apply Hanning Window to data
    for(unsigned int i = 0; i < amplitudeData.size(); ++i) amplitudeData[i] *= hannWindow[i];

    // Calculate FFT
    std::vector<std::vector<double>> dataFFT = fftCalculation(amplitudeData);
    // Cast FFT from std::vector to QVector. Necessary to plot data on QCustomPlot
    Qoutx = QVector<double>(dataFFT[0].begin(), dataFFT[0].end());
    Qouty = QVector<double>(dataFFT[2].begin(), dataFFT[2].end());
    // Emit signal to MainWindow to plot frequency data
    emit fftReady(Qoutx, Qouty);

    // Calculate peaks on FFT
    std::vector<Peak> peaksData = getPeaks(dataFFT);
    // Emit signal to MainWindow to update peak frequency and power
    emit peakOneReady(peaksData[0].frequency, 10.0 * log10(peaksData[0].value));
    //Sleep(500);
}

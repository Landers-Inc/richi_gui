#include "dataprocessor.h"

std::vector<std::vector<double>> DataProcessor::fftCalculation(std::vector<double> data){
    std::vector<std::vector<double>> out = {std::vector<double>(N_size), std::vector<double>(N_size)};
    std::vector<fftw_complex> fft_out(N_size);
    fftw_plan p = fftw_plan_dft_r2c_1d(N_size, data.data(), fft_out.data(), FFTW_ESTIMATE);
    fftw_execute(p);
    for(auto i = 0; i < N_size/2; i++){
        out[0][i] = (double)N_size * (double)i/(double)N_size;
        out[1][i] = 10.0*log10(1.0/N_size*(std::sqrt(pow(fft_out[i][0], 2.0) + pow(fft_out[i][1], 2.0))));
    }
    fftw_destroy_plan(p);
    fftw_cleanup();
    return out;
}

void DataProcessor::doData(){
    std::vector<std::vector<double>> out = {std::vector<double>(N_size), std::vector<double>(N_size)};
    std::normal_distribution<double> dist_amp(0.0, 0.001);
    std::normal_distribution<double> dist_freq(1000.0, 0.001);
    for (int i=0; i<N_size; ++i) {
        out[0][i] = 2.0*i/N_size - 1.0;
        out[1][i] = sin(2*M_PI*out[0][i]*(dist_freq(generator_freq_noise))) + dist_amp(generator_amp_noise);
    }
    QVector<double> Qoutx = QVector<double>(out[0].begin(), out[0].end());
    QVector<double> Qouty = QVector<double>(out[1].begin(), out[1].end());
    emit dataReady(Qoutx, Qouty);
    std::vector<std::vector<double>> dataFFT = fftCalculation(out[1]);
    for (int i=0; i< N_size; ++i) {
        out[0][i] = dataFFT[0][i];
        out[1][i] = dataFFT[1][i];
    }
    Qoutx = QVector<double>(out[0].begin(), out[0].end());
    Qouty = QVector<double>(out[1].begin(), out[1].end());
    emit fftReady(Qoutx, Qouty);
}

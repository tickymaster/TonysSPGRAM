#include "TonysSPGRAM.h"
#include <algorithm>
#include <cmath>

void TonysSPGRAM::GenerateSpectogramMatrix(const std::vector<int16_t>& audioData, int binSize) {
    if (binSize <= 0) {
        throw std::invalid_argument("Bin size must be greater than 0.");
    }
    N = binSize;

    if (audioData.size() < N / 2) {
        throw std::invalid_argument("Audio data size is too small for the given bin size.");
    }

    f_increment = static_cast<int>(floor(44100.0 / binSize));

    numBins = (audioData.size() - N / 2) / (N / 2);

    SpectogramMatrix.resize(numBins, std::vector<CmplxNum>(N/2));

    for (size_t i = 0; i < numBins; i++)
    {
        size_t start = (N / 2) * i;
        size_t end = std::min(start + static_cast<size_t>(N), audioData.size());

        std::vector<int16_t> bin(audioData.begin() + start, audioData.begin() + end);
        bin.resize(N, 0);

        // Apply Hanning window
        for (size_t j = 0; j < bin.size(); j++) {
            double multiplier = 0.5 * (1 - cos(2 * 3.14 * j / (N - 1)));
            bin[j] = static_cast<int16_t>(bin[j] * multiplier);
        }

        TonysFFT fft;
        std::vector<CmplxNum> binResult = fft.FFT(bin);

        if (binResult.size() >= static_cast<size_t>(N / 2)) {
            binResult.resize(N / 2);
        }

        SpectogramMatrix[i] = binResult;
    }
}

const std::vector<std::vector<CmplxNum>>& TonysSPGRAM::GetSpectogramMatrix() const {
    return SpectogramMatrix;
}

const std::vector<double> TonysSPGRAM::GetTime() {
    //time reperesented by each individual fft eg: 1024/44100 of a second
    std::vector<double> TimeIndicies;
    
    double index = (N / 44100); // binLength/sampling rate

    for (size_t i = 0; i < N/2; i++)
    {
        TimeIndicies.push_back(i * index);
    }
    return TimeIndicies;
}

const std::vector<int> TonysSPGRAM::GetFreuqencies() {
    std::vector<int> indices;
    indices.resize(N / 2, 0);

    for (size_t i = 0; i < static_cast<size_t>(N/2); i++)
    {
        indices[i] = static_cast<int>(i * f_increment);
    }

    return indices;
}

std::vector<std::vector<double>> TonysSPGRAM::GetMagnitudeSpectogramMatrix() {
    std::vector<std::vector<double>> magnitudeDbMatrix(numBins, std::vector<double>(N / 2));
    for (size_t i = 0; i < numBins; i++) {
        for (size_t j = 0; j < static_cast<size_t>(N / 2); j++) {
            magnitudeDbMatrix[i][j] = SpectogramMatrix[i][j].getModulus();
        }
    }

    return magnitudeDbMatrix;
}

void TonysSPGRAM::ConvdB(std::vector<std::vector<double>>& magnitudeDbMatrix) {
    double epsilon = 1e-10; // Small value to avoid log(0)
    for (size_t i = 0; i < numBins; i++) {
        for (size_t j = 0; j < static_cast<size_t>(N / 2); j++) {
            magnitudeDbMatrix[i][j] = 20 * log10(magnitudeDbMatrix[i][j]+epsilon);
        }
    }
}

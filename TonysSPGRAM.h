#ifndef TONYSSPGRAM_H
#define TONYSSPGRAM_H

#include <vector>
#include "CmplxNum.h"
#include "TonysFFT.h"

class TonysSPGRAM {
public:
    // Generates a spectrogram from the given audio data
    void GenerateSpectogram(const std::vector<int16_t>& audioData, int binSize = 1024);

    // Returns the computed spectrogram matrix
    const std::vector<std::vector<CmplxNum>>& GetSpectogramMatrix() const;

    std::vector<std::vector<int16_t>>& GetMagnitudeSpectogramMatrix();

    const std::vector<int> GetFreuqencies();

    const std::vector<double> GetTime();

    int f_increment; //frequency increment (how much each index represents)

private:
    int N; // Size of each bin
    size_t numBins;
    std::vector<std::vector<CmplxNum>> SpectogramMatrix; // 2D matrix to store FFT results
    std::vector<std::vector<int16_t>> MagnitudeSpectogramMatrix;
};

#endif // TONYSSPGRAM_H

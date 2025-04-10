#ifndef TONYSFFT_H
#define TONYSFFT_H

#include <vector>
#include "CmplxNum.h"

class TonysFFT {
public:
	static void InitializeWArray(int N);
	static std::vector<std::vector<CmplxNum>> W;

	//fast fourier transforms
	std::vector<CmplxNum> FFT(std::vector<int16_t>& raw_data);
	std::vector<double> GetMagnitudes(const std::vector<CmplxNum>& fftResult);
private:
	void FFTRecursive(std::vector<CmplxNum>& data, int size);
	uint16_t reverseBits(uint16_t n, int numBits);
};

#endif // TONYSFFT_H
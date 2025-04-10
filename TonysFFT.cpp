//my libraries
#include "TonysFFT.h"
#include "WavFile.h"

#include "fstream"
#include "vector"
#include "sstream"
#include "filesystem"
#include "Windows.h"
#include "CmplxNum.h"
#include "iostream"
#include "string"
#include "algorithm"
#include "span"

//Ill try to create an fft algorithm using both integers and floating point numbers, for speed and precission respecfully.

std::vector<std::vector<CmplxNum>> TonysFFT::W;

void TonysFFT::InitializeWArray(int N) {
	using namespace std;
	const double PI = 3.14159265358979323846;
	const double TWO_PI_OVER_N = 2.0 * PI / double(N);

	W.resize(N, vector<CmplxNum>(N));
	CmplxNum W_base = CmplxNum(1, 0);
	W_base.setArgument(TWO_PI_OVER_N);

	for (size_t n = 0; n < N; n++) {
		for (size_t k = 0; k < N; k++) {
			W[n][k] = CmplxNum::Pow(W_base, n * k);
		}
	}
}

//MAKE SURE THE INPUT DATA IS OF OPERABLE SIZE WE DONT WANT TO CREATE A 
//FOURIER ARRAY OF 170K X 170K ENTRIES/ SPLIT IT UP INTO MORE MANAGABLE CHUNKS
//CAN BE OF 1024/512 ETC we will see

//figure out how to disect the initial array into smaller arrays whilst keeping the resultant vector the same 
//as when we dont split it

std::vector<CmplxNum> TonysFFT::FFT(std::vector<int16_t>& raw_data) {
	//radix-2 padding
	int N = raw_data.size();
	InitializeWArray(N/2); //checked in debug, for large values of N the program slows down significantly
	size_t power_of_2 = 1;
	while (power_of_2 < N) power_of_2 <<= 1;

	if (power_of_2 != N) {
		raw_data.resize(power_of_2, 0);
		N = power_of_2;
	}

	CmplxNum num = CmplxNum(1, 0);
	std::vector<CmplxNum> data(N);

	for (size_t i = 0; i < N; i++)
	{
		int numBits = log2(N);
		num.setReal(raw_data[reverseBits(i, numBits)]);
		data[i] = num;
	}

	this->FFTRecursive(data, N);

	return data;
}

void TonysFFT::FFTRecursive(std::vector<CmplxNum>& data, int size) {
	using namespace std;

	//recursive end case
	if (size <= 2)
	{
		CmplxNum temp = data[0];
		data[0] = data[0] + data[1];
		data[1] = temp - data[1];
		return;
	}
	//load the twiddle factors

	//no need to create even and odd arrays since the bit have been reversed
	//divide the array into 2 sub arrays

	vector<CmplxNum> First_half(size / 2); 
	vector<CmplxNum> Second_half(size / 2);

	copy(data.begin(), data.begin() + size / 2, First_half.begin());

	copy(data.begin() + size / 2, data.end(), Second_half.begin());


	//call FFTRecursive for both odd and even arrays

	FFTRecursive(First_half, size / 2);
	FFTRecursive(Second_half, size / 2);


	//when FFTRecursive returns perofrm the FFT math
	//X(K) = Even(k) + W(k)*Odd(k)
	//X(k+size/2) = Even(K) - W(k)*Odd(k)

	for (size_t k = 0; k < size / 2; k++)
	{
		CmplxNum t = W[k][size / 2] * Second_half[k];
		data[k] = First_half[k] + t;
		data[k + size / 2] = First_half[k] - t;
	}

}

std::vector<double> TonysFFT::GetMagnitudes(const std::vector<CmplxNum>& fftResult)
{
	std::vector<double> magnitudes;
	CmplxNum num;
	for (const auto& val : fftResult)
	{
		num = val;
		magnitudes.push_back(num.getModulus());
	}
	return magnitudes;
}

uint16_t TonysFFT::reverseBits(uint16_t n, int numBits) {
	uint16_t ans = 0;
	for (int i = 0; i < numBits; i++) {
		ans |= (n & 1) << (numBits - 1 - i);
		n >>= 1;
	}
	return ans;
}
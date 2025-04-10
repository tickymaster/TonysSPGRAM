#ifndef CMPLXNUM_H
#define CMPLXNUM_H

#include <iostream>
#include <cmath>
#include <string>

class CmplxNum {
private:
	double real;
	double imag;
	double modulus;
	double argument;

	void updateModArg();
	void updateRealImag();

public:
	CmplxNum(double real = 0.0, double imag = 0.0);

	void setReal(double newValue);
	double getReal();

	void setImag(double newValue);
	double getImag();

	void setModulus(double newValue);
	double getModulus();

	void setArgument(double newValue);
	double getArgument();

	friend std::ostream& operator<<(std::ostream& os, const CmplxNum& num);

	CmplxNum operator+ (const CmplxNum& other) const;
	CmplxNum operator- (const CmplxNum& other) const;
	CmplxNum operator* (const CmplxNum& other) const;
	CmplxNum operator/ (const CmplxNum& other) const;

	static CmplxNum Pow(const CmplxNum& a, int expo);

	static CmplxNum Parse(const std::string& str);

	std::string ToString() const;

	bool operator==(const CmplxNum& other) const;
};
#endif // CMPLXNUM_H

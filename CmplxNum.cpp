#include "CmplxNum.h"
#include "iostream"
#include <sstream>

// Constructor
CmplxNum::CmplxNum(double real, double imag) {
    this->real = real;
    this->imag = imag;
    this->updateModArg();
}

void CmplxNum::setReal(double newValue) {
    this->real = newValue;
    this->updateModArg();
}

double CmplxNum::getReal() {
    return this->real;
}

void CmplxNum::setImag(double newValue) {
    this->imag = newValue;
    this->updateModArg();
}

double CmplxNum::getImag() {
    return this->imag;
}

void CmplxNum::setModulus(double newValue) {
    this->modulus = newValue;
    this->updateRealImag();
}

double CmplxNum::getModulus() {
    return this->modulus;
}

void CmplxNum::setArgument(double newValue) {
    this->argument = newValue;
    this->updateRealImag();
}

double CmplxNum::getArgument() {
    return this->argument;
}

void CmplxNum::updateModArg() {
    this->modulus = sqrt(pow(this->real, 2) + pow(this->imag, 2));
    this->argument = std::atan2(this->imag, this->real);
}

void CmplxNum::updateRealImag() {
    this->real = this->modulus * cos(this->argument);
    this->imag = this->modulus * sin(this->argument);
}

std::ostream& operator<<(std::ostream& os, const CmplxNum& num) {
    os << num.real << "+" << num.imag << "i";
    return os;
}

CmplxNum CmplxNum::operator+(const CmplxNum& other) const {
    return CmplxNum(this->real + other.real, this->imag + other.imag);
}

CmplxNum CmplxNum::operator-(const CmplxNum& other) const {
    return CmplxNum(this->real - other.real, this->imag - other.imag);
}

CmplxNum CmplxNum::operator*(const CmplxNum& other) const {
    double realSum = (this->real * other.real) - (this->imag * other.imag);
    double imagSum = (this->real * other.imag) + (this->imag * other.imag);
    return CmplxNum(realSum, imagSum);
}

CmplxNum CmplxNum::operator/(const CmplxNum& other) const {
	double denominator = pow(other.real,2) + pow(other.imag,2);
    double realQuotient = ((this->real * other.real) + (this->imag * other.imag)) / denominator;
    double imagQuotient = ((this->imag * other.real) - (this->real * other.imag)) / denominator;
    return CmplxNum(realQuotient, imagQuotient);
}
CmplxNum CmplxNum::Pow(const CmplxNum& a, int expo) {
    double raisedModulus = pow(a.modulus, expo);
    double multipliedArgument = a.argument * expo;
    CmplxNum result = CmplxNum(0, 0);
    result.setModulus(raisedModulus);
    result.setArgument(multipliedArgument);
    return result;
}

CmplxNum CmplxNum::Parse(const std::string& str) {
    double real = 0.0;
    double imag = 0.0;

    std::size_t iPos = str.find("i");
    if (iPos == std::string::npos) {
        std::cerr << "Invalid complex number format" << std::endl;
        return CmplxNum(real, imag);
    }

    std::string numPart = str.substr(0, iPos);

    std::size_t pos = numPart.find_last_of("+-", numPart.size() - 2);

    if (pos != std::string::npos) {
        real = std::stod(numPart.substr(0, pos));
        imag = std::stod(numPart.substr(pos));
    }
    else {
        std::cerr << "Invalid complex number format" << std::endl;
    }

    return CmplxNum(real, imag);
}

std::string CmplxNum::ToString() const {
    std::ostringstream oss;
    oss << this->real << "+" << this->imag << "i";
    return oss.str();
}

bool CmplxNum::operator==(const CmplxNum& other) const {
    return this->real == other.real && this->imag == other.imag;
}

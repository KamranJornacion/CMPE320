#pragma once
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

class Fraction{
private:
    int num;
    int denom;
    void normalize();
    static int gcd(int a, int b);

public:

    Fraction(int num);
    Fraction(int num1, int num2);
    Fraction();

    int numerator() const;
    int denominator() const;

    Fraction operator-() const;

    Fraction& operator++();
    Fraction operator++(int);

    Fraction& operator+=(const Fraction& rhs);
    Fraction& operator+=(int rhs);

    friend ostream& operator<<(ostream& os, const Fraction& f);
    friend istream& operator>>(istream& is, Fraction& f);

    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, const Fraction& b);

    friend bool operator==(const Fraction& a, const Fraction& b);
    friend bool operator!=(const Fraction& a, const Fraction& b);
    friend bool operator<(const Fraction& a, const Fraction& b);
    friend bool operator<=(const Fraction& a, const Fraction& b);
    friend bool operator>(const Fraction& a, const Fraction& b);
    friend bool operator>=(const Fraction& a, const Fraction& b);

};

class FractionException: public runtime_error{
public:
    using runtime_error::runtime_error;
};
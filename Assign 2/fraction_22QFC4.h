#ifndef FRACTION_22QFC4_H
#define FRACTION_22QFC4_H

#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

//class that stores fraction
class Fraction{
private:
    //numerator of frac
    int num;
    //denominator of frace
    int denom;

    //computes the greatest common divisor 
    static int gcd(int a, int b);
    //uses gcd to reduce fraction, and keep sign with numerator
    void normalize();

public:
    //Fraction constuctor from integer
    Fraction(int num);
    //Fraction constructor from numerator and denonimator
    Fraction(int numerator, int denominator);

    //Fraction constructor defaults to 0/1
    Fraction();

    //returns numerator and denominator accordingly
    int numerator() const;
    int denominator() const;

    //overwrite urnary minus
    Fraction operator-() const;
    //overwrite pre-increment
    Fraction& operator++();
    //overwrite post-increment
    Fraction operator++(int);
    //adds rhs to this fraction (rhs is Fraction)
    Fraction& operator+=(const Fraction& rhs);
    //adds rhs to this fraction (rhs is integer)
    Fraction& operator+=(int rhs);
    //output as "num/denom" or "num" when denom is 1
    friend ostream& operator<<(ostream& os, const Fraction& f);
    //input as "num1/num2" or "num1" (and check num2 nonzero)
    friend istream& operator>>(istream& is, Fraction& f);

    //Overwrites binary +,-,*,/ and returns reduced form
    friend Fraction operator+(const Fraction& a, const Fraction& b);
    friend Fraction operator-(const Fraction& a, const Fraction& b);
    friend Fraction operator*(const Fraction& a, const Fraction& b);
    friend Fraction operator/(const Fraction& a, const Fraction& b);

    //Checks equality after normalization
    friend bool operator==(const Fraction& a, const Fraction& b);
    //Checks inequality after normalization
    friend bool operator!=(const Fraction& a, const Fraction& b);
    //Checks less-than using corss-multiplication
    friend bool operator<(const Fraction& a, const Fraction& b);
    //checks less or equal
    friend bool operator<=(const Fraction& a, const Fraction& b);
    //checks greater than
    friend bool operator>(const Fraction& a, const Fraction& b);
    //checks greater than or equal
    friend bool operator>=(const Fraction& a, const Fraction& b);

};

//Custom Exception class that is used to indicate when invalid fraction operation/state occurs
class FractionException: public runtime_error{
public:
    //use runtime_error constructors
    using runtime_error::runtime_error;
};

#endif // FRACTION_22QFC4_H
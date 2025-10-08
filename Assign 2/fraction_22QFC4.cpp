#include "fraction_22QFC4.h"
#include <cstdlib>
using namespace std;

//helper to prevent overflow during multiplication
static inline long long cross(long long a, long long b) { return a * b; }

//Fraction Methods and constructors ----------------

//Uses Eulid's algo to find gcd
int Fraction::gcd(int a, int b) {

    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}


void Fraction::normalize() {
    //verify valid denom
    if (denom == 0) throw FractionException("denominator can't be zero");
    //format to ensure numerator carries sign
    if (num == 0) { denom = 1; return; }
    if (denom < 0) { denom = -denom; num = -num; }
    //reduce fraction
    int g = gcd(num, denom);
    if (g) { num /= g; denom /= g; }
}

//Construct as 0/1
Fraction::Fraction() : num(0), denom(1) {}

//Construct as n/1
Fraction::Fraction(int n) : num(n), denom(1) {}

//Construct as n/d then normalize format
Fraction::Fraction(int n, int d) : num(n), denom(d) { normalize(); }

//Access numerator or denominator accordingly
int Fraction::numerator() const { return num; }
int Fraction::denominator() const { return denom; }

//Overwrite urnary minus
Fraction Fraction::operator-() const {
    Fraction r(*this);
    r.num = -r.num;
    return r;
}

 //overwrite pre-increment
Fraction& Fraction::operator++() {
    num += denom;
    return *this;
}
//overwrite post-increment
Fraction Fraction::operator++(int) {
    Fraction tmp(*this);
    num += denom;
    return tmp;
}
//adds rhs to this fraction (rhs is Fraction)
Fraction& Fraction::operator+=(const Fraction& rhs) {
    long long n = cross(num, rhs.denom) + cross(rhs.num, denom);
    long long d = cross(denom, rhs.denom);
    num = static_cast<int>(n);
    denom = static_cast<int>(d);
    normalize();
    return *this;
}
 //adds rhs to this fraction (rhs is integer)
Fraction& Fraction::operator+=(int rhs) {
    long long n = num + cross(static_cast<long long>(rhs), denom);
    num = static_cast<int>(n);
    normalize();
    return *this;
}
//output as "num/denom" or "num" when denom is 1
ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.num << "/" << f.denom;
    return os;
}
//input as "num1/num2" or "num1" (and check num2 nonzero)
istream& operator>>(istream& is, Fraction& f) {
    int n = 0, d = 1;
    if (!(is >> n)) { is.setstate(ios::failbit); return is; }
    if (is.peek() == '/') {
        is.get();
        if (!(is >> d)) { is.setstate(ios::failbit); return is; }
    }
    if (d == 0) { is.setstate(ios::failbit); throw FractionException("denominator cannot be zero"); }
    f.num = n;
    f.denom = d;
    f.normalize();
    return is;
}
//Overwrites binary +,-,*,/ and returns reduced form---------------
Fraction operator+(const Fraction& a, const Fraction& b) {
    Fraction r;
    long long n = cross(a.num, b.denom) + cross(b.num, a.denom);
    long long d = cross(a.denom, b.denom);
    r.num = static_cast<int>(n);
    r.denom = static_cast<int>(d);
    r.normalize();
    return r;
}
Fraction operator-(const Fraction& a, const Fraction& b) {
    Fraction r;
    long long n = cross(a.num, b.denom) - cross(b.num, a.denom);
    long long d = cross(a.denom, b.denom);
    r.num = static_cast<int>(n);
    r.denom = static_cast<int>(d);
    r.normalize();
    return r;
}
Fraction operator*(const Fraction& a, const Fraction& b) {
    Fraction r;
    long long n = cross(a.num, b.num);
    long long d = cross(a.denom, b.denom);
    r.num = static_cast<int>(n);
    r.denom = static_cast<int>(d);
    r.normalize();
    return r;
}
Fraction operator/(const Fraction& a, const Fraction& b) {
    if (b.num == 0) throw FractionException("division by zero fraction");
    Fraction r;
    long long n = cross(a.num, b.denom);
    long long d = cross(a.denom, b.num);
    r.num = static_cast<int>(n);
    r.denom = static_cast<int>(d);
    r.normalize();
    return r;
}
//---------------------------------------------------------------

//Check equality
bool operator==(const Fraction& a, const Fraction& b) {
    return cross(a.num, b.denom) == cross(b.num, a.denom);
}
//Check inequality
bool operator!=(const Fraction& a, const Fraction& b) {
    return !(a == b);
}
//Checks less-than using cross-multiplication
bool operator<(const Fraction& a, const Fraction& b) {
    return cross(a.num, b.denom) < cross(b.num, a.denom);
}
//checks less or equal
bool operator<=(const Fraction& a, const Fraction& b) {
    return !(b < a);
}
//checks greater than
bool operator>(const Fraction& a, const Fraction& b) {
    return b < a;
}
//checks greater than or equal
bool operator>=(const Fraction& a, const Fraction& b) {
    return !(a < b);
}

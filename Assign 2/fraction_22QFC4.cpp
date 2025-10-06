#include "fraction_22QFC4.h"
#include <cstdlib>

using namespace std;

static inline long long cross(long long a, long long b) { return a * b; }

int Fraction::gcd(int a, int b) {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

void Fraction::normalize() {
    if (denom == 0) throw FractionException("denominator cannot be zero");
    if (num == 0) { denom = 1; return; }
    if (denom < 0) { denom = -denom; num = -num; }
    int g = gcd(num, denom);
    if (g) { num /= g; denom /= g; }
}

Fraction::Fraction() : num(0), denom(1) {}

Fraction::Fraction(int n) : num(n), denom(1) {}

Fraction::Fraction(int n, int d) : num(n), denom(d) { normalize(); }

int Fraction::numerator() const { return num; }

int Fraction::denominator() const { return denom; }

Fraction Fraction::operator-() const {
    Fraction r(*this);
    r.num = -r.num;
    return r;
}

Fraction& Fraction::operator++() {
    num += denom;
    return *this;
}

Fraction Fraction::operator++(int) {
    Fraction tmp(*this);
    num += denom;
    return tmp;
}

Fraction& Fraction::operator+=(const Fraction& rhs) {
    long long n = cross(num, rhs.denom) + cross(rhs.num, denom);
    long long d = cross(denom, rhs.denom);
    num = static_cast<int>(n);
    denom = static_cast<int>(d);
    normalize();
    return *this;
}

Fraction& Fraction::operator+=(int rhs) {
    long long n = num + cross(static_cast<long long>(rhs), denom);
    num = static_cast<int>(n);
    normalize();
    return *this;
}

ostream& operator<<(ostream& os, const Fraction& f) {
    os << f.num << "/" << f.denom;
    return os;
}

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

bool operator==(const Fraction& a, const Fraction& b) {
    return cross(a.num, b.denom) == cross(b.num, a.denom);
}

bool operator!=(const Fraction& a, const Fraction& b) {
    return !(a == b);
}

bool operator<(const Fraction& a, const Fraction& b) {
    return cross(a.num, b.denom) < cross(b.num, a.denom);
}

bool operator<=(const Fraction& a, const Fraction& b) {
    return !(b < a);
}

bool operator>(const Fraction& a, const Fraction& b) {
    return b < a;
}

bool operator>=(const Fraction& a, const Fraction& b) {
    return !(a < b);
}

#pragma once
#include <sstream>
#include <numeric>
#include <cstdint>

// Реализуйте класс Rational.
class Rational {
public:
    Rational() = default;

    Rational(int numerator) : numerator_(numerator) {}

    Rational(int numerator, int denominator)
        : numerator_(numerator)
        , denominator_(denominator) {
        Reduction();
    }

    Rational(const Rational& r) = default;

    Rational Inv() const {
        return Rational{denominator_, numerator_};
    }

    int GetNumerator() const {
        return numerator_;
    }

    int GetDenominator() const {
        return denominator_;
    }

    Rational& operator+=(const Rational& r) {
        numerator_ = (numerator_ * r.denominator_) + (r.numerator_ * denominator_);
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& r) {
        numerator_ = (numerator_ * r.denominator_) - (r.numerator_ * denominator_);
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& r) {
        numerator_ *= r.numerator_;
        denominator_ *= r.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& r) {
        numerator_ *= r.denominator_;
        denominator_ *= r.numerator_;
        Reduction();
        return *this;
    }

    Rational& operator=(int num) {
        numerator_ = num;
        return *this;
    }

    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return {-numerator_, denominator_};
    }

    friend std::istream& operator>>(std::istream& is, Rational& rational);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

inline Rational operator+(Rational r1, const Rational& r2) {
    return r1 += r2;
}

inline Rational operator-(Rational r1, const Rational& r2) {
    return r1 -= r2;
}

inline Rational operator*(Rational r1, const Rational& r2) {
    return r1 *= r2;
}

inline Rational operator/(Rational r1, const Rational& r2) {
    return r1 /= r2;
}

inline std::istream& operator>>(std::istream& is, Rational& rational) {
    int numerator;
    char op;

    if (!(is >> numerator)) return is;

    if (!(is >> op)) {
        is.clear();
        rational.numerator_ = numerator;
        rational.denominator_ = 1;
        return is;
    }

    if (op != '/') {
        is.unget();
        rational.numerator_ = numerator;
        rational.denominator_ = 1;
        return is;
    }

    int denominator;
    if (!(is >> denominator) || denominator == 0) {
        is.setstate(std::ios::failbit);
        return is;
    }

    rational.numerator_ = numerator;
    rational.denominator_ = denominator;
    rational.Reduction();
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& rational) {
    if (rational.denominator_ == 1) {
        os << rational.numerator_;
        return os;
    }
    os << rational.numerator_ << " / " << rational.denominator_;
    return os;
}

inline auto operator<=>(const Rational& r1, const Rational& r2) {
    std::int64_t a = static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator();
    std::int64_t b = static_cast<std::int64_t>(r2.GetNumerator()) * r1.GetDenominator();
    return a <=> b;
}

inline bool operator==(const Rational& r1, const Rational& r2) {
    std::int64_t a = static_cast<std::int64_t>(r1.GetNumerator()) * r2.GetDenominator();
    std::int64_t b = static_cast<std::int64_t>(r2.GetNumerator()) * r1.GetDenominator();
    return a == b;
}
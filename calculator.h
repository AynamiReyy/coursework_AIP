
#pragma once

#include <string>
#include <optional>
#include <cmath>
#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:

    bool GetHasMem() const {
        return mem_.has_value();
    }

    void Save() {
        mem_ = number_;
    }

    void Load() {
        if (mem_.has_value()) {
            number_ = mem_.value();
        }
    }

    void ClearMem() {
        mem_ = std::nullopt;
    }

    void Set(const Number& n) {
        number_ = n;
    }

    const Number& GetNumber() const {
        return  number_;
    }

    std::optional<Error> Add(const Number& n) {
        number_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(const Number& n) {
        number_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Div(const Number& n) {
        if constexpr (std::is_integral_v<Number>) {
            if(n == 0) {
                return "Division by zero";
            }

            number_ /= n;
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if(n.GetNumerator() == 0) {
                return "Division by zero";
            }

            number_ /= n;
            return std::nullopt;
        } else {
            number_ /= n;
            return std::nullopt;
        }
    }

    std::optional<Error> Mul(const Number& n) {
        number_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(const Number& n) {
        if constexpr (std::is_integral_v<Number>) {
            if (number_ == 0 && n == 0) {
                return "Zero power to zero";
            }
            if (n < 0) {
                return "Integer negative power";
            }
            number_ = IntegerPow(number_, n);
            return std::nullopt;
        } else if constexpr (std::is_same_v<Number, Rational>) {
            if (number_.GetNumerator() == 0 && n.GetNumerator() == 0) {
                return "Zero power to zero";
            }
            if (n.GetDenominator() != 1) {
                return "Fractional power is not supported";
            }
            number_ = ::Pow(number_, n);
            return std::nullopt;
        } else {
            number_ = std::pow(number_, n);
            return std::nullopt;
        }
    }

private:

    Number number_ = {};
    std::optional<Number> mem_;
};
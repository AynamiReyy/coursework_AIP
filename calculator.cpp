#include "calculator.h"

void Calculator::Set(Number n) {
    number_ = n;
}

Number Calculator::GetNumber() const {
    return  number_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(number_);
}

void Calculator::Add(Number n) {
    number_ += n;
}

void Calculator::Sub(Number n) {
    number_ -= n;
}

void Calculator::Div(Number n) {
    number_ /= n;
}

void Calculator::Mul(Number n) {
    number_ *= n;
}

void Calculator::Pow(Number n) {
    number_ = std::pow(number_, n);
}
//
// Created by Kane York on 1/9/18.
//

#include "Double.hpp"

Double::Double() : value(0) {}

Double::Double(double val) : value(val) {}

Double::Double(Double const &src) : value(src.value) {}

Double::~Double() {}

Double &Double::operator=(Double const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Double::make_self(double val) const {
    return new Double(val);
}
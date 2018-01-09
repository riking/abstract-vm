//
// Created by Kane York on 1/9/18.
//

#include "Int16.hpp"

Int16::Int16() : value(0) {}

Int16::Int16(uint16_t val) : value(val) {}

Int16::Int16(Int16 const &src) : value(src.value) {}

Int16::~Int16() {}

Int16 &Int16::operator=(Int16 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int16::make_self(uint16_t val) const {
    return new Int16(val);
}

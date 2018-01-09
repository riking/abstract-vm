//
// Created by Kane York on 1/9/18.
//

#include "Int8.hpp"

Int8::Int8() : value(0) {}

Int8::Int8(int8_t val) : value(val) {}

Int8::Int8(Int8 const &src) : value(src.value) {}

Int8::~Int8() {}

Int8 &Int8::operator=(Int8 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int8::make_self(int8_t val) const {
    return new Int8(val);
}

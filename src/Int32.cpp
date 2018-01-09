//
// Created by Kane York on 1/9/18.
//

#include "Int32.hpp"

Int32::Int32() : value(0) {}

Int32::Int32(int32_t val) : value(val) {}

Int32::Int32(Int32 const &src) : value(src.value) {}

Int32::~Int32() {}

Int32 &Int32::operator=(Int32 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int32::make_self(int32_t val) const {
    return new Int32(val);
}

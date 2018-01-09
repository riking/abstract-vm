//
// Created by Kane York on 1/9/18.
//

#include "Int8.hpp"

#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"
#include "Double.hpp"

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

virtual IOperand const *Int8::operator+(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return *this + static_cast<const Int8 &>(rhs);
        case eOperandType::INT_16:
            return *this + static_cast<const Int16 &>(rhs);
        case eOperandType::INT_32:
            return *this + static_cast<const Int32 &>(rhs);
        case eOperandType::FLOAT:
            return *this + static_cast<const Float &>(rhs);
        case eOperandType::DOUBLE:
            return *this + static_cast<const Double &>(rhs);
    }
}

virtual IOperand const *Int8::operator-(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return *this - static_cast<const Int8 &>(rhs);
        case eOperandType::INT_16:
            return *this - static_cast<const Int16 &>(rhs);
        case eOperandType::INT_32:
            return *this - static_cast<const Int32 &>(rhs);
        case eOperandType::FLOAT:
            return *this - static_cast<const Float &>(rhs);
        case eOperandType::DOUBLE:
            return *this - static_cast<const Double &>(rhs);
    }
}

virtual IOperand const *Int8::operator*(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return *this * static_cast<const Int8 &>(rhs);
        case eOperandType::INT_16:
            return *this * static_cast<const Int16 &>(rhs);
        case eOperandType::INT_32:
            return *this * static_cast<const Int32 &>(rhs);
        case eOperandType::FLOAT:
            return *this * static_cast<const Float &>(rhs);
        case eOperandType::DOUBLE:
            return *this * static_cast<const Double &>(rhs);
    }
}

virtual IOperand const *Int8::operator/(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return *this / static_cast<const Int8 &>(rhs);
        case eOperandType::INT_16:
            return *this / static_cast<const Int16 &>(rhs);
        case eOperandType::INT_32:
            return *this / static_cast<const Int32 &>(rhs);
        case eOperandType::FLOAT:
            return *this / static_cast<const Float &>(rhs);
        case eOperandType::DOUBLE:
            return *this / static_cast<const Double &>(rhs);
    }
}

virtual IOperand const *Int8::operator%(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return *this % static_cast<const Int8 &>(rhs);
        case eOperandType::INT_16:
            return *this % static_cast<const Int16 &>(rhs);
        case eOperandType::INT_32:
            return *this % static_cast<const Int32 &>(rhs);
        case eOperandType::FLOAT:
            return *this % static_cast<const Float &>(rhs);
        case eOperandType::DOUBLE:
            return *this % static_cast<const Double &>(rhs);
    }
}

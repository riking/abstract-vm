//
// Created by Kane York on 1/9/18.
//

#include "Int32.hpp"

#include "Int8.hpp"
#include "Int16.hpp"
#include "Float.hpp"
#include "Double.hpp"

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

virtual IOperand const *Int32::operator+(IOperand const &rhs) const {
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

virtual IOperand const *Int32::operator-(IOperand const &rhs) const {
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

virtual IOperand const *Int32::operator*(IOperand const &rhs) const {
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

virtual IOperand const *Int32::operator/(IOperand const &rhs) const {
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

virtual IOperand const *Int32::operator%(IOperand const &rhs) const {
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

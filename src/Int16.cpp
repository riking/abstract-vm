//
// Created by Kane York on 1/9/18.
//

#include "Int16.hpp"

#include "Double.hpp"
#include "Float.hpp"
#include "Int32.hpp"
#include "Int8.hpp"

Int16::Int16() : AbstractOperand(0) {}

Int16::Int16(int16_t val) : AbstractOperand(val) {}

Int16::Int16(Int16 const &src) : AbstractOperand(src.value) {}

Int16::~Int16() {}

Int16 &Int16::operator=(Int16 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int16::make_self(int16_t val) const { return new Int16(val); }

IOperand const *Int16::operator+(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return this->_add(static_cast<const Int8 &>(rhs));
        case eOperandType::INT_16:
            return this->_add(static_cast<const Int16 &>(rhs));
        case eOperandType::INT_32:
            return this->_add(static_cast<const Int32 &>(rhs));
        case eOperandType::FLOAT:
            return this->_add(static_cast<const Float &>(rhs));
        case eOperandType::DOUBLE:
            return this->_add(static_cast<const Double &>(rhs));
        default:
            throw StaticError("Bad operand type");
    }
}

IOperand const *Int16::operator-(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return this->_sub(static_cast<const Int8 &>(rhs));
        case eOperandType::INT_16:
            return this->_sub(static_cast<const Int16 &>(rhs));
        case eOperandType::INT_32:
            return this->_sub(static_cast<const Int32 &>(rhs));
        case eOperandType::FLOAT:
            return this->_sub(static_cast<const Float &>(rhs));
        case eOperandType::DOUBLE:
            return this->_sub(static_cast<const Double &>(rhs));
        default:
            throw StaticError("Bad operand type");
    }
}

IOperand const *Int16::operator*(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return this->_mul(static_cast<const Int8 &>(rhs));
        case eOperandType::INT_16:
            return this->_mul(static_cast<const Int16 &>(rhs));
        case eOperandType::INT_32:
            return this->_mul(static_cast<const Int32 &>(rhs));
        case eOperandType::FLOAT:
            return this->_mul(static_cast<const Float &>(rhs));
        case eOperandType::DOUBLE:
            return this->_mul(static_cast<const Double &>(rhs));
        default:
            throw StaticError("Bad operand type");
    }
}

IOperand const *Int16::operator/(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return this->_div(static_cast<const Int8 &>(rhs));
        case eOperandType::INT_16:
            return this->_div(static_cast<const Int16 &>(rhs));
        case eOperandType::INT_32:
            return this->_div(static_cast<const Int32 &>(rhs));
        case eOperandType::FLOAT:
            return this->_div(static_cast<const Float &>(rhs));
        case eOperandType::DOUBLE:
            return this->_div(static_cast<const Double &>(rhs));
        default:
            throw StaticError("Bad operand type");
    }
}

IOperand const *Int16::operator%(IOperand const &rhs) const {
    switch (rhs.getType()) {
        case eOperandType::INT_8:
            return this->_mod(static_cast<const Int8 &>(rhs));
        case eOperandType::INT_16:
            return this->_mod(static_cast<const Int16 &>(rhs));
        case eOperandType::INT_32:
            return this->_mod(static_cast<const Int32 &>(rhs));
        case eOperandType::FLOAT:
            return this->_mod(static_cast<const Float &>(rhs));
        case eOperandType::DOUBLE:
            return this->_mod(static_cast<const Double &>(rhs));
        default:
            throw StaticError("Bad operand type");
    }
}

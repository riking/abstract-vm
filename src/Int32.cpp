//
// Created by Kane York on 1/9/18.
//

#include "Int32.hpp"

#include "Double.hpp"
#include "Float.hpp"
#include "Int16.hpp"
#include "Int8.hpp"

Int32::Int32() : AbstractOperand(0) {}

Int32::Int32(int32_t val) : AbstractOperand(val) {}

Int32::Int32(Int32 const &src) : AbstractOperand(src.value) {}

Int32::~Int32() {}

Int32 &Int32::operator=(Int32 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int32::make_self(int32_t val) const { return new Int32(val); }

IOperand const *Int32::operator+(IOperand const &rhs) const {
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

IOperand const *Int32::operator-(IOperand const &rhs) const {
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

IOperand const *Int32::operator*(IOperand const &rhs) const {
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

IOperand const *Int32::operator/(IOperand const &rhs) const {
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

IOperand const *Int32::operator%(IOperand const &rhs) const {
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

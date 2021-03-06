//
// Created by Kane York on 1/9/18.
//

#include "Float.hpp"

#include "Double.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Int8.hpp"

Float::Float() : AbstractOperand(0.f) {}

Float::Float(float val) : AbstractOperand(val) {}

Float::Float(Float const &src) : AbstractOperand(src.value) {}

Float::~Float() {}

Float &Float::operator=(Float const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Float::operator+(IOperand const &rhs) const {
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

IOperand const *Float::operator-(IOperand const &rhs) const {
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

IOperand const *Float::operator*(IOperand const &rhs) const {
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

IOperand const *Float::operator/(IOperand const &rhs) const {
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

IOperand const *Float::operator%(IOperand const &rhs) const {
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

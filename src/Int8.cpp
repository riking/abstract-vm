//
// Created by Kane York on 1/9/18.
//

#include "Int8.hpp"

#include "Double.hpp"
#include "Float.hpp"
#include "Int16.hpp"
#include "Int32.hpp"

Int8::Int8() : AbstractOperand(0) {}

Int8::Int8(int8_t val) : AbstractOperand(val) {}

Int8::Int8(Int8 const &src) : AbstractOperand(src.value) {}

Int8::~Int8() {}

Int8 &Int8::operator=(Int8 const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Int8::make_self(int8_t val) const { return new Int8(val); }

int8_t const Int8::GetInt8() const { return this->value; }

IOperand const *Int8::operator+(IOperand const &rhs) const {
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
    }
}

IOperand const *Int8::operator-(IOperand const &rhs) const {
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
    }
}

IOperand const *Int8::operator*(IOperand const &rhs) const {
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
    }
}

IOperand const *Int8::operator/(IOperand const &rhs) const {
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
    }
}

template <eOperandType RhsOpType, typename RHSValueT>
IOperand const *Int8::_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    if (this->getPrecision() < rhs.getPrecision()) {
        RHSValueT new_value_r = ((RHSValueT)this->value) % rhs.get();
        return rhs.make_self(new_value_r);
    } else {
        int8_t new_value_s = this->value % ((int8_t)rhs.get());
        return this->make_self(new_value_s);
    }
}

template <>
IOperand const *Int8::_mod(AbstractOperand<eOperandType::FLOAT, float> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    float new_value = fmodf((float)this->value, rhs.get());
    return rhs.make_self(new_value);
}

template <>
IOperand const *Int8::_mod(AbstractOperand<eOperandType::DOUBLE, double> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    double new_value = fmod((double)this->value, rhs.get());
    return rhs.make_self(new_value);
}

IOperand const *Int8::operator%(IOperand const &rhs) const {
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
    }
}

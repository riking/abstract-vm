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

IOperand const *Int16::operator-(IOperand const &rhs) const {
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

IOperand const *Int16::operator*(IOperand const &rhs) const {
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

IOperand const *Int16::operator/(IOperand const &rhs) const {
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

template <eOperandType RhsOpType, typename RHSValueT>
IOperand const *Int16::_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    if (this->getPrecision() < rhs.getPrecision()) {
        RHSValueT new_value_r = ((RHSValueT)this->value) % rhs.get();
        return rhs.make_self(new_value_r);
    } else {
        int16_t new_value_s = this->value % ((int16_t)rhs.get());
        return this->make_self(new_value_s);
    }
}

template <>
IOperand const *Int16::_mod(AbstractOperand<eOperandType::FLOAT, float> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    float new_value = fmodf((float)this->value, rhs.get());
    return rhs.make_self(new_value);
}

template <>
IOperand const *Int16::_mod(AbstractOperand<eOperandType::DOUBLE, double> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    double new_value = fmod((double)this->value, rhs.get());
    return rhs.make_self(new_value);
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
    }
}

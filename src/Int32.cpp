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

IOperand const *Int32::operator-(IOperand const &rhs) const {
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

IOperand const *Int32::operator*(IOperand const &rhs) const {
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

IOperand const *Int32::operator/(IOperand const &rhs) const {
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
IOperand const *Int32::_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    if (this->getPrecision() < rhs.getPrecision()) {
        RHSValueT new_value_r = ((RHSValueT)this->value) % rhs.get();
        return rhs.make_self(new_value_r);
    } else {
        int32_t new_value_s = this->value % ((int32_t)rhs.get());
        return this->make_self(new_value_s);
    }
}

template <>
IOperand const *Int32::_mod(AbstractOperand<eOperandType::FLOAT, float> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    float new_value = fmodf((float)this->value, rhs.get());
    return rhs.make_self(new_value);
}

template <>
IOperand const *Int32::_mod(AbstractOperand<eOperandType::DOUBLE, double> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    double new_value = fmod((double)this->value, rhs.get());
    return rhs.make_self(new_value);
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
    }
}

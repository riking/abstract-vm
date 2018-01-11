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

IOperand const *Float::make_self(float val) const { return new Float(val); }

IOperand const *Float::operator+(IOperand const &rhs) const {
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

IOperand const *Float::operator-(IOperand const &rhs) const {
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

IOperand const *Float::operator*(IOperand const &rhs) const {
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

IOperand const *Float::operator/(IOperand const &rhs) const {
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
IOperand const *Float::_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    float new_value = fmodf(this->value, (float)rhs.get());
    return this->make_self(new_value);
}

template <>
IOperand const *Float::_mod(AbstractOperand<eOperandType::DOUBLE, double> const &rhs) const {
    if (rhs.get() == 0) {
        throw Div0Error();
    }

    double new_value = fmod((double)this->value, rhs.get());
    return rhs.make_self(new_value);
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
    }
}

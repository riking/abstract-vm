//
// Created by Kane York on 1/9/18.
//

#include "Double.hpp"

#include "Int8.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Float.hpp"

Double::Double() : value(0) {}

Double::Double(double val) : value(val) {}

Double::Double(Double const &src) : value(src.value) {}

Double::~Double() {}

Double &Double::operator=(Double const &rhs) {
    this->value = rhs.value;
    return *this;
}

IOperand const *Double::make_self(double val) const {
    return new Double(val);
}

virtual IOperand const *Double::operator+(IOperand const &rhs) const {
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

virtual IOperand const *Double::operator-(IOperand const &rhs) const {
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

virtual IOperand const *Double::operator*(IOperand const &rhs) const {
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

virtual IOperand const *Double::operator/(IOperand const &rhs) const {
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

virtual IOperand const *Double::operator%(IOperand const &rhs) const {
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

//
// Created by Kane York on 1/9/18.
//

#ifndef PROJECT_INT_HPP
#define PROJECT_INT_HPP

#include "Div0Error.hpp"
#include "IOperand.hpp"
#include "OperandType.hpp"
#include "StaticError.hpp"

#include <cmath>
#include <sstream>
#include <type_traits>

class Int8;
class Int16;
class Int32;
class Float;
class Double;

template <eOperandType Type, typename ValueT>
class AbstractOperand : public IOperand {
   public:
    ~AbstractOperand(){};

    AbstractOperand(ValueT value) : value(value){};

    virtual int getPrecision(void) const {
        if (Type == eOperandType::INT_8) {
            return 8;
        } else if (Type == eOperandType::INT_16) {
            return 16;
        } else if (Type == eOperandType::INT_32) {
            return 32;
        } else if (Type == eOperandType::FLOAT) {
            return 36;
        } else if (Type == eOperandType::DOUBLE) {
            return 72;
        }
        return 0;
    }

    virtual eOperandType getType(void) const { return Type; }

    virtual std::string const &toString(void) const {
        std::stringstream ss;
        ss << value;
        return *(new std::string(ss.str()));
    }

    virtual bool operator==(IOperand const &rhs) const {
        if (this->getType() != rhs.getType()) {
            return false;
        }
        auto const &casted_rhs =
            static_cast<AbstractOperand<Type, ValueT> const &>(rhs);

        if (Type == eOperandType::FLOAT || Type == eOperandType::DOUBLE) {
            if (isnan(this->value) && isnan(casted_rhs.value)) {
                return true;
            }
        }

        return !(this->value != casted_rhs.value);
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *operator+(
        AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        if (this->getPrecision() < rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT)this->value) + rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value + ((ValueT)rhs.value);
            return this->make_self(new_value_s);
        }
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *operator-(
        AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        if (this->getPrecision() < rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT)this->value) - rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value - ((ValueT)rhs.value);
            return this->make_self(new_value_s);
        }
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *operator*(
        AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        if (this->getPrecision() < rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT)this->value) * rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value * ((ValueT)rhs.value);
            return this->make_self(new_value_s);
        }
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *operator/(
        AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        if (rhs.value == 0) {
            throw Div0Error();
        }

        if (this->getPrecision() < rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT)this->value) / rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value / ((ValueT)rhs.value);
            return this->make_self(new_value_s);
        }
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *operator%(
        AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        if (rhs.value == 0) {
            throw Div0Error();
        }

        if (this->getPrecision() < rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT)this->value) % rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value % ((ValueT)rhs.value);
            return this->make_self(new_value_s);
        }
    }

   protected:
    ValueT value;

    virtual IOperand const *make_self(ValueT value) const = 0;
};

#endif  // PROJECT_INT_HPP

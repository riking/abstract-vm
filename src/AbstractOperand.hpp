//
// Created by Kane York on 1/9/18.
//

#ifndef PROJECT_INT_HPP
#define PROJECT_INT_HPP

#include "OperandType.hpp"
#include "IOperand.hpp"
#include "Int_forward.hpp"
#include <type_traits>

template<eOperandType Type, typename ValueT>
class Int : public IOperand {
public:

    ~Int() {};

    virtual int getPrecision(void) const {
        if (Type == eOperandType::INT_8) {
            return 8;
        } else if (Type == eOperandType::INT_16) {
            return 16;
        } else if (Type == eOperandType::INT_32) {
            return 32;
        }
        return 0;
    }

    virtual eOperandType getType(void) const {
        return Type;
    }

    template<eOperandType RhsOpType, typename RHSValueT>
    virtual IOperand const *operator+(Int<RhsOpType, RHSValueT> const &rhs) const {
        if (this->getPrecision() > rhs.getPrecision()) {
            RHSValueT new_value_r = ((RHSValueT) this->value) + rhs.value;
            return rhs.make_self(new_value_r);
        } else {
            ValueT new_value_s = this->value + ((ValueT) rhs.value);
            return this->make_self(new_value_s);
        }
    }

    virtual IOperand const *operator+(IOperand const &rhs) const {
        switch (rhs.getType()) {
            case eOperandType::INT_8:
                return *this + static_cast<const Int8 &>(rhs);
            case eOperandType::INT_16:
                return *this + static_cast<const Int16 &>(rhs);
            case eOperandType::INT_32:
                return *this + static_cast<const Int32 &>(rhs);
            case eOperandType::FLOAT:break;
            case eOperandType::DOUBLE:break;
        }
    }

protected:
    ValueT value;

    virtual IOperand const *make_self(ValueT value) const = 0;
};


#endif //PROJECT_INT_HPP

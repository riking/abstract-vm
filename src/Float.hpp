//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_FLOAT_HPP
#define ABSTRACTVM_FLOAT_HPP

#include "AbstractOperand.hpp"
#include "OperandType.hpp"

class Float : public AbstractOperand<eOperandType::FLOAT, float> {
   public:
    Float();
    Float(float val);
    Float(Float const &src);
    virtual ~Float();
    Float &operator=(Float const &rhs);

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;
};

#endif  // ABSTRACTVM_FLOAT_HPP

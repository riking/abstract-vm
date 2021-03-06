//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_DOUBLE_HPP
#define ABSTRACTVM_DOUBLE_HPP

#include "AbstractOperand.hpp"
#include "OperandType.hpp"

class Double : public AbstractOperand<eOperandType::DOUBLE, double> {
   public:
    Double();
    Double(double val);
    Double(Double const &src);
    virtual ~Double();
    Double &operator=(Double const &rhs);

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;
};

#endif  // ABSTRACTVM_DOUBLE_HPP

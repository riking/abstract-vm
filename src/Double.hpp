//
// Created by Kane York on 1/9/18.
//

#ifndef PROJECT_DOUBLE_HPP
#define PROJECT_DOUBLE_HPP

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

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const;

   protected:
    virtual IOperand const *make_self(double val) const;
};

#endif  // PROJECT_DOUBLE_HPP

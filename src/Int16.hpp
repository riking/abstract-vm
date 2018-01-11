//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_INT16_HPP
#define ABSTRACTVM_INT16_HPP

#include "AbstractOperand.hpp"
#include "OperandType.hpp"

class Int16 : public AbstractOperand<eOperandType::INT_16, int16_t> {
   public:
    Int16();
    Int16(int16_t val);
    Int16(Int16 const &src);
    virtual ~Int16();
    Int16 &operator=(Int16 const &rhs);

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const;

   protected:
    virtual IOperand const *make_self(int16_t val) const;
};

#endif  // ABSTRACTVM_INT16_HPP

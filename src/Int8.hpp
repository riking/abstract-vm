//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_INT8_HPP
#define ABSTRACTVM_INT8_HPP

#include "AbstractOperand.hpp"
#include "OperandType.hpp"

class Int8 : public AbstractOperand<eOperandType::INT_8, int8_t> {
   public:
    Int8();
    Int8(int8_t val);
    Int8(Int8 const &src);
    virtual ~Int8();
    Int8 &operator=(Int8 const &rhs);

    virtual IOperand const *operator+(IOperand const &rhs) const;
    virtual IOperand const *operator-(IOperand const &rhs) const;
    virtual IOperand const *operator*(IOperand const &rhs) const;
    virtual IOperand const *operator/(IOperand const &rhs) const;
    virtual IOperand const *operator%(IOperand const &rhs) const;

    int8_t const GetInt8() const;

    template <eOperandType RhsOpType, typename RHSValueT>
    IOperand const *_mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const;

   protected:
    virtual IOperand const *make_self(int8_t val) const;
};

#endif  // ABSTRACTVM_INT8_HPP

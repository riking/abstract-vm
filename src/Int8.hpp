//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_INT8_HPP
#define ABSTRACTVM_INT8_HPP

#include "OperandType.hpp"
#include "AbstractOperand.hpp"

class Int8 : public AbstractOperand<eOperandType::INT_8, int8_t> {
public:
    Int8();
    Int8(int8_t val);
    Int8(Int8 const &src);
    virtual ~Int8();
    Int8 &operator=(Int8 const &rhs);

protected:
    virtual IOperand const *make_self(int8_t val) const;
};


#endif // ABSTRACTVM_INT8_HPP

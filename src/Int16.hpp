//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_INT16_HPP
#define ABSTRACTVM_INT16_HPP


#include "OperandType.hpp"
#include "AbstractOperand.hpp"

class Int16 : public AbstractOperand<eOperandType::INT_16, int16_t> {
public:
    Int16();
    Int16(int16_t val);
    Int16(Int16 const &src);
    virtual ~Int16();
    Int16 &operator=(Int16 const &rhs);

protected:
    virtual IOperand const *make_self(int16_t val) const;
};


#endif // ABSTRACTVM_INT16_HPP

//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_INT32_HPP
#define ABSTRACTVM_INT32_HPP


#include "OperandType.hpp"
#include "AbstractOperand.hpp"

class Int32 : public Int<eOperandType::INT_32, uint32_t> {
public:
    Int32();
    Int32(uint32_t val);
    Int32(Int32 const &src);
    virtual ~Int32();
    Int32 &operator=(Int32 const &rhs);

protected:
    virtual IOperand const *make_self(uint32_t val) const;
};


#endif // ABSTRACTVM_INT32_HPP

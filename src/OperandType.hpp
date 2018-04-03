//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_OPERANDTYPE_HPP
#define ABSTRACTVM_OPERANDTYPE_HPP

enum class eOperandType {
    INT_8,
    INT_16,
    INT_32,
    FLOAT,
    DOUBLE,
};

const char *eOperandType_Name(eOperandType type);

#endif  // ABSTRACTVM_OPERANDTYPE_HPP

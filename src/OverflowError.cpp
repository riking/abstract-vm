//
// Created by Kane York on 1/9/18.
//

#include "OverflowError.hpp"
#include "InstructionType.hpp"

#include <sstream>


OverflowError::OverflowError() : reason_("Math overflow") {}

OverflowError::~OverflowError() {}

OverflowError::OverflowError(
    IOperand const *lhs,
    IOperand const *rhs,
    eInstructionType instr_type,
    eOperandType result_type) {

    std::stringstream ss;
    ss << "Operation overflow: ";
    ss << "[" << eOperandType_Name(lhs->getType()) << " " << lhs->toString() << "]";
    ss << " " << eInstructionType_Symbol(instr_type) << " ";
    ss << "[" << eOperandType_Name(rhs->getType()) << " " << rhs->toString() << "]";
    ss << " overflows result type of " << eOperandType_Name(result_type);
    this->reason_ = ss.str();
}

OverflowError::OverflowError(OverflowError const &src) : reason_(src.reason_) {}

OverflowError &OverflowError::operator=(OverflowError const &rhs) {
    this->reason_ = rhs.reason_;
    return *this;
}

const char *OverflowError::what() const throw() { return reason_.c_str(); }

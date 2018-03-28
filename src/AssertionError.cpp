//
// Created by Kane York on 1/9/18.
//

#include "AssertionError.hpp"

#include <sstream>

AssertionError::AssertionError() : reason_("Assertion failed") {}

AssertionError::~AssertionError() {}

AssertionError::AssertionError(IOperand const *expected, IOperand const *actual) {
    std::stringstream ss;
    ss << "Assertion failed: wanted [" << eOperandType_Name(expected->getType()) << " "
       << expected->toString() << "], got [" << eOperandType_Name(actual->getType()) << " "
       << actual->toString() << "]";
    this->reason_ = ss.str();
}

AssertionError::AssertionError(AssertionError const &src) : reason_(src.reason_) {}

AssertionError &AssertionError::operator=(AssertionError const &rhs) {
    this->reason_ = rhs.reason_;
    return *this;
}

const char *AssertionError::what() const throw() { return reason_.c_str(); }

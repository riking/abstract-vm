//
// Created by Kane York on 1/9/18.
//

#include "AssertionError.hpp"

#include <sstream>

static const char *type_name(eOperandType type) {
    switch (type) {
        case eOperandType::INT_8:
            return "Int8";
        case eOperandType::INT_16:
            return "Int16";
        case eOperandType::INT_32:
            return "Int32";
        case eOperandType::FLOAT:
            return "Float";
        case eOperandType::DOUBLE:
            return "Double";
    }
}

AssertionError::AssertionError() : reason_("Assertion failed") {}

AssertionError::~AssertionError() {}

AssertionError::AssertionError(IOperand const *expected, IOperand const *actual) {
    std::stringstream ss;
    ss << "Assertion failed: wanted [" << type_name(expected->getType()) << " "
       << expected->toString() << "], got [" << type_name(actual->getType()) << " "
       << actual->toString() << "]";
    this->reason_ = ss.str();
}

AssertionError::AssertionError(AssertionError const &src) : reason_(src.reason_) {}

AssertionError &AssertionError::operator=(AssertionError const &rhs) {
    this->reason_ = rhs.reason_;
    return *this;
}

const char *AssertionError::what() const throw() { return reason_.c_str(); }

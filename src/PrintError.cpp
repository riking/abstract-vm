//
// Created by Kane York on 1/9/18.
//

#include "PrintError.hpp"

#include <sstream>

PrintError::PrintError() : reason_("Print failed") {}

PrintError::~PrintError() {}

PrintError::PrintError(eOperandType actual) {
    std::stringstream ss;
    ss << "Print failed: need Int8, got " << eOperandType_Name(actual);
    this->reason_ = ss.str();
}

PrintError::PrintError(PrintError const &src) : reason_(src.reason_) {}

PrintError &PrintError::operator=(PrintError const &rhs) {
    this->reason_ = rhs.reason_;
    return *this;
}

const char *PrintError::what() const throw() { return reason_.c_str(); }

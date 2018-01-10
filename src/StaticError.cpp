//
// Created by Kane York on 1/9/18.
//

#include "StaticError.hpp"

StaticError::StaticError() : reason_("") {}

StaticError::~StaticError() {}

StaticError::StaticError(const char *reason) : reason_(reason) {}

StaticError::StaticError(std::string reason) : reason_(reason) {}

StaticError::StaticError(StaticError const &src) : reason_(src.reason_) {}

StaticError &StaticError::operator=(StaticError const &rhs) {
    this->reason_ = rhs.reason_;
    return *this;
}

const char *StaticError::what() const throw() { return this->reason_.c_str(); }

//
// Created by Kane York on 2018/04/02.
//

#include "NumberParseError.hpp"

NumberParseError::NumberParseError() {}

NumberParseError::~NumberParseError() {}

NumberParseError::NumberParseError(const std::string value, const std::string message)
    : value(value), msg() {
    msg = message + ": " + value;
}

NumberParseError::NumberParseError(NumberParseError const &src) : value(src.value), msg(src.msg) {}

NumberParseError &NumberParseError::operator=(NumberParseError const &rhs) {
    this->value = rhs.value;
    this->msg = rhs.msg;
    return *this;
}

const char *NumberParseError::what() const throw() { return msg.c_str(); }

const std::string &NumberParseError::GetValueStr() const { return value; }

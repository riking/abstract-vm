//
// Created by Kane York on 1/9/18.
//

#include "StackEmptyError.hpp"

StackEmptyError::StackEmptyError() {}

StackEmptyError::~StackEmptyError() {}

StackEmptyError::StackEmptyError(StackEmptyError const &src) {}

StackEmptyError &StackEmptyError::operator=(StackEmptyError const &rhs) { return *this; }

const char *StackEmptyError::what() const throw() { return "Use of an empty stack"; }

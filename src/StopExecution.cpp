//
// Created by Kane York on 1/9/18.
//

#include "StopExecution.hpp"

StopExecution::StopExecution() {}

StopExecution::~StopExecution() {}

StopExecution::StopExecution(StopExecution const &src) {}

StopExecution &StopExecution::operator=(StopExecution const &rhs) {
    return *this;
}

const char *StopExecution::what() const throw() { return "Exit"; }

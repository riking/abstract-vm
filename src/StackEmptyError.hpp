//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_STACKEMPTYERROR_HPP
#define ABSTRACTVM_STACKEMPTYERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"

/**
 * An error caused via popping values from an empty stack.
 */
class StackEmptyError : public IException {
   public:
    StackEmptyError();
    StackEmptyError(StackEmptyError const &src);
    virtual ~StackEmptyError();
    StackEmptyError &operator=(StackEmptyError const &rhs);

    virtual const char *what() const throw();
};

#endif  // ABSTRACTVM_STACKEMPTYERROR_HPP

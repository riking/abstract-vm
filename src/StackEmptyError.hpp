//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_STACKEMPTYERROR_HPP
#define ABSTRACTVM_STACKEMPTYERROR_HPP

#include <exception>
#include <string>

/**
 * An error caused via popping values from an empty stack.
 */
class StackEmptyError : public std::exception {
   public:
    StackEmptyError();
    StackEmptyError(StackEmptyError const &src);
    virtual ~StackEmptyError();
    StackEmptyError &operator=(StackEmptyError const &rhs);

    const char *what() const throw();
};

#endif  // ABSTRACTVM_STACKEMPTYERROR_HPP

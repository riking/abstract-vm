//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_WRAPPEDERROR_HPP
#define ABSTRACTVM_WRAPPEDERROR_HPP

#include <exception>
#include <string>
#include "Token.hpp"

/**
 * An error annotated with line number and code.
 *
 * Generated by the Interpreter class.
 */
class WrappedError : public std::exception {
   public:
    WrappedError();
    WrappedError(std::exception wrapped);
    WrappedError(std::exception wrapped, std::string error_line, int lineno);
    WrappedError(std::exception wrapped, std::string error_line, Token phrase);
    WrappedError(WrappedError const &src);
    virtual ~WrappedError();
    WrappedError &operator=(WrappedError const &rhs);

    const char *what() const throw();

   private:
    std::string msg;
};

#endif  // ABSTRACTVM_WRAPPEDERROR_HPP
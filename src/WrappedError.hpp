//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_WRAPPEDERROR_HPP
#define ABSTRACTVM_WRAPPEDERROR_HPP

#include <exception>
#include <string>
#include <vector>
#include "IException.hpp"
#include "Line.hpp"
#include "Token.hpp"

/**
 * An error annotated with line number and code.
 *
 * Generated by the Interpreter class.
 */
class WrappedError : public IException {
   public:
    WrappedError();
    WrappedError(const std::exception& wrapped);
    WrappedError(const std::exception& wrapped, const Token& line_token,
                 const std::vector<Line>& context);
    WrappedError(const std::string& what, const Token& line_token, const Token& phrase,
                 const std::vector<Line>& context);
    WrappedError(WrappedError const& src);
    virtual ~WrappedError();
    WrappedError& operator=(WrappedError const& rhs);

    virtual const char* what() const throw();

   private:
    std::string msg;
};

#endif  // ABSTRACTVM_WRAPPEDERROR_HPP

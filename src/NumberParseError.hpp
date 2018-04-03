//
// Created by Kane York on 2018/04/02.
//

#ifndef ABSTRACTVM_NUMBERPARSEERROR_HPP
#define ABSTRACTVM_NUMBERPARSEERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"

/**
 * NumberParseError represents a failure to create an IOperand.
 */
class NumberParseError : public IException {
   public:
    NumberParseError();
    NumberParseError(const std::string value, const std::string message);
    NumberParseError(NumberParseError const &src);
    virtual ~NumberParseError();
    NumberParseError &operator=(NumberParseError const &rhs);

    virtual const char *what() const throw();

    const std::string &GetValueStr() const;

   private:
    std::string value;
    std::string msg;
};

#endif  // ABSTRACTVM_NUMBERPARSEERROR_HPP

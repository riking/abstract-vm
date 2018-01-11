//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_ASSERTIONERROR_HPP
#define ABSTRACTVM_ASSERTIONERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"
#include "IOperand.hpp"

/**
 * An error caused via an 'assert' instruction.
 */
class AssertionError : public IException {
   public:
    AssertionError();
    /**
     * Note: parameters do not need to live past construction
     */
    AssertionError(IOperand const *expected, IOperand const *actual);
    AssertionError(AssertionError const &src);
    virtual ~AssertionError();
    AssertionError &operator=(AssertionError const &rhs);

    virtual const char *what() const throw();

   private:
    std::string reason_;
};

#endif  // ABSTRACTVM_ASSERTIONERROR_HPP

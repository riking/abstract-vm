//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_OVERFLOWERROR_HPP
#define ABSTRACTVM_OVERFLOWERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"
#include "IOperand.hpp"
#include "InstructionType.hpp"
#include "OperandType.hpp"

/**
 * An error caused via arithmatic overflow.
 */
class OverflowError : public IException {
   public:
    OverflowError();
    /**
     * Note: parameters do not need to live past construction
     */
    OverflowError(IOperand const *lhs, IOperand const *rhs, eInstructionType instr_type,
                  eOperandType result_type);
    OverflowError(OverflowError const &src);
    virtual ~OverflowError();
    OverflowError &operator=(OverflowError const &rhs);

    virtual const char *what() const throw();

   private:
    std::string reason_;
};

#endif  // ABSTRACTVM_OVERFLOWERROR_HPP

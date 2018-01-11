//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_PRINTERROR_HPP
#define ABSTRACTVM_PRINTERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"
#include "OperandType.hpp"

/**
 * An error caused via a 'print' instruction.
 */
class PrintError : public IException {
   public:
    PrintError();
    PrintError(eOperandType actual);
    PrintError(PrintError const &src);
    virtual ~PrintError();
    PrintError &operator=(PrintError const &rhs);

    virtual const char *what() const throw();

   private:
    std::string reason_;
};

#endif  // ABSTRACTVM_PRINTERROR_HPP

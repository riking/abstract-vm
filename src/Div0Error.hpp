//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_DIV0ERROR_HPP
#define ABSTRACTVM_DIV0ERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"

/**
 * An error caused via dividing by zero.
 */
class Div0Error : public IException {
   public:
    Div0Error();
    Div0Error(Div0Error const &src);
    virtual ~Div0Error();
    Div0Error &operator=(Div0Error const &rhs);

    virtual const char *what() const throw();
};

#endif  // ABSTRACTVM_DIV0ERROR_HPP

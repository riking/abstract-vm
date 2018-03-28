//
// Created by Kane York on 1/10/18.
//

#ifndef ABSTRACTVM_IEXCEPTION_HPP
#define ABSTRACTVM_IEXCEPTION_HPP

#include <exception>

#define UNUSED_PARAM __attribute__((unused))

class IException : public std::exception {
   public:
    virtual ~IException(){};
    virtual const char *what() const throw() = 0;
};

#endif  // ABSTRACTVM_IEXCEPTION_HPP

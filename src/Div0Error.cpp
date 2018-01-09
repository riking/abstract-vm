//
// Created by Kane York on 1/9/18.
//

#include "Div0Error.hpp"

Div0Error::Div0Error() {}

Div0Error::~Div0Error() {}

Div0Error::Div0Error(Div0Error const &src) {}

Div0Error &Div0Error::operator=(Div0Error const &rhs) {
    return *this;
}

const char *Div0Error::what() const throw() {
    return "Divide by 0";
}

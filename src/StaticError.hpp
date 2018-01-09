//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_STATICERROR_HPP
#define ABSTRACTVM_STATICERROR_HPP

#include <exception>
#include <string>

/**
 * An error caused independent of the input.
 */
class StaticError : public std::exception {
public:
    StaticError();
    StaticError(const char * reason);
    StaticError(std::string reason);
    StaticError(StaticError const &src);
    virtual ~StaticError();
    StaticError &operator=(StaticError const &rhs);

    const char * what() const throw();

private:
    std::string reason_;
};


#endif //PROJECT_STATICERROR_HPP

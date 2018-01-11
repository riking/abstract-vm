//
// Created by Kane York on 1/10/18.
//

#ifndef ABSTRACTVM_PARSEERROR_HPP
#define ABSTRACTVM_PARSEERROR_HPP

#include <exception>
#include <string>
#include "IException.hpp"
#include "Token.hpp"

/**
 * ParseError is a vehicle for passing the correct Token into WrappedError.
 */
class ParseError : public IException {
   public:
    ParseError();
    ParseError(Token err_token, std::string message);
    ParseError(const Token *err_token, std::string message);
    ParseError(ParseError const &src);
    virtual ~ParseError();
    ParseError &operator=(ParseError const &rhs);

    virtual const char *what() const throw();

    const Token &GetToken() const;
    const std::string &GetMessage() const;

   private:
    Token err_token;
    std::string message;
};

#endif  // ABSTRACTVM_PARSEERROR_HPP

//
// Created by Kane York on 1/10/18.
//

#include "ParseError.hpp"

ParseError::ParseError() {}

ParseError::~ParseError() {}

ParseError::ParseError(Token err_token, std::string message)
    : err_token(err_token), message(message) {}

ParseError::ParseError(const Token *err_token, std::string message)
    : err_token(*err_token), message(message) {}

ParseError::ParseError(ParseError const &src) : err_token(src.err_token), message(src.message) {}

ParseError &ParseError::operator=(ParseError const &rhs) {
    this->err_token = rhs.err_token;
    this->message = rhs.message;
    return *this;
}

const char *ParseError::what() const throw() { return "Parsing error"; }

const Token &ParseError::GetToken() const { return err_token; }
const std::string &ParseError::GetMessage() const { return message; }

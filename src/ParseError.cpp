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

ParseError::ParseError(ParseError const &src) {}

ParseError &ParseError::operator=(ParseError const &rhs) { return *this; }

const char *ParseError::what() const throw() { return "Parsing error"; }

const Token &ParseError::GetToken() const { return err_token; }
const std::string &ParseError::GetMessage() const { return message; }

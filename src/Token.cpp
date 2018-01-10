//
// Created by Kane York on 1/9/18.
//

#include "Token.hpp"

Token::Token() : source(""), column(-1) {}

Token::~Token() {}

Token::Token(unsigned long lineno, std::string source, signed long column)
    : lineno(lineno), source(source), column(column) {}

Token::Token(const Token &src) { *this = src; }

Token &Token::operator=(Token const &rhs) {
    this->lineno = rhs.lineno;
    this->source = rhs.source;
    this->column = rhs.column;
    return *this;
}

unsigned long Token::GetLine() const { return lineno; }

signed long Token::GetColumn() const { return column; }

unsigned long Token::GetLength() const { return source.size(); }

const std::string &Token::GetSource() const { return source; }

Token *Token::SubToken(unsigned long offset, unsigned long len) const {
    return new Token(lineno, source.substr(offset, len), column + offset);
}

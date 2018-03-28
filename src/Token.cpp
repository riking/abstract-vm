//
// Created by Kane York on 1/9/18.
//

#include "Token.hpp"
#include "StaticError.hpp"

Token::Token() : source(""), lineno(-1), column(-1) {}

Token::~Token() {}

Token::Token(size_t lineno, std::string source) : source(source), lineno(lineno), column(0) {}

Token::Token(size_t lineno, std::string source, ssize_t column)
    : source(source), lineno(lineno), column(column) {}

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

std::unique_ptr<Token> Token::SubToken(ssize_t offset, ssize_t len) const {
    if (offset < 0 || len < 0) {
        throw StaticError("Negative values as input to SubToken");
    }
    return std::make_unique<Token>(lineno, source.substr(offset, len), column + offset);
}

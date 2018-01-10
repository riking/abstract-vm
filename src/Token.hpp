//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_TOKEN_HPP
#define ABSTRACTVM_TOKEN_HPP


#include <string>

/**
 * A lexeme in the source code.
 */
class Token {
public:
    Token();
    Token(unsigned long lineno, std::string source, signed long column);
    Token(Token const &src);
    virtual ~Token();
    Token &operator=(Token const &rhs);

    unsigned long GetLine() const;
    signed long GetColumn() const;
    unsigned long GetLength() const;
    const std::string& GetSource() const;

    Token *SubToken(unsigned long offset, unsigned long len) const;

private:
    std::string source;
    unsigned long lineno;
    signed long column;
};


#endif // ABSTRACTVM_TOKEN_HPP

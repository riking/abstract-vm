//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_TOKEN_HPP
#define ABSTRACTVM_TOKEN_HPP

#include <memory>
#include <string>

/**
 * A lexeme in the source code.
 */
class Token {
   public:
    Token();
    Token(size_t lineno, std::string source);
    Token(size_t lineno, std::string source, ssize_t column);
    Token(Token const &src);
    virtual ~Token();
    Token &operator=(Token const &rhs);

    unsigned long GetLine() const;
    signed long GetColumn() const;
    unsigned long GetLength() const;
    const std::string &GetSource() const;

    /**
     * Allocates a new Token object.
     * @param offset
     * @param len
     * @return new Token object that must be deleted
     */
    std::unique_ptr<Token> SubToken(ssize_t offset, ssize_t len) const;

   private:
    std::string source;
    size_t lineno;
    ssize_t column;
};

#endif  // ABSTRACTVM_TOKEN_HPP

//
// Created by Kane York on 1/10/18.
//

#ifndef PROJECT_PARSER_HPP
#define PROJECT_PARSER_HPP

#include <istream>
#include <memory>
#include <vector>
#include "Line.hpp"
#include "ParseError.hpp"
#include "WrappedError.hpp"

class Parser {
   public:
    Parser();
    Parser(Parser const &src);
    virtual ~Parser();
    Parser &operator=(Parser const &rhs);

    std::unique_ptr<std::vector<Line>> ParseProgram(std::istream &input,
                                                    bool is_stdin) throw(WrappedError);

   private:
    /**
     * if is_stdin, treat a double semicolon as end of input
     */
    bool is_stdin;
    std::istream *input;

    Line ParseLine(const Token &line_token) throw(ParseError);
    eInstructionType RecognizeInstruction(const Token *token) throw(ParseError);
    const IOperand *ParseOperand(const Token *trimmed_line, size_t instr_len) throw(ParseError);
    eOperandType RecognizeOperand(const Token *type) throw(ParseError);
    const IOperand *MakeOperand(eOperandType type, const Token *value) throw(ParseError);

    std::unique_ptr<const Token> TrimSpace(const Token *tok);
    std::unique_ptr<const Token> TrimCommentsAndSpaces(const Token *tok);
    std::unique_ptr<const Token> GetFirstWord(const Token *tok);
};
#endif  // PROJECT_PARSER_HPP

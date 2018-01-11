//
// Created by Kane York on 1/10/18.
//

#ifndef PROJECT_LINE_HPP
#define PROJECT_LINE_HPP

#include "IOperand.hpp"
#include "InstructionType.hpp"
#include "Token.hpp"

class Line {
   public:
    Line();
    /**
     * A line with no instruction.
     * @param full Full line token
     */
    Line(const Token full);

    /**
     * No-operand instructions, like mul, print, exit
     * @param source Line source token
     * @param type Instruction type
     */
    Line(Token full, Token instr, eInstructionType type);

    /**
     * Instructions with an operand, like push, assert
     * @param source Line source token
     * @param type Instruction type
     * @param op Operand
     */
    Line(Token source, Token instr, eInstructionType type, const IOperand *op);
    Line(Line const &src);
    virtual ~Line();
    Line &operator=(Line const &rhs);

    const Token& GetSource() const;

   private:
    eInstructionType type;
    const IOperand *op;
    Token source;
    Token instr;
};

#endif  // PROJECT_LINE_HPP

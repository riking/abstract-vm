//
// Created by Kane York on 1/10/18.
//

#include "Line.hpp"

#include "InstructionType.hpp"
#include "OperandFactory.hpp"

Line::Line() : type(eInstructionType::COMMENT), op(NULL), source(Token()), instr(Token()) {}

Line::Line(const Token full) : Line(full, Token(), eInstructionType::COMMENT, NULL) {}

Line::Line(Token full, Token instr, eInstructionType type) : Line(full, instr, type, NULL) {}

Line::Line(Token full, Token instr, eInstructionType type, const IOperand *op)
    : type(type), op(op), source(full), instr(instr) {}

Line::~Line() {
    if (this->op) {
        delete this->op;
        this->op = NULL;
    }
}

Line::Line(Line const &src) : type(src.type), op(NULL), source(src.source), instr(src.instr) {
    if (src.op) {
        OperandFactory factory{};
        this->op = factory.createOperand(src.op->getType(), src.op->toString());
    } else {
        this->op = NULL;
    }
}

Line &Line::operator=(const Line &rhs) {
    this->source = rhs.source;
    this->instr = rhs.instr;
    this->type = rhs.type;
    if (this->op) {
        delete this->op;
        this->op = NULL;
    }
    if (rhs.op) {
        OperandFactory factory{};
        this->op = factory.createOperand(rhs.op->getType(), rhs.op->toString());
    }
    return *this;
}

const Token &Line::GetSource() const { return this->source; }
const Token &Line::GetInstrToken() const { return this->instr; }
const IOperand *Line::GetOperand() const { return this->op; }
eInstructionType Line::GetType() const { return this->type; }

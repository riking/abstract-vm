//
// Created by Kane York on 1/10/18.
//

#include "Line.hpp"
#include "Int8.hpp"

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

Line::Line(Line const &src) : source(src.source), instr(src.instr), type(src.type) {
    if (src.op) {
        Int8 identity = Int8(0);
        this->op = (*src.op) + identity;
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
    Int8 identity = Int8(0);
    this->op = (*rhs.op) + identity;
    return *this;
}

const Token &Line::GetSource() const { return this->source; }
const Token &Line::GetInstrToken() const { return this->instr; }
const IOperand *Line::GetOperand() const { return this->op; }
eInstructionType Line::GetType() const { return this->type; }

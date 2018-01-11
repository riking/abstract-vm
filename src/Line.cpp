//
// Created by Kane York on 1/10/18.
//

#include "Line.hpp"
#include "Int8.hpp"

Line::Line()
    : source(Token()), instr(Token()), type(eInstructionType::COMMENT), op(NULL) {}

Line::Line(const Token full)
    : Line(full, Token(), eInstructionType::COMMENT, NULL) {}

Line::Line(Token full, Token instr, eInstructionType type)
    : Line(full, instr, type, NULL) {}

Line::Line(Token full, Token instr, eInstructionType type, const IOperand *op)
    : source(full), instr(instr), type(type), op(op) {}

Line::~Line() {
    if (this->op) {
        delete this->op;
        this->op = NULL;
    }
}

Line::Line(Line const &src) : source(src.source), type(src.type) {
    Int8 identity = Int8(0);
    this->op = (*src.op) + identity;
}

Line &Line::operator=(const Line &rhs) {
    this->source = rhs.source;
    this->type = rhs.type;
    if (this->op) {
        delete this->op;
        this->op = NULL;
    }
    Int8 identity = Int8(0);
    this->op = (*rhs.op) + identity;
    return *this;
}

const Token &Line::GetSource() const {
    return this->source;
}

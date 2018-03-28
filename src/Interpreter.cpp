//
// Created by Kane York on 1/10/18.
//

#include "Interpreter.hpp"
#include <iostream>
#include "StaticError.hpp"

Interpreter::Interpreter() : executing_line(0), stack(Stack()) {}
Interpreter::Interpreter(const Interpreter &src)
    : executing_line(src.executing_line), stack(src.stack) {}
Interpreter::~Interpreter() {}

Interpreter &Interpreter::operator=(const Interpreter &rhs) {
    this->executing_line = rhs.executing_line;
    this->stack = rhs.stack;
    return *this;
}

void Interpreter::Run(std::unique_ptr<std::vector<Line>> program) throw(StopExecution,
                                                                        WrappedError) {
    for (const Line &line : *program) {
        executing_line++;
        try {
            RunLine(line);
        } catch (StopExecution) {
            throw StopExecution();
        } catch (const IException &e) {
            throw WrappedError(e.what(), line.GetSource(), line.GetInstrToken(), *program);
        } catch (const std::exception &e) {
            throw WrappedError(e.what(), line.GetSource(), line.GetInstrToken(), *program);
        }
    }
    throw WrappedError(StaticError("Reached end of file without 'exit' instruction"));
}

void Interpreter::RunLine(const Line &line) throw(StopExecution, IException) {
    switch (line.GetType()) {
        case eInstructionType::COMMENT:
            // Comment
            break;
        case eInstructionType::PUSH:
            stack.Push(line.GetOperand());
            break;
        case eInstructionType::POP:
            stack.Pop();
            break;
        case eInstructionType::DUMP:
            stack.Dump(std::cout);
            break;
        case eInstructionType::ASSERT:
            stack.Assert(line.GetOperand());
            break;
        case eInstructionType::ADD:
            stack.Add();
            break;
        case eInstructionType::SUB:
            stack.Sub();
            break;
        case eInstructionType::MUL:
            stack.Mul();
            break;
        case eInstructionType::DIV:
            stack.Div();
            break;
        case eInstructionType::MOD:
            stack.Mod();
            break;
        case eInstructionType::PRINT:
            stack.Print(std::cout);
            break;
        case eInstructionType::EXIT:
            stack.Exit();
            break;
        case eInstructionType::END_OF_FILE:
            break;
    }
}

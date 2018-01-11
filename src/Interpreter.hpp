//
// Created by Kane York on 1/10/18.
//

#ifndef ABSTRACTVM_INTERPRETER_HPP
#define ABSTRACTVM_INTERPRETER_HPP

#include <vector>
#include "Line.hpp"
#include "Stack.hpp"
#include "WrappedError.hpp"

class Interpreter {
   public:
    Interpreter();
    Interpreter(std::vector<Line> code);
    Interpreter(Interpreter const &src);
    virtual ~Interpreter();
    Interpreter &operator=(Interpreter const &rhs);

    void RunProgram() throw(WrappedError);

   private:
    std::vector<Line> lines;
    int executing_line;
    Stack stack;

    void exec_line(const Line &line) throw(WrappedError);
};

#endif  // ABSTRACTVM_INTERPRETER_HPP

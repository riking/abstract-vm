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
    Interpreter(Interpreter const &src);
    virtual ~Interpreter();
    Interpreter &operator=(Interpreter const &rhs);

    // @throws StopExection, WrappedError
    void Run(std::unique_ptr<std::vector<Line>> program);

   private:
    int executing_line;
    Stack stack;

    // @throws StopExection, IException
    void RunLine(const Line &line);
};

#endif  // ABSTRACTVM_INTERPRETER_HPP

//
// Created by Kane York on 1/9/18.
//

#ifndef PROJECT_STACK_HPP
#define PROJECT_STACK_HPP

#include <vector>

#include "AssertionError.hpp"
#include "Div0Error.hpp"
#include "IOperand.hpp"
#include "PrintError.hpp"
#include "StackEmptyError.hpp"
#include "StopExecution.hpp"

class Stack {
   public:
    Stack();
    Stack(Stack const &src);
    virtual ~Stack();
    Stack &operator=(Stack const &rhs);

    void Push(const IOperand *value) throw(IException);
    void Pop() throw(IException);
    void Dump(std::ostream &out) const throw(IException);
    void Assert(const IOperand *value) throw(IException);
    void Add() throw(IException);
    void Sub() throw(IException);
    void Mul() throw(IException);
    void Div() throw(IException);
    void Mod() throw(IException);
    void Print(std::ostream &out) throw(IException);
    void Exit() throw(StopExecution);

   private:
    void empty_();

    std::vector<const IOperand *> stack_;
};

#endif  // PROJECT_STACK_HPP

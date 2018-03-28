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

    void Push(const IOperand *value);
    void Pop() throw(StackEmptyError);
    void Dump(std::ostream &out) const;
    void Assert(const IOperand *value) throw(AssertionError);
    void Add();
    void Sub();
    void Mul();
    void Div();
    void Mod();
    void Print(std::ostream &out) throw(PrintError);
    void Exit() throw(StopExecution);

   private:
    void empty_();

    std::vector<const IOperand *> stack_;
};

#endif  // PROJECT_STACK_HPP

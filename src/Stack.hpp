//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_STACK_HPP
#define ABSTRACTVM_STACK_HPP

#include "AssertionError.hpp"
#include "Div0Error.hpp"
#include "IOperand.hpp"
#include "PrintError.hpp"
#include "StackEmptyError.hpp"
#include "StopExecution.hpp"

#include <vector>

class Stack {
   public:
    Stack();
    Stack(Stack const &src);
    virtual ~Stack();
    Stack &operator=(Stack const &rhs);

    // All operations can throw IException
    void Push(const IOperand *value);
    void Pop();
    void Dump(std::ostream &out) const;
    // @throws AssertionError
    void Assert(const IOperand *value);
    void Add();
    void Sub();
    void Mul();
    void Div();
    void Mod();
    void Print(std::ostream &out);
    // @throws StopExecution
    void Exit();

   private:
    void empty_();

    std::vector<const IOperand *> stack_;
};

#endif  // ABSTRACTVM_STACK_HPP

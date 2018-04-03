//
// Created by Kane York on 1/9/18.
//

#include "Stack.hpp"
#include "Int8.hpp"

#include <memory>

namespace {
Int8 g_identity = Int8(0);
}

Stack::Stack() : stack_() {}

Stack::Stack(Stack const &src) : stack_() { (*this) = src; }

Stack::~Stack() { this->empty_(); }

void Stack::empty_() {
    while (this->stack_.size()) {
        std::unique_ptr<const IOperand> op(stack_.back());
        stack_.pop_back();
    }
}

Stack &Stack::operator=(Stack const &rhs) {
    this->empty_();

    for (const IOperand *op : rhs.stack_) {
        const IOperand *clone = op->operator+(g_identity);
        stack_.push_back(clone);
    }

    return *this;
}

void Stack::Push(const IOperand *value) throw(IException) {
    // Need to create an owned copy so destructor functions correctly
    const IOperand *owned_copy = g_identity + *value;
    stack_.push_back(owned_copy);
}

void Stack::Pop() throw(IException) {
    if (stack_.size() == 0) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> op(stack_.back());
    stack_.pop_back();
    // drop 'op'
}

void Stack::Dump(std::ostream &out) const throw(IException) {
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
        const IOperand *op = *it;
        out << op->toString() << std::endl;
    }
}

void Stack::Assert(const IOperand *expected) throw(IException) {
    if (stack_.size() == 0) {
        throw StackEmptyError();
    }
    const IOperand *actual = stack_.back();  // do not delete
    if (actual->getType() != expected->getType()) {
        throw AssertionError(expected, actual);
    }

    if (!(*expected == *actual)) {
        throw AssertionError(expected, actual);
    }
    // OK
    return;
}

void Stack::Add() throw(IException) {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> rhs(stack_.back());
    stack_.pop_back();
    std::unique_ptr<const IOperand> lhs(stack_.back());
    stack_.pop_back();
    const IOperand *push = (*lhs) + (*rhs);
    stack_.push_back(push);
}

void Stack::Sub() throw(IException) {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> rhs(stack_.back());
    stack_.pop_back();
    std::unique_ptr<const IOperand> lhs(stack_.back());
    stack_.pop_back();
    const IOperand *push = (*lhs) - (*rhs);
    stack_.push_back(push);
}

void Stack::Mul() throw(IException) {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> rhs(stack_.back());
    stack_.pop_back();
    std::unique_ptr<const IOperand> lhs(stack_.back());
    stack_.pop_back();
    const IOperand *push = (*lhs) * (*rhs);
    stack_.push_back(push);
}

void Stack::Div() throw(IException) {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> rhs(stack_.back());
    stack_.pop_back();
    std::unique_ptr<const IOperand> lhs(stack_.back());
    stack_.pop_back();
    const IOperand *push = (*lhs) / (*rhs);
    stack_.push_back(push);
}

void Stack::Mod() throw(IException) {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    std::unique_ptr<const IOperand> rhs(stack_.back());
    stack_.pop_back();
    std::unique_ptr<const IOperand> lhs(stack_.back());
    stack_.pop_back();
    const IOperand *push = (*lhs) % (*rhs);
    stack_.push_back(push);
}

void Stack::Print(std::ostream &out) throw(IException) {
    if (stack_.size() == 0) {
        throw StackEmptyError();
    }

    const IOperand *op = stack_.back();
    if (op->getType() != eOperandType::INT_8) {
        throw PrintError(op->getType());
    }
    const Int8 &i = *(static_cast<const Int8 *>(op));
    const int8_t val = i.GetInt8();

    out << char(val);
}

void Stack::Exit() throw(StopExecution) { throw StopExecution(); }

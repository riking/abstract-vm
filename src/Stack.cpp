//
// Created by Kane York on 1/9/18.
//

#include "Stack.hpp"
#include "Int8.hpp"

namespace {
Int8 g_identity = Int8(0);
}

//bool operator==(IOperand const &self, IOperand const &rhs);

Stack::Stack() : stack_() {}

Stack::Stack(Stack const &src) : stack_() { (*this) = src; }

Stack::~Stack() { this->empty_(); }

void Stack::empty_() {
    while (this->stack_.size()) {
        const IOperand *op = stack_.back();
        stack_.pop_back();
        delete op;
    }
}

Stack &Stack::operator=(Stack const &rhs) {
    this->empty_();

    // additive identity at lowest available precision
    const Int8 min_prec_zero = Int8(0);

    for (const IOperand *op : rhs.stack_) {
        const IOperand *clone = op->operator+(min_prec_zero);
        stack_.push_back(clone);
    }

    return *this;
}

void Stack::Push(const IOperand *value) {
    // Need to create an owned copy so destructor functions correctly
    const IOperand *owned_copy = g_identity + *value;
    stack_.push_back(owned_copy);
}

void Stack::Pop() throw(StackEmptyError) {
    if (stack_.size() == 0) {
        throw StackEmptyError();
    }
    const IOperand *op = stack_.back();
    stack_.pop_back();
    delete op;
}

void Stack::Dump(std::ostream &out) const {
    for (auto it = stack_.rbegin(); it != stack_.rend(); ++it) {
        const IOperand *op = *it;
        out << op->toString() << std::endl;
    }
}

void Stack::Assert(const IOperand *expected) throw(AssertionError) {
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

void Stack::Add() {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    const IOperand *rhs = stack_.back();
    stack_.pop_back();
    const IOperand *lhs = stack_.back();
    stack_.pop_back();
    const IOperand *push = (*lhs) + (*rhs);
    delete rhs;
    delete lhs;
    stack_.push_back(push);
}

void Stack::Sub() {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    const IOperand *rhs = stack_.back();
    stack_.pop_back();
    const IOperand *lhs = stack_.back();
    stack_.pop_back();
    const IOperand *push = (*lhs) - (*rhs);
    delete rhs;
    delete lhs;
    stack_.push_back(push);
}

void Stack::Mul() {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    const IOperand *rhs = stack_.back();
    stack_.pop_back();
    const IOperand *lhs = stack_.back();
    stack_.pop_back();
    const IOperand *push = (*lhs) * (*rhs);
    delete rhs;
    delete lhs;
    stack_.push_back(push);
}

void Stack::Div() {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    const IOperand *rhs = stack_.back();
    stack_.pop_back();
    const IOperand *lhs = stack_.back();
    stack_.pop_back();
    const IOperand *push = (*lhs) / (*rhs);
    delete rhs;
    delete lhs;
    stack_.push_back(push);
}

void Stack::Mod() {
    if (stack_.size() < 2) {
        throw StackEmptyError();
    }
    const IOperand *rhs = stack_.back();
    stack_.pop_back();
    const IOperand *lhs = stack_.back();
    stack_.pop_back();
    const IOperand *push = (*lhs) % (*rhs);
    delete rhs;
    delete lhs;
    stack_.push_back(push);
}

void Stack::Print(std::ostream &out) throw(PrintError) {
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

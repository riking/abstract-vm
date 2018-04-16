//
// Created by Kane York on 1/9/18.
//

#ifndef ABSTRACTVM_ABSTRACTOPERAND_HPP
#define ABSTRACTVM_ABSTRACTOPERAND_HPP

#include "Div0Error.hpp"
#include "IOperand.hpp"
#include "InstructionType.hpp"
#include "OperandFactory.hpp"
#include "OperandType.hpp"
#include "OverflowError.hpp"
#include "StaticError.hpp"
#include "StringConverter.hpp"

#include <cmath>
#include <memory>
#include <sstream>
#include <type_traits>

class Int8;
class Int16;
class Int32;
class Float;
class Double;

template <eOperandType Type, typename ValueT>
class AbstractOperand : public IOperand {
   public:
    AbstractOperand() : value(0), as_string(){};
    AbstractOperand(ValueT value) : value(value), as_string(){};

    AbstractOperand(AbstractOperand &src) : value(src.value), as_string(src.as_string){};
    virtual ~AbstractOperand(){};
    AbstractOperand &operator=(AbstractOperand const &rhs) {
        this->value = rhs.value;
        this->as_string = rhs.as_string;
    }

    virtual int getPrecision(void) const {
        if (Type == eOperandType::INT_8) {
            return 8;
        } else if (Type == eOperandType::INT_16) {
            return 16;
        } else if (Type == eOperandType::INT_32) {
            return 32;
        } else if (Type == eOperandType::FLOAT) {
            return 36;
        } else if (Type == eOperandType::DOUBLE) {
            return 72;
        }
        return 0;
    }

    virtual eOperandType getType(void) const { return Type; }

    virtual std::string const &toString(void) const {
        if (as_string.get()) {
            return *as_string;
        }
        StringConverter conv{};
        std::string tmp_string = conv.MakeString(value);
        as_string = std::make_unique<std::string>(tmp_string);
        return *as_string;
    }

    virtual bool operator==(IOperand const &rhs) const {
        if (this->getType() != rhs.getType()) {
            return false;
        }
        auto const &casted_rhs = static_cast<AbstractOperand<Type, ValueT> const &>(rhs);

        if (Type == eOperandType::FLOAT || Type == eOperandType::DOUBLE) {
            if (std::isnan(this->value) && std::isnan(casted_rhs.get())) {
                return true;
            }
        }

        return !(this->value != casted_rhs.get());
    }

    ValueT get() const { return value; }

   protected:
    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type < eOperandType::FLOAT) && (RhsOpType < eOperandType::FLOAT),
                            IOperand const *>::type
    _add(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        bool check;
        check = __builtin_add_overflow(lhsv, rhsv, &result);
        if (check) {
            throw OverflowError(this, &rhs, eInstructionType::ADD, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type >= eOperandType::FLOAT) || (RhsOpType >= eOperandType::FLOAT),
                            IOperand const *>::type
    _add(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        result = lhsv + rhsv;
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::ADD, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type < eOperandType::FLOAT) && (RhsOpType < eOperandType::FLOAT),
                            IOperand const *>::type
    _sub(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        bool check;
        check = __builtin_sub_overflow(lhsv, rhsv, &result);
        if (check) {
            throw OverflowError(this, &rhs, eInstructionType::SUB, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type >= eOperandType::FLOAT) || (RhsOpType >= eOperandType::FLOAT),
                            IOperand const *>::type
    _sub(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        result = lhsv - rhsv;
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::SUB, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type < eOperandType::FLOAT) && (RhsOpType < eOperandType::FLOAT),
                            IOperand const *>::type
    _mul(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        bool check;
        check = __builtin_mul_overflow(lhsv, rhsv, &result);
        if (check) {
            throw OverflowError(this, &rhs, eInstructionType::MUL, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type >= eOperandType::FLOAT) || (RhsOpType >= eOperandType::FLOAT),
                            IOperand const *>::type
    _mul(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        result = lhsv * rhsv;
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::MUL, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type < eOperandType::FLOAT) && (RhsOpType < eOperandType::FLOAT),
                            IOperand const *>::type
    _div(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        if (rhsv == 0) {
            throw Div0Error();
        }
        result = lhsv / rhsv;
        if (false) {
            // Integer division cannot overflow
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type >= eOperandType::FLOAT) || (RhsOpType >= eOperandType::FLOAT),
                            IOperand const *>::type
    _div(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        if (rhsv == 0) {
            throw Div0Error();
        }
        result = lhsv / rhsv;
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::DIV, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    // Modulo

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type < eOperandType::FLOAT) && (RhsOpType < eOperandType::FLOAT),
                            IOperand const *>::type
    _mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        if (rhsv == 0) {
            throw Div0Error();
        }
        result = lhsv % rhsv;
        if (false) {
            // Integer modulo cannot overflow
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    }

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<((Type == eOperandType::FLOAT) || (RhsOpType == eOperandType::FLOAT)) &&
                                !((Type == eOperandType::DOUBLE) ||
                                  (RhsOpType == eOperandType::DOUBLE)),
                            IOperand const *>::type
    _mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        if (rhsv == 0) {
            throw Div0Error();
        }
        if (std::isinf(lhsv)) {
            throw OverflowError(this, &rhs, eInstructionType::MOD, ResultOpType);
        }
        result = fmodf(lhsv, rhsv);
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::MOD, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    template <eOperandType RhsOpType, typename RHSValueT>
    typename std::enable_if<(Type == eOperandType::DOUBLE) || (RhsOpType == eOperandType::DOUBLE),
                            IOperand const *>::type
    _mod(AbstractOperand<RhsOpType, RHSValueT> const &rhs) const {
        constexpr eOperandType ResultOpType = (RhsOpType > Type) ? RhsOpType : Type;
        typedef typename std::conditional<(RhsOpType > Type), RHSValueT, ValueT>::type ResultValueT;
        ResultValueT lhsv = (ResultValueT) this->value;
        ResultValueT rhsv = (ResultValueT)rhs.get();
        ResultValueT result = 0;
        if (rhsv == 0) {
            throw Div0Error();
        }
        if (std::isinf(lhsv)) {
            throw OverflowError(this, &rhs, eInstructionType::MOD, ResultOpType);
        }
        result = fmod(lhsv, rhsv);
        if (std::isinf(result)) {
            throw OverflowError(this, &rhs, eInstructionType::MOD, ResultOpType);
        }
        OperandFactory factory{};
        StringConverter conv{};
        return factory.createOperand(ResultOpType, conv.MakeString(result));
    };

    ValueT value;
    // This is mutable to fix lifetime problems when lazy creating the string representation
    mutable std::unique_ptr<std::string> as_string;
};

#endif  // ABSTRACTVM_ABSTRACTOPERAND_HPP

//
// Created by Kane York on 2018/04/02.
//

#ifndef ABSTRACTVM_OPERANDFACTORY_HPP
#define ABSTRACTVM_OPERANDFACTORY_HPP

#include "IOperand.hpp"

#include <array>
#include <string>
#include "IException.hpp"

class OperandFactory final {
   public:
    IOperand const* createOperand(eOperandType type, std::string const& value) const;

   private:
    IOperand const* createInt8(std::string const& value) const;
    IOperand const* createInt16(std::string const& value) const;
    IOperand const* createInt32(std::string const& value) const;
    IOperand const* createFloat(std::string const& value) const;
    IOperand const* createDouble(std::string const& value) const;

    using FactoryFunction = IOperand const* (OperandFactory::*)(std::string const&)const;
    static const std::array<FactoryFunction, 5> factory_methods_by_type;
};

#endif  // ABSTRACTVM_OPERANDFACTORY_HPP

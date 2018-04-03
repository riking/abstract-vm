//
// Created by Kane York on 2018/04/02.
//

#include "OperandFactory.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <limits>
#include <string>

#include "Double.hpp"
#include "Float.hpp"
#include "IOperand.hpp"
#include "Int16.hpp"
#include "Int32.hpp"
#include "Int8.hpp"
#include "NumberParseError.hpp"

const std::array<OperandFactory::FactoryFunction, 5> OperandFactory::factory_methods_by_type = {
    &OperandFactory::createInt8,  &OperandFactory::createInt16,  &OperandFactory::createInt32,
    &OperandFactory::createFloat, &OperandFactory::createDouble,
};

IOperand const *OperandFactory::createOperand(eOperandType type, std::string const &value) const
    throw(IException) {
    return (this->*(factory_methods_by_type[static_cast<int>(type)]))(value);
}

IOperand const *OperandFactory::createInt8(std::string const &value) const throw(IException) {
    size_t val_end_idx;
    long long val_ll;
    try {
        val_ll = std::stoll(value, &val_end_idx);
    } catch (std::invalid_argument) {
        throw NumberParseError(value, "Failed to parse int8");
    } catch (std::out_of_range) {
        throw NumberParseError(value, "Value out of range for int8");
    }
    if (val_end_idx != value.size()) {
        throw NumberParseError(value, "Extra content after numeric value");
    }
    if (val_ll < std::numeric_limits<int8_t>::min() ||
        val_ll > std::numeric_limits<int8_t>::max()) {
        throw NumberParseError(value, "Value out of range for int8");
    }
    return new Int8((int8_t)val_ll);
}
IOperand const *OperandFactory::createInt16(std::string const &value) const throw(IException) {
    size_t val_end_idx;
    long long val_ll;
    try {
        val_ll = std::stoll(value, &val_end_idx);
    } catch (std::invalid_argument) {
        throw NumberParseError(value, "Failed to parse int16");
    } catch (std::out_of_range) {
        throw NumberParseError(value, "Value out of range for int16");
    }
    if (val_end_idx != value.size()) {
        throw NumberParseError(value, "Extra content after numeric value");
    }
    if (val_ll < std::numeric_limits<int16_t>::min() ||
        val_ll > std::numeric_limits<int16_t>::max()) {
        throw NumberParseError(value, "Value out of range for int16");
    }
    return new Int16((int16_t)val_ll);
}

IOperand const *OperandFactory::createInt32(std::string const &value) const throw(IException) {
    size_t val_end_idx;
    long long val_ll;
    try {
        val_ll = std::stoll(value, &val_end_idx);
    } catch (std::invalid_argument) {
        throw NumberParseError(value, "Failed to parse int32");
    } catch (std::out_of_range) {
        throw NumberParseError(value, "Value out of range for int32");
    }
    if (val_end_idx != value.size()) {
        throw NumberParseError(value, "Extra content after numeric value");
    }
    if (val_ll < std::numeric_limits<int32_t>::min() ||
        val_ll > std::numeric_limits<int32_t>::max()) {
        throw NumberParseError(value, "Value out of range for int32");
    }
    return new Int32((int32_t)val_ll);
}

IOperand const *OperandFactory::createFloat(std::string const &value) const throw(IException) {
    size_t val_end_idx;
    float val_f;
    try {
        val_f = std::stof(value, &val_end_idx);
    } catch (std::invalid_argument) {
        throw NumberParseError(value, "Failed to parse float");
    } catch (std::out_of_range) {
        throw NumberParseError(value, "Value out of range for float");
    }
    if (val_end_idx != value.size()) {
        throw NumberParseError(value, "Extra content after numeric value");
    }
    return new Float(val_f);
}

IOperand const *OperandFactory::createDouble(std::string const &value) const throw(IException) {
    size_t val_end_idx;
    double val_d;
    try {
        val_d = std::stod(value, &val_end_idx);
    } catch (std::invalid_argument) {
        throw NumberParseError(value, "Failed to parse double-precision float");
    } catch (std::out_of_range) {
        throw NumberParseError(value, "Value out of range for double-precision float");
    }
    if (val_end_idx != value.size()) {
        throw NumberParseError(value, "Extra content after numeric value");
    }
    return new Double(val_d);
}

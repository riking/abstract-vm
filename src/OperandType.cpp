//
// Created by Kane York on 1/12/18.
//

#include "OperandType.hpp"

const char *eOperandType_Name(eOperandType type) {
    switch (type) {
        case eOperandType::INT_8:
            return "Int8";
        case eOperandType::INT_16:
            return "Int16";
        case eOperandType::INT_32:
            return "Int32";
        case eOperandType::FLOAT:
            return "Float";
        case eOperandType::DOUBLE:
            return "Double";
    }
    return "<ERROR: Invalid operand type>";
}

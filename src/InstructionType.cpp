//
// Created by Kane York on 1/12/18.
//

#include "InstructionType.hpp"

const char *eInstructionType_Symbol(eInstructionType type) {
    switch (type) {
        case eInstructionType::COMMENT: return "COMMENT";
        case eInstructionType::PUSH: return "PUSH";
        case eInstructionType::POP: return "POP";
        case eInstructionType::DUMP: return "DUMP";
        case eInstructionType::ASSERT: return "ASSERT";
        case eInstructionType::NEG_ASSERT: return "NEGASSERT";
        case eInstructionType::ADD: return "+";
        case eInstructionType::SUB: return "-";
        case eInstructionType::MUL: return "*";
        case eInstructionType::DIV: return "/";
        case eInstructionType::MOD: return "%";
        case eInstructionType::PRINT: return "PRINT";
        case eInstructionType::EXIT: return "EXIT";
        case eInstructionType::END_OF_FILE: return ";;";
    }
}

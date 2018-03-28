//
// Created by Kane York on 1/10/18.
//

#ifndef PROJECT_INSTRUCTIONTYPE_HPP
#define PROJECT_INSTRUCTIONTYPE_HPP

enum class eInstructionType {
    COMMENT,
    EXPECT_COMMENT,
    PUSH,
    POP,
    DUMP,
    ASSERT,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    PRINT,
    EXIT,
    END_OF_FILE,
};

const char *eInstructionType_Symbol(eInstructionType type);

#endif  // PROJECT_INSTRUCTIONTYPE_HPP

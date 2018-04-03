//
// Created by Kane York on 1/9/18.
//

#include "Interpreter.hpp"
#include "Parser.hpp"
#include "StopExecution.hpp"
#include "WrappedError.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
    char* file;
    if (argc == 1) {
        file = NULL;
    } else if (argc == 2) {
        file = argv[1];
    } else {
        std::cerr << "Usage: abstract-vm [file]";
        return 2;
    }

    std::string expect_error = "";
    std::string actual_error = "";
    int result = -1;

    try {
        std::unique_ptr<std::vector<Line>> program;

        {
            Parser p;
            if (file == NULL) {
                program = p.ParseProgram(std::cin, true);
            } else {
                std::ifstream input(file);
                program = p.ParseProgram(input, false);
            }
        }

        // Check for ;EXPECT
        auto it = std::find_if(program->begin(), program->end(), [](const Line& l) -> bool {
            return l.GetType() == eInstructionType::EXPECT_COMMENT;
        });
        if (it != program->end()) {
            const Line& l = *it;
            const Token& instr_tok = l.GetInstrToken();
            // ";EXPECT ".length
            constexpr int instr_len = sizeof(";EXPECT ") - 1;
            if (instr_tok.GetLength() > instr_len) {
                std::unique_ptr<Token> expect_tok =
                    instr_tok.SubToken(instr_len, instr_tok.GetLength() - instr_len);
                expect_error = expect_tok->GetSource();
            }
        }

        Interpreter i;
        i.Run(std::move(program));

    } catch (StopExecution) {
        result = 0;
    } catch (WrappedError e) {
        actual_error = e.GetInnerMessage();
        std::cerr << e.what() << std::endl;
        result = 1;
    }

    if (expect_error != "") {
        size_t idx = actual_error.find(expect_error);
        if (idx == std::string::npos) {
            std::cerr << "EXPECT FAILURE" << std::endl;
            std::cerr << "Expected error: " << expect_error << std::endl;
            std::cerr << "Actual error: ";
            if (actual_error == "") {
                std::cerr << "(success)";
            } else {
                std::cerr << actual_error;
            }
            std::cerr << std::endl;
            abort();
        }
    }

    return result;
}

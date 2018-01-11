//
// Created by Kane York on 1/9/18.
//

#include <fstream>
#include <iostream>

#include "Interpreter.hpp"
#include "Parser.hpp"
#include "StopExecution.hpp"
#include "WrappedError.hpp"

int main(int argc, char **argv) {
    char *file;
    if (argc == 1) {
        file = NULL;
    } else if (argc == 2) {
        file = argv[1];
    } else {
        std::cerr << "Usage: abstract-vm [file]";
        return 2;
    }

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

        Interpreter i;
        i.Run(std::move(program));

    } catch (StopExecution) {
        return 0;
    } catch (WrappedError e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

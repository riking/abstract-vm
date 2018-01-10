//
// Created by Kane York on 1/9/18.
//

#include <iostream>

#include "StopExecution.hpp"
#include "WrappedError.hpp"

int main(int argc, char **argv) {
    try {

    } catch (StopExecution) {
        return 0;
    } catch (WrappedError e) {
        std::cerr << e.what() << std::endl;
    }
}

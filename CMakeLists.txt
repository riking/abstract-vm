cmake_minimum_required(VERSION 3.6)

include_directories(src)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(abstract-vm
        src/main.cpp
        src/Stack.cpp
        src/Stack.hpp
        src/Token.cpp
        src/Token.hpp
        src/Interpreter.cpp
        src/Interpreter.hpp
        src/InstructionType.hpp
        src/Line.cpp
        src/Line.hpp
        src/Parser.cpp
        src/Parser.hpp

        src/IOperand.hpp
        src/OperandType.hpp
        src/AbstractOperand.cpp
        src/AbstractOperand.hpp

        src/Int8.cpp
        src/Int8.hpp
        src/Int16.cpp
        src/Int16.hpp
        src/Int32.cpp
        src/Int32.hpp
        src/Float.cpp
        src/Float.hpp
        src/Double.cpp
        src/Double.hpp

        src/AssertionError.cpp
        src/AssertionError.hpp
        src/Div0Error.cpp
        src/Div0Error.hpp
        src/PrintError.cpp
        src/PrintError.hpp
        src/StackEmptyError.cpp
        src/StackEmptyError.hpp
        src/StaticError.cpp
        src/StaticError.hpp
        src/StopExecution.cpp
        src/StopExecution.hpp
        src/WrappedError.cpp
        src/WrappedError.hpp
        src/ParseError.cpp src/ParseError.hpp)

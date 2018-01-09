cmake_minimum_required(VERSION 3.6)

include_directories(src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(abstract-vm
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
        src/StaticError.cpp
        src/StaticError.hpp
        src/main.cpp
        src/Float.cpp
        src/Float.hpp
        src/Double.cpp
        src/Double.hpp)

cmake_minimum_required(VERSION 3.8)
project(avm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp headers/main.h defined_literals.cpp Parser.cpp headers/Parser.h headers/IOperand.h Operand.hpp OperandController.cpp headers/OperandController.h RunTypeError.cpp headers/RunTypeError.h NotFitError.cpp headers/NotFitError.h)
add_executable(avm ${SOURCE_FILES})
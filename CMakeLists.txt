cmake_minimum_required(VERSION 3.8)
project(avm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp main.h defined_literals.cpp Parser.cpp Parser.h IOperand.h Operand.h OperandController.cpp OperandController.h check_func.cpp NotFit.cpp NotFit.h)
add_executable(avm ${SOURCE_FILES})
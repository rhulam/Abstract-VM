#ifndef AVM_MAIN_H
#define AVM_MAIN_H

#include <iostream>

enum eOperandType: unsigned {INT8, INT16, INT32, FLOAT, DOUBLE};
extern const std::string red;
extern const std::string reset;
extern const std::string b_red;
extern const std::string blue;
extern const std::string cyan;

#include "Parser.h"
#include "Operand.h"

int8_t operator "" _int8(unsigned long long int v);
int16_t operator "" _int16(unsigned long long int v);
int32_t operator "" _int32(unsigned long long int v);

#endif //AVM_MAIN_H

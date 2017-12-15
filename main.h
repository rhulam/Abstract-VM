#ifndef AVM_MAIN_H
#define AVM_MAIN_H

#include <iostream>

extern const std::string red;
extern const std::string reset;
extern const std::string b_red;
extern int a;

#include "Parser.h"

int8_t operator "" _int8(unsigned long long int v);
int16_t operator "" _int16(unsigned long long int v);
int32_t operator "" _int32(unsigned long long int v);

#endif //AVM_MAIN_H

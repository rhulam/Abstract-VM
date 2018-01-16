#ifndef AVM_MAIN_H
#define AVM_MAIN_H

#include <iostream>

extern const std::string Red;
extern const std::string Reset;
extern const std::string B_red;
extern const std::string Blue;
extern const std::string Cyan;

int8_t operator "" _int8(unsigned long long int v);
int16_t operator "" _int16(unsigned long long int v);
int32_t operator "" _int32(unsigned long long int v);

#endif //AVM_MAIN_H

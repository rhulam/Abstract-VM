#include "main.h"

int8_t operator "" _int8(unsigned long long int v) { return static_cast<std::int8_t>(v); }
int16_t operator "" _int16(unsigned long long int v) { return static_cast<std::int16_t>(v); }
int32_t operator "" _int32(unsigned long long int v) { return static_cast<std::int32_t>(v); }
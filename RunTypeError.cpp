#include "headers/RunTypeError.h"

RunTypeError::RunTypeError(const std::string &msgs)
{
    this->msgs = "Run type Error: " + msgs;
}

const char* RunTypeError::what() const noexcept
{
    return msgs.c_str();
}

RunTypeError::RunTypeError(const RunTypeError &src): msgs(src.msgs) {}
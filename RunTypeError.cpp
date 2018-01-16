#include "RunTypeError.h"

RunTypeError::RunTypeError(const std::string &msgs): msgs(msgs) {}

const char* RunTypeError::what() const noexcept
{
    return msgs.c_str();
}

RunTypeError::RunTypeError(const RunTypeError &src): msgs(src.msgs) {}
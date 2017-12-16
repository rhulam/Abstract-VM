#include "NotFit.h"

NotFit::NotFit(const std::string &msg): msg(msg) {};

const char* NotFit::what() const noexcept
{
    return msg.c_str();
}
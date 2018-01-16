#include "NotFitError.h"

NotFit::NotFit(const std::string &msg): msg(msg) {};

const char *NotFit::what() const noexcept
{
    return msg.c_str();
}

NotFit::NotFit(const NotFit &src)
{
    msg = src.msg;
}
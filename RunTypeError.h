#ifndef AVM_RUNTYPEERROR_H
#define AVM_RUNTYPEERROR_H

#include <string>
#include <exception>

class RunTypeError: public std::exception
{
    std::string msgs;
    RunTypeError() = default;
    RunTypeError &operator=(const RunTypeError &src) = default;

public:
    explicit RunTypeError(const std::string &msg);
    const char *what() const noexcept override;
    ~RunTypeError() = default;
    RunTypeError(const RunTypeError &src);
};


#endif //AVM_RUNTYPEERROR_H

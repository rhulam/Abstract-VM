#ifndef AVM_NOTFITERROR_H
#define AVM_NOTFITERROR_H

#include <exception>
#include <string>

class NotFit: public std::exception {

    std::string msg;
    NotFit &operator=(const NotFit &src) = default;
    NotFit() = default;

public:

    explicit NotFit(const std::string &msg);
    const char *what() const noexcept final;
    ~NotFit() = default;
    NotFit(const NotFit &src);
};


#endif //AVM_NOTFITERROR_H

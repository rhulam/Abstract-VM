#ifndef AVM_NOTFIT_H
#define AVM_NOTFIT_H

#include <iostream>

class NotFit: public std::exception {

    std::string msg;

public:

    explicit NotFit(const std::string &msg);
    const char *what() const noexcept;
};


#endif //AVM_NOTFIT_H

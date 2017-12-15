#ifndef AVM_PARSES_H
#define AVM_PARSES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include "main.h"

class Parser {

public:
    bool fail = false;
    explicit Parser(int argc, char **argv);
    Parser(const Parser &src) = default;
    Parser &operator=(const Parser &src) = default;
    ~Parser() = default;

    void lexis();
    std::vector<std::string> instructions;

    class LexicalException: public std::exception
    {
        int i;
        std::string msg;

    public:
        explicit LexicalException(int i, const std::string &msg);
        const char *what() const noexcept override;
    };

    class ParseException: public std::exception
    {
        int i;
        std::string msg;

    public:
        explicit ParseException(int i, const std::string &msg);
        const char *what() const noexcept override;
    };

private:
    //std::vector<std::string> instructions;
    bool file = false;

    Parser() = default;

    void read(std::istream &i);
};


#endif //AVM_PARSES_H

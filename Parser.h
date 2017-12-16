#ifndef AVM_PARSES_H
#define AVM_PARSES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <sstream>

class Parser {

public:
    bool fail = false;
    unsigned errors_counter = 0;
    explicit Parser(int argc, char **argv);
    Parser(const Parser &src) = default;
    Parser &operator=(const Parser &src) = default;
    ~Parser() = default;

    void lexis();
    void logic();

    class LexicalException: public std::exception
    {
        std::string msgs;

    public:
        explicit LexicalException(const std::string &msg);
        const char *what() const noexcept override;
    };

    class ParseException: public std::exception
    {
        std::string msgs;

    public:
        explicit ParseException(const std::string &msg);
        const char *what() const noexcept override;
    };

private:
    std::vector<std::pair<std::string, unsigned int>> instructions;
    std::string errors;
    bool file = false;

    Parser() = default;

    void read(std::istream &i);
    bool check_command(const std::string &command, unsigned i);
    bool check_type(const std::string &command, unsigned i);
};


#endif //AVM_PARSES_H

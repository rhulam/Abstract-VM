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
    ~Parser() = default;

    void lexis();
    void logic();

    class LexicalException: public std::exception
    {
        std::string msgs;
        LexicalException() = default;
        LexicalException &operator=(const LexicalException &src) = default;

    public:
        explicit LexicalException(const std::string &msg);
        const char *what() const noexcept override;
        ~LexicalException() = default;
        LexicalException(const LexicalException &src);
    };

    class ParseException: public std::exception
    {
        std::string msgs;
        ParseException() = default;
        ParseException &operator=(const ParseException &src) = default;

    public:
        explicit ParseException(const std::string &msg);
        const char *what() const noexcept override;
        ParseException(const ParseException &src);
    };

private:
    std::vector<std::pair<std::string, unsigned int>> instructions;
    std::string errors;
    bool file = false;

    Parser() = default;
    Parser(const Parser &src) = default;
    Parser &operator=(const Parser &src) = default;

    void read(std::istream &i);
    void check_command(const std::string &command, unsigned i);
    void check_type(const std::string &command, unsigned i);
    void add_error(const std::string &error);
};


#endif //AVM_PARSES_H

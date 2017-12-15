#include "Parser.h"

Parser::Parser(int argc, char **argv)
{
    if (argc == 1)
        read(std::cin);
    else
    {
        file = true;
        std::ifstream f(argv[1]);
        if (!f.is_open())
        {
            std::cerr << red << "Can't open the file" << reset << std::endl;
            exit(-1);
        }
        read(f);
    }
}

void Parser::lexis()
{
    throw LexicalException(123, "bitch");
}

Parser::LexicalException::LexicalException(int i, const std::string &msg): i(i), msg(msg) {}

const char* Parser::LexicalException::what() const noexcept
{
    std::string message;
    message = red + "Lexical Exception " + reset + "at line " + std::to_string(i) + ": " + msg;
    return message.c_str();
}

Parser::ParseException::ParseException(int i, const std::string &msg): i(i), msg(msg){}

const char* Parser::ParseException::what() const noexcept
{
    std::string message;
    message = red + "Parse Exception " + reset + "at line " + std::to_string(i) + ": " + msg;
    return message.c_str();
}

void Parser::read(std::istream &i)
{
    std::string line;
    size_t pos;
    while (getline(i, line))
    {
        if (line == ";;" && !file)
            break;
        line = line.substr(0, line.find(";"));
        if (line.find_first_not_of(" ") == std::string::npos)
            continue;
        instructions.emplace_back(line);
    }
}
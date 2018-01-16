#include "headers/Parser.h"
#include "headers/main.h"
#include "Operand.hpp"

//void tester();

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
            std::cerr << Red << "Can't open the file" << Reset << std::endl;
            exit(-1);
        }
        read(f);
    }
}

void Parser::check_type(const std::string &command, unsigned i)
{
    std::regex expr("^(int(8|16|32)\\([-+]{0,1}[0-9]+\\))|((double|float)\\([-+]{0,1}[0-9]{0,}(\\.){0,1}[0-9]+\\))$");
    std::string value = command.substr(command.find('(') + 1, command.find(')') - command.find('(') - 1);
    std::string type = command.substr(0, command.find('('));
    std::string pattern = B_red + "Parse Exception " + Reset + "at line " + Cyan + std::to_string(i) + Reset + ": ";

    if (!std::regex_match(command, expr))
        add_error(pattern + "unknown type parameter '" + command + "'\n");
    else
    {
        try
        {
            if (type == "int8")
                Operand<int8_t>::check_val((stold(value)));
            else if (type == "int16")
                Operand<int16_t>::check_val((stold(value)));
            else if (type == "int32")
                Operand<int32_t>::check_val((stold(value)));
            else if (type == "float")
                Operand<float>::check_val((stold(value)));
            else if (type == "double")
                Operand<double>::check_val((stold(value)));
        }
        catch (const NotFit &e)
        {
            add_error(pattern + e.what() + " '" + command + "'\n");
        }
    }
}

void Parser::check_command(const std::string &command, unsigned i)
{
    std::string commands[] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};

    for (const auto &word: commands)
        if (word == command)
            return;
    add_error(B_red + "Parse Exception " + Reset + "at line " + Cyan + std::to_string(i) + Reset + ": " +
                      "unknown assembly command '" + command + "'\n");
}

void Parser::logic()
{
    errors_counter = 0;
    errors.clear();
    fail = false;

    for(const auto &line: instructions)
    {
        std::istringstream ss(line.first);
        std::vector<std::string> words;
        std::string word;
        std::string pattern = B_red + "Parse Exception " + Reset + "at line " + Cyan + std::to_string(line.second) + Reset + ": ";

        while (getline(ss, word, ' '))
            words.emplace_back(word);

        check_command(words[0], line.second);

        if ((words[0] == "push" || words[0] == "assert") && words.size() > 1)
            check_type(words[1], line.second);
        else if (words[0] == "push" || words[0] == "assert")
            add_error(pattern + "expected parameter for '" + words[0] + "'\n");
        else if (words.size() > 1)
            add_error(pattern + "unknown parameter '" + words[1] + "'\n");
    }

    if (fail)
        throw ParseException(errors);
}

void Parser::lexis()
{
    for(const auto &line: instructions)
    {
        std::string word;
        std::regex word_expr("^[a-z]+$");
        auto pos = line.first.find(' ');

        word = line.first.substr(0, pos);
        std::string pattern = Red + "Lexical Exception " + Reset + "at line " + Cyan + std::to_string(line.second) + Reset + ": ";

        if (!std::regex_match(word, word_expr))
        {
            add_error(pattern += "unexpected symbols in assembly command '" + word + "'\n");
        }
        if (pos != std::string::npos)
        {
            std::string type = line.first.substr(pos + 1, line.first.find_first_of(" \t", pos + 1) - pos - 1);
            std::regex type_expr_main("^[a-z]+(.*)");
            std::regex type_expr_parentheses("(.*)\\((.*)\\)(.*)");
            std::regex type_expr_value("(.*)\\(([0-9\\-+\\.]+)\\)(.*)");
            std::regex type_expr_full("^(.*)\\([-+]{0,1}[0-9(\\.){0,1}]+\\)$");

            if (!std::regex_match(type, type_expr_main))
                add_error(pattern + "unexpected symbols in variable type '" + type + "'\n");
            else if (!std::regex_match(type, type_expr_parentheses))
                add_error(pattern + "must be opened and closed parentheses '" + type + "'\n");
            else if (!std::regex_match(type, type_expr_value))
                add_error(pattern + "expected a number inside parentheses '" + type + "'\n");
            else if (!std::regex_match(type, type_expr_full))
                add_error(pattern + "invalid syntax '" + type + "'\n");
            if (line.first.find_first_of(" \t", pos + 1) != std::string::npos)
                add_error(pattern + "unexpected symbols after '" + type + "'\n");
        }

    }
    if (fail)
        throw LexicalException(errors);
}

Parser::LexicalException::LexicalException(const std::string &msgs): msgs(msgs) {}

const char* Parser::LexicalException::what() const noexcept
{
    return msgs.c_str();
}

Parser::LexicalException::LexicalException(const LexicalException &src): msgs(src.msgs) {}

Parser::ParseException::ParseException(const std::string &msg): msgs(msg) {}

const char* Parser::ParseException::what() const noexcept
{
    return msgs.c_str();
}

Parser::ParseException::ParseException(const ParseException &src): msgs(src.msgs) {};

void Parser::read(std::istream &i)
{
    std::string line;
    size_t pos = 0;
    unsigned int counter = 0;

    while (getline(i, line))
    {
        counter++;
        if (line == ";;" && !file)
            break;
        line = line.substr(0, line.find(';'));
        if (line.find_first_not_of(" \t") == std::string::npos)
            continue;
        line = line.substr(line.find_first_not_of(" \t"), line.find_last_not_of(" \t") + 1 - line.find_first_not_of(" \t"));
        if ((pos = line.find_first_of(" \t", 0)) != std::string::npos)
        {
            size_t next_pos = line.find_first_not_of(" \t", pos);
            line = line.substr(0, pos) + " " + line.substr(next_pos);
        }
        instructions.emplace_back(std::make_pair(line, counter));
    }
}

void Parser::add_error(const std::string &error)
{
    fail = true;
    errors_counter++;
    errors += error;
}

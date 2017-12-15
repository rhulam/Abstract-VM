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

bool Parser::check_type(const std::string &command, unsigned i)
{
    std::regex expr("^((int(8|16|32))|double|float)\\([-+]{0,1}[0-9]+\\)$");
    if (!std::regex_match(command, expr))
    {
        errors_counter++;
        errors += b_red + "Parse Exception " + reset + "at line " + cyan + std::to_string(i) + reset + ": " + "unexpected parameter '" + command + "'\n";
        return true;
    }
    return false;
}

bool Parser::check_command(const std::string &command, unsigned i)
{
    std::string commands[] = {"push", "pop", "dump", "assert", "add", "sub", "mul", "div", "mod", "print", "exit"};

    for (const auto &word: commands)
    {
        if (word == command)
            return false;
    }
    errors_counter++;
    errors += b_red + "Parse Exception " + reset + "at line " + cyan + std::to_string(i) + reset + ": " + "unexpected assembly command '" + command + "'\n";
    return true;
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

        while (getline(ss, word, ' '))
            words.emplace_back(word);

        fail = check_command(words[0], line.second);
        if (words[0] == "push" || words[0] == "assert")
            fail = check_type(words[1], line.second);
        else if (words.size() > 1)
        {
            errors_counter++;
            errors += b_red + "Parse Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset + ": " + "unexpected parameter '" + words[1] + "'\n";
        }
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
        if (!std::regex_match(word, word_expr))
        {
            fail = true;
            errors += red + "Lexical Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset +
                      ": " + "unexpected symbols in assembly command '" + word + "'\n";
            errors_counter++;
        }
        if (pos != std::string::npos)
        {
            std::string type = line.first.substr(pos + 1, line.first.find_first_of(" \t", pos + 1) - pos - 1);
            std::regex type_expr_main("^[a-z]+(.*)");
            std::regex type_expr_parentheses("(.*)\\((.*)\\)(.*)");
            std::regex type_expr_value("(.*)\\(([0-9\\-+]+)\\)(.*)");

            if (!std::regex_match(type, type_expr_main))
            {
                fail = true;
                errors += red + "Lexical Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset +
                          ": " + "unexpected symbols in variable type '" + type + "'\n";
                errors_counter++;
            }
            else if (!std::regex_match(type, type_expr_parentheses))
            {
                fail = true;
                errors += red + "Lexical Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset +
                          ": " + "must be opened and closed parentheses '" + type + "'\n";
                errors_counter++;
            }
            else if (!std::regex_match(type, type_expr_value))
            {
                fail = true;
                errors += red + "Lexical Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset +
                          ": " + "expected a number inside parentheses '" + type + "'\n";
                errors_counter++;
            }
            if (line.first.find_first_of(" \t", pos + 1) != std::string::npos)
            {
                fail = true;
                errors += red + "Lexical Exception " + reset + "at line " + cyan + std::to_string(line.second) + reset +
                          ": " + "unexpected symbols after '" + type + "'\n";
                errors_counter++;
            }
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

Parser::ParseException::ParseException(const std::string &msg): msgs(msg){}

const char* Parser::ParseException::what() const noexcept
{
    return msgs.c_str();
}

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
        line = line.substr(0, ';');
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
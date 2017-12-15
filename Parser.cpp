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

void Parser::logic()
{
    errors_counter = 0;
    errors.clear();

    for(const auto &line: instructions)
    {
        std::istringstream ss(line.first);
        std::vector<std::string> words;
        std::string word;

        while (getline(ss, word, ' '))
            words.emplace_back(word);

        
    }

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
            std::regex type_expr_main("^[a-z]+[0-9]{0}(.*)");
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

Parser::ParseException::ParseException(int i, const std::string &msg): i(i), msg(msg){}

const char* Parser::ParseException::what() const noexcept
{
    std::string message;
    message = red + "Parse Exception " + reset + "at line " + cyan + std::to_string(i) + reset + ": " + msg;
    return message.c_str();
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
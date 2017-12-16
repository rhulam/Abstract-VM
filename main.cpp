#include "main.h"
#include "Parser.h"

const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string blue = "\033[34m";
const std::string yellow = "\033[33m";
const std::string cyan = "\033[36m";
const std::string reset = "\033[0m";
const std::string b_red = "\033[91m";

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        std::cerr << red << "Too many arguments!" << reset << std::endl;
        exit(-1);
    }
    std::cout << green << "Starting..." << reset << std::endl;
    Parser parse(argc, argv);
    std::cout << green << "All commands read" << reset << std::endl;

    try
    {
        parse.lexis();
    }
    catch (const Parser::LexicalException &e)
    {
        std::cerr << red << "Lexer failed with " << parse.errors_counter << " errors!" << reset << "\n" << e.what();
    }
    if (!parse.fail)
        std::cout << green << "Lexer OK" << reset << std::endl;
    try
    {
        parse.logic();
    }
    catch (const Parser::ParseException &e)
    {
        std::cerr << b_red << "Parser failed with " << parse.errors_counter << " errors!" << reset << "\n" << e.what();
    }
    if (!parse.fail)
        std::cout << green << "Parser OK" << reset << std::endl;
    if (parse.fail)
       exit(-1);

    return 0;
}
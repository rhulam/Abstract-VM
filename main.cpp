#include "headers/main.h"
#include "headers/Parser.h"

const std::string Red = "\033[31m";
const std::string Green = "\033[32m";
const std::string Blue = "\033[34m";
const std::string Yellow = "\033[33m";
const std::string Cyan = "\033[36m";
const std::string Reset = "\033[0m";
const std::string B_red = "\033[91m";

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        std::cerr << Red << "Too many arguments!" << Reset << std::endl;
        exit(-1);
    }

    std::cout << Green << "Starting..." << Reset << std::endl;
    Parser parse(argc, argv);
    std::cout << Green << "All commands read" << Reset << std::endl;

    try
    {
        parse.lexis();
    }
    catch (const Parser::LexicalException &e)
    {
        std::cerr << Red << "Lexer failed with " << parse.errors_counter << " errors!" << Reset << "\n" << e.what();
    }

    if (!parse.fail)
        std::cout << Green << "Lexer OK" << Reset << std::endl;

    try
    {
        parse.logic();
    }
    catch (const Parser::ParseException &e)
    {
        std::cerr << B_red << "Parser failed with " << parse.errors_counter << " errors!" << Reset << "\n" << e.what();
    }

    if (!parse.fail)
        std::cout << Green << "Parser OK" << Reset << std::endl;
    else
        exit(-1);

    return 0;
}
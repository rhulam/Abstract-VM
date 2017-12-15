#include "main.h"

const std::string red = "\033[31m";
const std::string green = "\033[32m";
const std::string blue = "\033[34m";
const std::string yellow = "\033[33m";
const std::string cyan = "\033[36m";
const std::string reset = "\033[0m";
const std::string b_red = "\033[91m";
int a = 2;

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        std::cerr << red << "Too many arguments!" << reset << std::endl;
        exit(-1);
    }
    Parser parse(argc, argv);
    std::copy(parse.instructions.begin(), parse.instructions.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

    try
    {
        parse.lexis();
        //    parse.logic();
    }
    catch (const Parser::LexicalException &e)
    {
        std::cerr << e.what() << std::endl;
    }
    catch (const Parser::ParseException &e)
    {
        std::cerr << e.what() << std::endl;
    }

    if (parse.fail)
       exit(-1);

    return 0;
}
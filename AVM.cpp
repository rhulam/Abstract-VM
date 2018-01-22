#include "headers/AVM.h"

void AVM::start()
{
    for (const auto &i: instructions)
    {
        if (i.find("push") != std::string::npos)
            pushValue(i);
        else if (i == "pop")
            popStack();
        else if (i == "dump")
            dump();
        else if (i.find("assert") != std::string::npos)
            assert(i);
        else if (i == "add")
            operation('+');
        else if (i == "sub")
            operation('-');
        else if (i == "mul")
            operation('*');
        else if (i == "div")
            operation('/');
        else if (i == "mod")
            operation('%');
        else if (i == "print")
            print();
        else if (i == "exit")
            toExit();
        if (exit)
            break;
    }
    if (!exit)
        throw RunTypeError("missing exit command");
}

void AVM::pushValue(const std::string &command)
{
    stack.emplace_back(getValuePointer(command));
}

std::string AVM::getValue(const std::string &command) const
{
    auto start = command.find('(');
    auto end = command.find(')');
    return command.substr(start + 1, end - start - 1);
}

eOperandType AVM::getType(const std::string &command) const
{
    if (command.find("int8") != std::string::npos)
        return INT8;
    else if (command.find("int16") != std::string::npos)
        return INT16;
    else if (command.find("int32") != std::string::npos)
        return INT32;
    else if (command.find("float") != std::string::npos)
        return FLOAT;
    else
        return DOUBLE;
}

void AVM::popStack()
{
    if (stack.empty())
        throw RunTypeError("pop empty stack");
    stack.pop_back();
}

void AVM::dump() const
{
    for (auto i = stack.rbegin(); i != stack.rend(); i++)
        std::cout << (*i)->toString() << std::endl;
}

void AVM::assert(const std::string &command) const
{
    if (stack.empty())
        throw RunTypeError("assert empty stack");
    std::unique_ptr<const IOperand> temp(getValuePointer(command));
    if (temp->toString() != stack.back()->toString() || temp->getType() != stack.back()->getType())
        throw RunTypeError("assert error");
}

IOperand const *AVM::getValuePointer(const std::string &command) const
{
    auto value = getValue(command);
    auto type = getType(command);

    return controller.createOperand(type, value);
}

void AVM::operation(char o)
{
    if (stack.size() < 2)
        throw RunTypeError("operation on stack with size less than 2");
    auto temp1 = std::move(stack.back());
    stack.pop_back();
    auto temp2 = std::move(stack.back());
    stack.pop_back();
    IOperand const* result;
    switch(o)
    {
        case '+': result = *temp2 + *temp1; break;
        case '-': result = *temp2 - *temp1; break;
        case '*': result = *temp2 * *temp1; break;
        case '/': result = *temp2 / *temp1; break;
        case '%': result = *temp2 % *temp1; break;
    }
    stack.emplace_back(result);
}

void AVM::print() const
{
    if (stack.empty())
        throw RunTypeError("assert empty stack");
    auto &value = stack.back();
    if (value->getType() != INT8)
        throw RunTypeError("can't print not int8 type");
    std::cout << static_cast<char>(stoi(value->toString())) << std::endl;
}

void AVM::toExit()
{
    exit = true;
}
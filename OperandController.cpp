#include "OperandController.h"

OperandController& OperandController::Instance()
{
    static OperandController s;
    return s;
}

IOperand const* OperandController::createOperand(eOperandType type, std::string const &value) const
{
    return (*this.*pointers[type])(value);
}

OperandController::OperandController()
{
    pointers[0] = &OperandController::createInt8;
    pointers[1] = &OperandController::createInt16;
    pointers[2] = &OperandController::createInt32;
    pointers[3] = &OperandController::createFloat;
    pointers[4] = &OperandController::createDouble;;
}

IOperand const* OperandController::createInt8(std::string const &value) const
{

}

IOperand const* OperandController::createInt16(std::string const &value) const
{

}

IOperand const* OperandController::createInt32(std::string const &value) const
{

}

IOperand const* OperandController::createFloat(std::string const &value) const
{

}

IOperand const* OperandController::createDouble(std::string const &value) const
{

}
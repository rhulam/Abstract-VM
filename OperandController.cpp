#include "OperandController.h"
#include "Operand.hpp"

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
    int8_t n = strtold(value.c_str(), nullptr);
    Operand<int8_t>::check_val(n);
    const IOperand *r = new Operand<int8_t>(n);
    return r;
}

IOperand const* OperandController::createInt16(std::string const &value) const
{
    int16_t n = strtold(value.c_str(), nullptr);
    Operand<int16_t>::check_val(n);
    const IOperand *r = new Operand<int16_t>(n);
    return r;
}

IOperand const* OperandController::createInt32(std::string const &value) const
{
    int32_t n = strtold(value.c_str(), nullptr);
    Operand<int32_t>::check_val(n);
    const IOperand *r = new Operand<int32_t>(n);
    return r;
}

IOperand const* OperandController::createFloat(std::string const &value) const
{
    float n = strtold(value.c_str(), nullptr);
    Operand<float>::check_val(n);
    const IOperand *r = new Operand<float>(n);
    return r;
}

IOperand const* OperandController::createDouble(std::string const &value) const
{
    double n = strtold(value.c_str(), nullptr);
    Operand<double>::check_val(n);
    const IOperand *r = new Operand<double>(n);
    return r;
}
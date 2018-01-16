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
    long double n = strtold(value.c_str(), nullptr);
    Operand<int8_t>::check_val(n);
    const IOperand *r = new Operand<int8_t>(static_cast<int8_t >(n), INT8);
    return r;
}

IOperand const* OperandController::createInt16(std::string const &value) const
{
    long double n = strtold(value.c_str(), nullptr);
    Operand<int16_t>::check_val(n);
    const IOperand *r = new Operand<int16_t>(static_cast<int16_t >(n), INT16);
    return r;
}

IOperand const* OperandController::createInt32(std::string const &value) const
{
    long double n = strtold(value.c_str(), nullptr);
    Operand<int32_t>::check_val(n);
    const IOperand *r = new Operand<int32_t>(static_cast<int32_t>(n), INT32);
    return r;
}

IOperand const* OperandController::createFloat(std::string const &value) const
{
    long double n = strtold(value.c_str(), nullptr);
    Operand<float>::check_val(n);
    const IOperand *r = new Operand<float>(static_cast<float>(n), FLOAT);
    return r;
}

IOperand const* OperandController::createDouble(std::string const &value) const
{
    long double n = strtold(value.c_str(), nullptr);
    Operand<double>::check_val(n);
    const IOperand *r = new Operand<double>(static_cast<double>(n), DOUBLE);
    return r;
}
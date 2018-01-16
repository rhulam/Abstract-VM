#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include "headers/IOperand.h"
#include "headers/OperandController.h"
#include "headers/RunTypeError.h"
#include "headers/NotFitError.h"

template <typename T>
class Operand: public IOperand {

public:

    explicit Operand(T n, eOperandType type);
    ~Operand() = default;
    int getPrecision() const final;
    eOperandType getType() const final;

    IOperand const * operator+(IOperand const & rhs) const final;
    IOperand const * operator-(IOperand const & rhs) const final;
    IOperand const * operator*(IOperand const & rhs) const final;
    IOperand const * operator/(IOperand const & rhs) const final;
    IOperand const * operator%(IOperand const & rhs) const final;

    std::string const & toString() const final;

    static void check_val(long double l);

private:

    T value;
    int precision;
    std::string string_value;
    eOperandType type;
    Operand &operator=(const Operand &src) = default;
    Operand() = default;
    Operand(const Operand &src) = default;

};

template <typename T>
int Operand<T>::getPrecision() const {return precision;}

template <typename T>
eOperandType Operand<T>::getType() const {return type;}

template <typename T>
std::string const& Operand<T>::toString() const {return string_value;}

template <typename T>
void Operand<T>::check_val(long double l)
{
    if (std::numeric_limits<T>::max() < l)
        throw NotFit("overflow");
    else if (std::numeric_limits<T>::lowest() > l)
        throw NotFit("underflow");
}

template <typename T>
Operand<T>::Operand(T n, eOperandType type): value(n), precision(type), type(type)
{
    string_value = std::to_string(value);
}

template <typename T>
IOperand const* Operand<T>::operator+(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    return OperandController::Instance().createOperand(p, std::to_string(value + stold(rhs.toString(), nullptr)));

}

template <typename T>
IOperand const* Operand<T>::operator-(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    return OperandController::Instance().createOperand(p, std::to_string(value - stold(rhs.toString(), nullptr)));
}

template <typename T>
IOperand const* Operand<T>::operator*(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    return OperandController::Instance().createOperand(p, std::to_string(value * stold(rhs.toString(), nullptr)));
}

template <typename T>
IOperand const* Operand<T>::operator/(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    if (!strtold(rhs.toString().c_str(), nullptr))
        throw RunTypeError("division by zero");
    return OperandController::Instance().createOperand(p, std::to_string(value / stold(rhs.toString(), nullptr)));
}

template <typename T>
IOperand const* Operand<T>::operator%(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    if (p > 2)
        throw RunTypeError("taking modulo from non integer");
    if (!strtold(rhs.toString().c_str(), nullptr))
        throw RunTypeError("modulo by zero");
    return OperandController::Instance().createOperand(p, std::to_string(static_cast<long long>(value) % stoll(rhs.toString(), nullptr)));
}



#endif //AVM_OPERAND_H

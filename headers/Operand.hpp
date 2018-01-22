#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include <sstream>
#include "IOperand.h"
#include "OperandController.h"
#include "RunTypeError.h"
#include "NotFitError.h"

template <typename T>
class Operand: public IOperand {

public:

    explicit Operand(T n, eOperandType type);
    ~Operand() = default;
    int getPrecision() const final;
    eOperandType getType() const final;
    std::string string_value;

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
Operand<T>::Operand(T n, eOperandType type): value(n), precision(type), type(type) {}

template <typename T>
IOperand const* Operand<T>::operator+(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    auto val = value + std::strtold(rhs.toString().c_str(), nullptr);
    std::stringstream ss;
    ss << val;
    return OperandController::Instance().createOperand(p, ss.str());

}

template <typename T>
IOperand const* Operand<T>::operator-(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    auto val = value - std::strtold(rhs.toString().c_str(), nullptr);
    std::stringstream ss;
    ss << val;
    return OperandController::Instance().createOperand(p, ss.str());
}

template <typename T>
IOperand const* Operand<T>::operator*(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    auto val = value * std::strtold(rhs.toString().c_str(), nullptr);
    std::stringstream ss;
    ss << val;
    return OperandController::Instance().createOperand(p, ss.str());
}

template <typename T>
IOperand const* Operand<T>::operator/(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    if (!strtold(rhs.toString().c_str(), nullptr))
        throw RunTypeError("division by zero");
    auto val = value / std::strtold(rhs.toString().c_str(), nullptr);
    std::stringstream ss;
    ss << val;
    return OperandController::Instance().createOperand(p, ss.str());
}

template <typename T>
IOperand const* Operand<T>::operator%(IOperand const &rhs) const
{
    eOperandType p = type >= rhs.getType() ? type : rhs.getType();
    if (p > 2)
        throw RunTypeError("taking modulo from non integer");
    if (!strtold(rhs.toString().c_str(), nullptr))
        throw RunTypeError("modulo by zero");
    auto val = static_cast<long long>(value) % std::strtoll(rhs.toString().c_str(), nullptr, 10);
    std::stringstream ss;
    ss << val;
    return OperandController::Instance().createOperand(p, ss.str());
}



#endif //AVM_OPERAND_H

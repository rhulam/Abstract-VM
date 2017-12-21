#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include "IOperand.h"
#include "OperandController.h"
#include "RunTypeError.h"

template <typename T>
class Operand: public IOperand {

public:

    explicit Operand(T n);
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

    class NotFit: public std::exception {

        std::string msg;
        NotFit &operator=(const NotFit &src) = default;
        NotFit() = default;

    public:

        explicit NotFit(const std::string &msg);
        const char *what() const noexcept final;
        ~NotFit() = default;
        NotFit(const NotFit &src);
    };

private:

    T value;
    int precision;
    eOperandType type;
    Operand &operator=(const Operand &src) = default;
    Operand() = default;
    Operand(const Operand &src) = default;

};

template <typename T>
Operand<T>::NotFit::NotFit(const std::string &msg): msg(msg) {};

template <typename T>
const char* Operand<T>::NotFit::what() const noexcept
{
    return msg.c_str();
}

template <typename T>
Operand<T>::NotFit::NotFit(const NotFit &src)
{
    msg = src.msg;
}

template <typename T>
int Operand<T>::getPrecision() const {return precision;}

template <typename T>
eOperandType Operand<T>::getType() const {return type;}

template <typename T>
std::string const& Operand<T>::toString() const {return std::to_string(value);}

template <typename T>
void Operand<T>::check_val(long double l)
{
    if (std::numeric_limits<T>::max() < l)
        throw NotFit("overflow");
    else if (std::numeric_limits<T>::lowest() > l)
        throw NotFit("underflow");
}

template <typename T>
Operand<T>::Operand(T n)
{
    value = n;
    precision = INT8;
    type = INT8;
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

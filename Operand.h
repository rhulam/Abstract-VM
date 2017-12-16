#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include "IOperand.h"
#include "NotFit.h"

template <typename T>
class Operand: public IOperand {

public:

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
    unsigned precision;
    eOperandType type;

};

template <typename T>
int Operand<T>::getPrecision() const {return precision;}

template <typename T>
eOperandType Operand::getType() const {return type;}

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

#endif //AVM_OPERAND_H

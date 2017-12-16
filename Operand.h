#ifndef AVM_OPERAND_H
#define AVM_OPERAND_H

#include "IOperand.h"

template <typename T>
class Operand: public IOperand {

public:

    virtual int getPrecision() const;
    virtual eOperandType getType() const;

    virtual IOperand const * operator+(IOperand const & rhs) const;
    virtual IOperand const * operator-(IOperand const & rhs) const;
    virtual IOperand const * operator*(IOperand const & rhs) const;
    virtual IOperand const * operator/(IOperand const & rhs) const;
    virtual IOperand const * operator%(IOperand const & rhs) const;

    virtual std::string const & toString() const;

    virtual ~IOperand() {};

private:

    T value;

};


#endif //AVM_OPERAND_H

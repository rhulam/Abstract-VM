#ifndef AVM_OPERANDCONTROLLER_H
#define AVM_OPERANDCONTROLLER_H

#include "IOperand.h"

class OperandController //singleton
{

public:
    static OperandController& Instance();
    IOperand const * createOperand(eOperandType type, std::string const & value) const;

    OperandController(OperandController const&&) = delete;
    OperandController& operator= (OperandController &&) = delete;

private:
    OperandController();
    ~OperandController() = default;
    OperandController(OperandController const&) = default;
    OperandController& operator= (OperandController const&) = default;

    IOperand const * createInt8(std::string const & value) const;
    IOperand const * createInt16(std::string const & value) const;
    IOperand const * createInt32(std::string const & value) const;
    IOperand const * createFloat(std::string const & value) const;
    IOperand const * createDouble(std::string const & value) const;

    typedef IOperand const * (OperandController::*functions)(std::string const &) const;
    functions pointers[5];

};


#endif //AVM_OPERANDCONTROLLER_H

#ifndef AVM_AVM_H
#define AVM_AVM_H

#include "OperandController.h"
#include "Operand.hpp"
#include <vector>

class AVM
{

public:
    explicit AVM(const std::vector<std::string> &instructions): instructions(instructions) {};
    void start();
    AVM(const AVM &src) = delete;
    ~AVM() = default;

private:
    OperandController &controller = OperandController::Instance();
    const std::vector<std::string> &instructions;
    std::vector<std::unique_ptr<const IOperand>> stack;
    bool exit = false;

    void pushValue(const std::string &command);
    void popStack();
    void dump() const;
    void assert(const std::string &command) const;
    void operation(char o);
    void print() const;
    void toExit();

    std::string getValue(const std::string &command) const;
    eOperandType getType(const std::string &command) const;
    IOperand const* getValuePointer(const std::string &command) const;
};


#endif //AVM_AVM_H

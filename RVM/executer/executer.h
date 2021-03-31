#ifndef __EXECUTER_HEADER__
#define __EXECUTER_HEADER__

#include "class.h"
#include "value.h"
#include <stack>

struct Context {
    RainClass currentClass;
    std::stack<std::string> methodStack;
    std::stack<Refence> runtimeStack;
    std::vector<Refence> variablePool;
};

class Executer {
    Context context;
    std::vector<Instruction> bytes;
    void __generateIns(std::vector<byte> ins);
public:
    Context& getContext();
    void setClass(std::string classpath);
};

#endif
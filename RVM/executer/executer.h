#ifndef __EXECUTER_HEADER__
#define __EXECUTER_HEADER__

#include "class.h"
#include "value.h"
#include <stack>
#include <map>
struct Context {
    RainClass currentClass;
    std::stack<std::pair<RainClass, Method>> methodStack;
    std::stack<Reference> runtimeStack;
    std::map<int, Reference> variablePool;
};
class Executer {
    Context context;
    std::vector<Instruction> bytes;
    void __generateIns(std::vector<byte> ins);
public:
    Context& getContext();
    void setClass(RainClass clazz);
    void pushValue(Reference ref);
    Reference popValue();
    void throwException(std::string exception);
};

#endif
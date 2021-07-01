#ifndef __EXECUTER_HEADER__
#define __EXECUTER_HEADER__

#include "class.h"
#include "value.h"
#include <stack>
#include <map>

namespace Runtime {
    struct Context {
        RainClass currentClass;
        Method currentMethod;
        std::stack<std::pair<std::pair<RainClass, Method>, r_int>> methodStack;
        std::stack<Reference> runtimeStack;
        std::map<r_int, Reference> variablePool;
    };

    std::pair<std::pair<RainClass, Method>, int> makeMethodInfo(RainClass clazz, Method method, int ins);

    class Executer {
        Context& context;
        std::vector<Instruction> ins;
        int pi;
        std::vector<Instruction> __generateIns(std::shared_ptr<byte[]> ins, int insLen);
    public:
        Executer(Context contextIn);
        void step(Environment *env);
        void run(Environment *env);
        void jmp(int pi);
        void init();
        void pushPi();
    };

    class Environment {
        std::string workDir;
        Context context;
        Executer executer;
    public:
        Context& getContext();
        Executer& getExecuter();
        void setClass(std::string classpath);
        void setClass(RainClass clazz, std::string classpath);
        void setMethod(std::string methodName);
        void setMethod(Method method);
        void pushValue(Reference ref);
        Reference popValue();
        void throwException(std::string exception);
        Environment(std::string workDirIn);
    };

    std::string p2cp(std::string package);
}
#endif
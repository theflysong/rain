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
        std::stack<std::map<r_int, Reference>> vpStack;
        std::stack<Reference> runtimeStack;
        std::map<r_int, Reference> variablePool;
        std::map<std::string, std::map<std::string, Reference>> staticPool;
    };

    struct DebugContext {
        std::vector<int> watches;
        std::vector<int> breaks;
    };

    std::pair<std::pair<RainClass, Method>, int> makeMethodInfo(RainClass clazz, Method method, int ins);

    class Executer {
        Context& context;
        std::vector<Instruction> ins;
        int pi;
        std::vector<Instruction> __generateIns(byte* ins, int insLen);
    public:
        Executer(Context &contextIn);
        void step(Environment *env);
        void run(Environment *env);
        void debug(Environment *env);
        void update_watch(Environment *env);
        void jmp(int pi);
        void init();
        void pushPi();
        void end();
        std::vector<Instruction> getInstructions();
    };

    class Environment {
        std::string workDir;
        Context context;
        DebugContext debug_context;
        Executer executer;
    public:
        Context& getContext();
        DebugContext& getDebugContext();
        Executer& getExecuter();
        void setClass(std::string classpath);
        void setClass(RainClass clazz);
        void setMethod(std::string methodName);
        void setMethod(Method method);
        RainClass createClass(std::string package);
        void loadStatic(std::string package);
        void loadStatic(RainClass clazz);
        void pushValue(Reference ref);
        Reference popValue();
        void throwException(std::string exception);
        Environment(std::string workDirIn);
    };

    extern Reference NullReference;

    std::string p2cp(std::string package);
}
#endif
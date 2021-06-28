#include "executer.h"

namespace Runtime {
    void Executer::pushValue(Reference ref) {
        this->context.runtimeStack.push(ref);
    }

    Reference Executer::popValue() {
        Reference ref = this->context.runtimeStack.top();
        this->context.runtimeStack.pop();
        return ref;
    }

    Context& Executer::getContext() {
        return this->context;
    }

    Executer::Executer(std::string workDirIn) : workDir(workDirIn) {
    }

    /*std::string p2cp(std::string package) {
    }*/
}
#include "executer.h"

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
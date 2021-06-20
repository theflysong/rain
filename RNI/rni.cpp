#include "rni.h"

#include <map>

static std::map<std::string, rni_function> functionTable;

void registryFunction(std::string name, rni_function func) {
    functionTable[name] = func;
}

rni_function getFunction(std::string name) {
    return functionTable[name];
}
#include "System.h"
#include <iostream>

std::shared_ptr<RainReference> _System_print_s(RainUtil* util, RainReference* args, int argSum) {
    if (argSum != 1)
        return std::shared_ptr<RainReference>(&util->getNullReference());
    std::cout << (*args)->getAsString();
    return std::shared_ptr<RainReference>(&util->getNullReference());
}

std::shared_ptr<RainReference> _System_println_s(RainUtil* util, RainReference* args, int argSum) {
    if (argSum != 1)
        return std::shared_ptr<RainReference>(&util->getNullReference());
    std::cout << (*args)->getAsString() << std::endl;
    return std::shared_ptr<RainReference>(&util->getNullReference());
}

MethodInfo System_print_s = {"print(s)V#static", _System_print_s};
MethodInfo System_println_s = {"println(s)V#static", _System_println_s};

MethodInfo systemMethods[] = {System_print_s, System_println_s, NULL_METHOD_INFO};
ClassInfo systemClass = {"rain.lang.System", systemMethods};
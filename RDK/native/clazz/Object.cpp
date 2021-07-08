#include "Object.h"
#include <iostream>

std::shared_ptr<RainReference> _Object_finalize(RainUtil* util, RainReference* args, int argSum) {
    return std::shared_ptr<RainReference>(&util->getNullReference());
}

std::shared_ptr<RainReference> _Object_test(RainUtil* util, RainReference* args, int argSum) {
    if (argSum != 2)
        return std::shared_ptr<RainReference>(&util->getNullReference());
    auto ref = util->make_value();
    (*ref)->set((*args)->getAsInt() + (*util->nxtArg(args))->getAsInt());
    return ref;
}

MethodInfo Object_finalize = {"finalize()V", _Object_finalize};
MethodInfo Object_test = {"test(II)I#static", _Object_test};

MethodInfo objectMethods[] = {Object_finalize, Object_test, NULL_METHOD_INFO};
ClassInfo objectClass = {"rain.clazz.Object", objectMethods};
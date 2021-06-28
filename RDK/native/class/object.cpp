#include "object.h"

r_value _Object_finalize(r_value* args, int argSum) {
    return r_null;
}

r_value _Object_test(r_value* args, int argSum) {
    if (argSum != 2)
        return r_null;
    return {args[0].longV + args[1].longV};
}

MethodInfo Object_finalize = {"finalize(V;)V", _Object_finalize};
MethodInfo Object_test = {"test(II;)I", _Object_test};

MethodInfo objectMethods[] = {Object_finalize, Object_test, NULL_METHOD_INFO};
ClassInfo objectClass = {"rain.lang.Object", objectMethods};
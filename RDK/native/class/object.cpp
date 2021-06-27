#include "object.h"

void _Object_finalize() {
}

MethodInfo Object_finalize = {"finalize(V;)V", _VP(_Object_finalize)};

MethodInfo objectMethods[] = {Object_finalize, NULL_METHOD_INFO};
ClassInfo objectClass = {"rain.lang.Object", objectMethods};
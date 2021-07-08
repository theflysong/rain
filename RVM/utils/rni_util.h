#ifndef __RNI_UTIL_H__
#define __RNI_UTIL_H__

#include <rni.h>
#include <string>
namespace Runtime {
    class Environment;
}
MethodInfo findMethod(const char* libName, const char* class_name, const char* method_name);
void callMethod(Runtime::Environment* env, std::string method_name, MethodPointer method);
ClassInfo findClass(const char* libName, const char* class_name);
void onTerminate();

#endif
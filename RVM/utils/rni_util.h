#ifndef __RNI_UTIL_H__
#define __RNI_UTIL_H__

#include <rni.h>
MethodInfo findMethod(const char* libName, const char* class_name, const char* method_name);
ClassInfo findClass(const char* libName, const char* class_name);
void onTerminate();

#endif
#ifndef __RNI_H__
#define __RNI_H__

#include <stdint.h>

typedef int64_t rlong;
typedef int32_t rint;
typedef int16_t rshort;
typedef uint64_t urlong;
typedef uint32_t urint;
typedef uint16_t urshort;

struct MethodInfo {
    const char* name;
    void* method;
};

struct ClassInfo {
    const char* name;
    MethodInfo* method;
};

#define NULL_METHOD_INFO {"",(void*)0}
#define NULL_CLASS_INFO {"",(MethodInfo*)0}

#define _VP(x) ((void*)x)

typedef ClassInfo*(*GetInstFunc)();

#endif
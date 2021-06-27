#ifndef __RNI_H__
#define __RNI_H__

#include <stdint.h>

typedef int64_t r_long;
typedef int32_t r_int;
typedef int16_t r_short;
typedef uint64_t ur_long;
typedef uint32_t ur_int;
typedef uint16_t ur_short;

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
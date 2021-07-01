#ifndef __RNI_H__
#define __RNI_H__

#include <stdint.h>

#include "types.h"

#define r_null r_value{0}

struct r_object;
struct r_value {
    union {
        r_long longV;
        r_int intV;
        r_short shortV;
        r_byte byteV;
        ur_long ulongV;
        ur_int uintV;
        ur_short ushortV;
        ur_byte ubyteV;
        r_real realV;
    };
    r_object* objV;
};

#include <map>
#include <string>
struct r_object {
    std::map<std::string, r_value> values;
};

typedef r_value(*MethodPointer)(r_value*, int);

struct MethodInfo {
    const char* name;
    MethodPointer method;
};

struct ClassInfo {
    const char* name;
    MethodInfo* method;
};

#define NULL_METHOD_INFO {"",(MethodPointer)0}
#define NULL_CLASS_INFO {"",(MethodInfo*)0}

typedef ClassInfo*(*GetInstFunc)();

#endif
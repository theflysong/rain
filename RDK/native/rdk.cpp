#include "rdk.h"
#include "clazz/object.h"

ClassInfo class_infos[] = {
    objectClass,
    NULL_CLASS_INFO
};

ClassInfo* GetInstance() {
    return class_infos;
}
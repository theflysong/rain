#include "rdk.h"
#include "clazz/packages_info.h"
#include "lang/packages_info.h"

ClassInfo class_infos[] = {
    objectClass, systemClass,
    NULL_CLASS_INFO
};

ClassInfo* GetInstance() {
    return class_infos;
}
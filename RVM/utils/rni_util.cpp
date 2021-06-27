#include "rni_util.h"
#include "osplatformutil.h"

#include <map>
#include <string>
#include <iostream>
#include <cstring>

#ifdef I_OS_WIN
#define byte a_byte
#include <windows.h>
#undef byte
std::map<std::string, HMODULE> loadedList;

HMODULE GetModule(const char* libName) {
    if (loadedList.count(libName)) {
        return loadedList[libName];
    }
    else {
        return LoadLibraryA(((std::string)libName + ".dll").c_str());
    }
}

ClassInfo findClass(const char* libName, const char* class_name) {
    GetInstFunc func = (GetInstFunc)GetProcAddress(GetModule(libName), "_Z11GetInstancev");
    ClassInfo* infos = func();
    int cur = 0;
    while (true) {
        ClassInfo info = infos[cur ++];
        if (! strcmp(info.name, ""))
            break;
        if (! strcmp(info.name, class_name))
            return info;
    }
    return NULL_CLASS_INFO;
}

void onTerminate() {
    for (auto p : loadedList)
        FreeLibrary(p.second);
    loadedList.clear();
}
#endif

#if defined(I_OS_LINUX) || defined(I_OS_MACOS)
#ifdef I_OS_LINUX
std::string getLibName(const char* libName) {
    return (std::string)"lib" + libName + ".so";
}
#else
std::string getLibName(const char* libName) {
    return (std::string)"lib" + libName + ".dylib";
}
#endif
#include <dlfcn.h>
std::map<std::string, void*> loadedList;

void* GetLib(const char* libName) {
    if (loadedList.count(libName)) {
        return loadedList[libName];
    }
    else {
        return dlopen(getLibName(libName).c_str(), RTLD_LAZY);
    }
}

ClassInfo findClass(const char* libName, const char* class_name) {
    GetInstFunc func = (GetInstFunc)dlsym(GetLib(libName), "_Z11GetInstancev");
    ClassInfo* infos = func();
    int cur = 0;
    while (true) {
        ClassInfo info = infos[cur ++];
        if (! strcmp(info.name, ""))
            break;
        if (! strcmp(info.name, class_name))
            return info;
    }
    return NULL_CLASS_INFO;
}

void onTerminate() {
    for (auto p : loadedList)
        dlclose(p.second);
    loadedList.clear();
}
#endif

MethodInfo findMethod(const char* libName, const char* class_name, const char* method_name) {
    ClassInfo info = findClass(libName, class_name);
    if (! strcmp(info.name, ""))
        return NULL_METHOD_INFO;
    int cur = 0;
    while (true) {
        MethodInfo minfo = info.method[cur ++];
        if (! strcmp(minfo.name, ""))
            break;
        if (! strcmp(minfo.name, method_name))
            return minfo;
    }
    return NULL_METHOD_INFO;
}
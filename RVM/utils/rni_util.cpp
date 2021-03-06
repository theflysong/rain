#include "rni_util.h"
#include "osplatformutil.h"

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
    return (std::string)"./lib" + libName + ".so";
}
#else
std::string getLibName(const char* libName) {
    return (std::string)"./lib" + libName + ".dylib";
}
#endif
#include <dlfcn.h>
std::map<std::string, void*> loadedList;

void* GetLib(const char* libName) {
    if (loadedList.count(libName)) {
        return loadedList[libName];
    }
    else {
        void* p = dlopen(getLibName(libName).c_str(), RTLD_LAZY);
        const char* error = dlerror();
        if (error != (const char*)0) {
            std::cerr << error << std::endl;
        }
        return p;
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

#include "../executer/executer.h"

class RainUtilImpl : public RainUtil {
    std::shared_ptr<RainReference> make_value() override {
        return std::make_shared<Runtime::Reference>(std::make_shared<Runtime::Value>());
    }
    std::shared_ptr<RainReference> call_method(std::string method_path, RainReference* args, int argNum) override {
        std::cout << "native call vm method" << std::endl;
        return std::make_shared<Runtime::Reference>(std::make_shared<Runtime::Value>());
    }
    RainReference* nxtArg(RainReference* args) override {
        return ((Runtime::Reference*)args) + 1;
    }
    RainReference& getNullReference() override {
        return Runtime::NullReference;
    }
}__RainUtilImpl;

void callMethod(Runtime::Environment* env, std::string method_name, MethodPointer method) {
    int pos = method_name.find('(');
    int arg_num = 0;
    while (method_name[++ pos] != ')') {
        arg_num ++;
        if (method_name[pos] == '[') {
            ++ pos;
        }
        if (method_name[pos] == '{') {
            while (method_name[++ pos] != ';');
        }
    }

    if (method_name.find("#static") == std::string::npos)
        arg_num ++;

    Runtime::Reference refs[arg_num];
    int arg_num_ = arg_num;

    while (--arg_num_ >= 0) {
        refs[arg_num_] = env->popValue();
    }

    std::shared_ptr<RainReference> ref = method(&__RainUtilImpl, refs, arg_num);
    if (Runtime::NullReference != *ref.get());
        env->pushValue(Runtime::Reference(ref.get()).copy());
}
//WIP!!!!!
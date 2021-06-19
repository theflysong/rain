#ifndef __RNI_H__
#define __RNI_H__

#include <vector>
#include <string>

struct Value {
    void* get();
    bool isClass;
    Value getMember(std::string name);
};

#define _INIT_ extern "C" void init()
typedef void(*rni_function)(std::vector<Value>);

void registryFunction(std::string name, rni_function func);
rni_function getFunction(std::string name);

#endif
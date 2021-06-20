#ifndef __RNI_H__
#define __RNI_H__

#include <vector>
#include <string>

struct RNIValue {
    void* ptr;
    bool isClass;
    RNIValue(*getMember)(std::string name);
};

#define _INIT_ extern "C" void init()
typedef RNIValue(*rni_function)(std::vector<RNIValue>);

void registryFunction(std::string name, rni_function func);
rni_function getFunction(std::string name);

#endif
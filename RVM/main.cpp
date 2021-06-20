#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/tostringhelper.h"
#include <iostream>
#include "lib/rni.h"

RNIValue func(std::vector<RNIValue>) {
    RNIValue result {new int};
    *(int*)(result.ptr) = 2;
    return result;
}

int main(int argc, char** argv) {
    int a = 1, b = 2;
    std::cout << 1 << std::endl;
    registryFunction("func", func);
    RNIValue result = getFunction("func")(std::vector<RNIValue>());
    std::cout << result.ptr << std::endl;
    delete result.ptr;
    return 0;
}
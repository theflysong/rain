#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/stringhelper.h"
#include <iostream>
#include <cstring>
#include "./utils/rni_util.h"

int main(int argc, char** argv) {
    MethodInfo info = findMethod("RdkNative", "rain.lang.Object", "test(II;)I");
    r_value args[2] = {{1}, {2}};
    std::cout << (int)info.method(args, 2).longV;
    return 0;
}
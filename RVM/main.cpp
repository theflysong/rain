#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/tostringhelper.h"
#include <iostream>
#include <cstring>
#include "./utils/rni_util.h"

int main(int argc, char** argv) {
    std::cout << findMethod("RdkNative", "rain.lang.Object", "finalize(V;)I").method;
    std::cout << findMethod("RdkNative", "rain.lang.Object", "finalize(V;)V").method;
    return 0;
}

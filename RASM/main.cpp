#include <string>
#include <iostream>
#include <fstream>
#include "translator.h"
#include "info_gen.h"

int main(int argc, const char** argv) {
    if (argc <= 1) {
        return -1;
    }
    std::ifstream fin(argv[1]);
    RainClass clazz;

    _clazzGen(fin, clazz);

    while (! fin.eof()) {
    }
    //Ins ins = translate("push \"1\"", clazz.const_pool);
    return 0;
}
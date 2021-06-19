#include <string>
#include <iostream>
#include <fstream>
#include "translator.h"
#include "info_gen.h"

int main(int argc, const char** argv) {
    if (argc <= 2) {
        return -1;
    }
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2], std::ios::binary);
    RainClass clazz = {};

    _clazzGen(fin, clazz);
    std::vector<std::string> insList;

    while (! fin.eof()) {
        _memberGen(fin, insList, clazz);
    }
    generate(fout, clazz, insList);
    return 0;
}
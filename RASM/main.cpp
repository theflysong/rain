#include <string>
#include <iostream>
#include "translator.h"

int main() {
    std::pair<int, byte*> p = transIns("nop", '\0', 0);
    std::cout << p.first;
    delete[] p.second;
    return 0;
}
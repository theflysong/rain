#include <string>
#include <iostream>
#include "translator.h"

int main() {
    std::vector<std::string> const_pool;
    Ins ins = translate("push \"1\"", const_pool);
    //std::pair<int, byte*> p = transIns("nop", Typer::NONE, 0);
    //std::cout << p.first;
    //delete[] p.second;
    return 0;
}
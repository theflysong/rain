#include "translator.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Ins translate(std::string str, std::vector<std::string> &const_pool) {
    if (str.find(' ') + 1 == 0)
        return Ins{str, Typer::NONE, 0};
    std::string ins = str.substr(0, str.find(' '));
    str = str.substr(str.find(' ') + 1);
    char typer = str[0];
    if (typer == '"') {
        const_pool.push_back(str.substr(1, str.size() - 2));
        return Ins{ins, Typer::CONSTANT, const_pool.size() - 1};
    }
    return Ins{ins, toTyper(typer), atoll(str.substr(1).c_str())};
}
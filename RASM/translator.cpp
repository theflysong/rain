#include "translator.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

Ins translate(std::string str, std::vector<std::string> &const_pool, std::map<std::string, r_int> &name2no) {
    if (str.find(' ') + 1 == 0)
        return Ins{str, Typer::NONE, 0};
    std::string ins = str.substr(0, str.find(' '));
    str = str.substr(str.find(' ') + 1);
    char typer = str[0];
    if (typer == '"') {
        std::string cst = str.substr(1, str.size() - 2);
        if (! name2no.count(cst)) {
            name2no[cst] = const_pool.size();
            const_pool.push_back(cst);
        }
        return Ins{ins, Typer::CONSTANT, name2no[cst]};
    }
    return Ins{ins, toTyper(typer), atoll(str.substr(1).c_str())};
}
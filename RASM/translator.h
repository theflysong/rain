#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include "generator.h"

#include <vector>
#include <string>
#include <map>

struct Ins {
    std::string ins;
    Typer typer;
    long long op;
};

Ins translate(std::string str, std::vector<std::string> &const_pool, std::map<std::string, r_int> &name2no);

#endif
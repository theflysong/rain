#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include "generator.h"

#include <vector>
#include <string>

struct Ins {
    std::string ins;
    Typer typer;
    long long op;
};

Ins translate(std::string str, std::vector<std::string> &const_pool);

#endif
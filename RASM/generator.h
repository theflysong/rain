#ifndef __GENERATOR__
#define __GENERATOR__

#include <string>
#include "const/defs.h"
#include "class_info.h"

enum class Typer {
    NONE,
    CONSTANT,
    VARIABLE,
    IMMEDIATE_BYTE,
    IMMEDIATE_WORD,
    IMMEDIATE_DWORD,
    IMMEDIATE_QWORD,
    UNKNOWN
};

std::pair<int, byte*> genIns(std::string ins, Typer typer, long long op);
byte TyperToByte(Typer typer, long long op);
Typer toTyper(int typer);
Typer toTyper(char typer);

void generate(std::ostream& ostream, RainClass clazz, std::vector<std::string> insList);

#endif
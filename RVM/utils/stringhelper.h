#ifndef __STRINGHELPER_HEADER__
#define __STRINGHELPER_HEADER__

#include "../const/defs.h"
#include <string>

std::string acceseToString(byte accese);
std::string toString(bool flag);
std::string replaceAll(std::string source, std::string from, std::string to);

#endif
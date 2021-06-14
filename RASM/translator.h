#ifndef __TRANSLATOR__
#define __TRANSLATOR__

#include <string>
#include "const/defs.h"

std::pair<int, byte*> transIns(std::string ins, char typer, long long op);

#endif
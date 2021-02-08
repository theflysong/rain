#ifndef __INSTRUCTION_HEADER__
#define __INSTRUCTION_HEADER__

#include "../const/defs.h"
#include <map>

class Executer;

typedef void(ins_handle)(Executer*);

std::map<byte, ins_handle> ins_map;

#endif
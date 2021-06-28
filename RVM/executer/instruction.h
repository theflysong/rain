#ifndef __INSTRUCTION_HEADER__
#define __INSTRUCTION_HEADER__

#include "../const/defs.h"
#include "../reader/reader.h"
#include <map>

namespace Runtime {
    class Executer;
    struct Instruction;

    typedef void(*ins_handle)(Executer*, Instruction ins);

    void __ins_init();

    extern std::map<byte, ins_handle> ins_map;

    struct Instruction {
        ins_handle handle;
        byte typer;
        long long op;
    };

    Instruction genIns(IByteReader& reader);
}

#endif
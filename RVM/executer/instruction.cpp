#include "instruction.h"
#include "executer.h"
#include <cstdio>

std::map<byte, ins_handle> ins_map;

void __test_printer(Executer* exe, Instruction op) {
    printf("Test output");
}

void __ins_init() {
    ins_map[0xff] = __test_printer;
}

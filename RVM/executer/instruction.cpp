#include "instruction.h"
#include "executer.h"
#include <cstdio>

std::map<byte, ins_handle> ins_map;

void __test_printer(Executer* exe, Instruction ins) {
    printf("Test output:%d\n", ins.op);
}

void _nop(Executer* exe, Instruction ins) {
}

void _add(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() + num2.getValue()->getAsNumber())));
}

void _sub(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() - num2.getValue()->getAsNumber())));
}

void _mul(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() * num2.getValue()->getAsNumber())));
}

void _div(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() / num2.getValue()->getAsNumber())));
}

void _mod(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((int)num1.getValue()->getAsNumber()) % ((int)num2.getValue()->getAsNumber()))));
}

void _shr(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((int)num1.getValue()->getAsNumber()) >> ((int)num2.getValue()->getAsNumber()))));
}

void _shl(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((int)num1.getValue()->getAsNumber()) << ((int)num2.getValue()->getAsNumber()))));
}

void __ins_init() {
    ins_map[0x00] = _nop;
    ins_map[0x01] = _add;
    ins_map[0x02] = _sub;
    ins_map[0x03] = _mul;
    ins_map[0x04] = _div;
    ins_map[0x05] = _mod;
    ins_map[0x06] = _shr;
    ins_map[0x07] = _shl;
    ins_map[0xff] = __test_printer;
}

Instruction genIns(IByteReader& reader) {
    byte ins = reader.next();
    byte typer = reader.next();
    long long op;
    if (typer & 1) {
        if (typer == 5)
            op = reader.next();
        else
            op = reader.getAsInt();
    }
    else if (typer == 6) {
        op = reader.getAsShort();
    }
    else if (! typer) {
        op = 0;
    }
    else {
        op = reader.getAsLongLong();
    }
    return Instruction{ins_map[ins], typer, op};
}
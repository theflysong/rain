#include "instruction.h"
#include "executer.h"
#include <cstdio>

std::map<byte, ins_handle> ins_map;

struct TyperValue {
    Reference ref;
    std::string con;
    long long value;
    bool isRef;
    bool isCon;
    bool isValue;
};

TyperValue makeTyper(Reference ref) {
    TyperValue tv = {};
    tv.ref = ref;
    tv.isRef = true;
    return tv;
}

TyperValue makeTyper(std::string con) {
    TyperValue tv = {};
    tv.con = con;
    tv.isCon = true;
    return tv;
}

TyperValue makeTyper(long long value) {
    TyperValue tv = {};
    tv.value = value;
    tv.isValue = true;
    return tv;
}

TyperValue makeTyper() {
    TyperValue tv = {};
    return tv;
}

TyperValue getByTyper(Executer *exe, byte typer, long long op) {
    switch (typer) {
    case 1:
    case 2:
        return makeTyper(exe->getContext().currentClass.const_pool[op]);
    case 3:
    case 4:
        return makeTyper(exe->getContext().variablePool[op]);
    case 5:
    case 6:
    case 7:
    case 8:
        return makeTyper(op);
    default:
        return makeTyper();
    }
}

void __test_printer(Executer* exe, Instruction ins) {
    printf("Test output:%lld\n", ins.op);
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

void _push(Executer* exe, Instruction ins) {
    TyperValue tv = getByTyper(exe, ins.typer, ins.op);
    if (tv.isValue)
        exe->pushValue(Reference(std::make_shared<Value>(tv.value)));
    if (tv.isCon)
        exe->pushValue(Reference(std::make_shared<Value>(tv.con)));
    if (tv.isRef)
        exe->pushValue(tv.ref);
}

void _pop(Executer* exe, Instruction ins) {
    exe->getContext().variablePool[ins.op] = exe->popValue();
}

void _call(Executer* exe, Instruction ins) { //TODO
}

void _sml(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() < num2.getValue()->getAsNumber())));
}

void _big(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() > num2.getValue()->getAsNumber())));
}

void _equ(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() == num2.getValue()->getAsNumber())));
}

void _seq(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() <= num2.getValue()->getAsNumber())));
}

void _beq(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(num1.getValue()->getAsNumber() >= num2.getValue()->getAsNumber())));
}

void _not(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(!(bool)num1.getValue()->getAsNumber())));
}

void _neg(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(-num1.getValue()->getAsNumber())));
}

void _and(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((bool)num1.getValue()->getAsNumber()) & ((bool)num2.getValue()->getAsNumber()))));
}

void _or(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((bool)num1.getValue()->getAsNumber()) | ((bool)num2.getValue()->getAsNumber()))));
}

void _xor(Executer* exe, Instruction ins) {
    Reference num1 = exe->popValue();
    Reference num2 = exe->popValue();

    if (num1.getValue()->getType() != Value::NUMBER || num2.getValue()->getType() != Value::NUMBER)
        return;

    exe->pushValue(Reference(std::make_shared<Value>(((bool)num1.getValue()->getAsNumber()) ^ ((bool)num2.getValue()->getAsNumber()))));
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
    ins_map[0x08] = _push;
    ins_map[0x09] = _pop;
    ins_map[0x0A] = _call;
    ins_map[0x0B] = _sml;
    ins_map[0x0C] = _big;
    ins_map[0x0D] = _equ;
    ins_map[0x0E] = _seq;
    ins_map[0x0F] = _beq;
    ins_map[0x10] = _not;
    ins_map[0x12] = _neg;
    ins_map[0x13] = _and;
    ins_map[0x14] = _or;
    ins_map[0x15] = _xor;
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
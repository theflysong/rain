#include "translator.h"
#include "json/CJsonObject.hpp"
#include <iostream>
#include "utils/bytehelper.h"

neb::CJsonObject translator(
#include "instructions.jstr"
);

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

Typer toTyper(char typer) {
    switch (typer) {
    case '\0':
        return Typer::NONE;
    case '$':
        return Typer::IMMEDIATE_DWORD;
    case '^':
        return Typer::IMMEDIATE_QWORD;
    case '#':
        return Typer::IMMEDIATE_WORD;
    case '@':
        return Typer::IMMEDIATE_BYTE;
    case '%':
        return Typer::VARIABLE;
    case '&':
        return Typer::CONSTANT;
    default:
        return Typer::UNKNOWN;
    }
}

Typer toTyper(int typer) {
    if (typer == 0)
        return Typer::NONE;
    if (typer == 1 || typer == 2)
        return Typer::CONSTANT;
    if (typer == 3 || typer == 4)
        return Typer::VARIABLE;
    if (typer == 5)
        return Typer::IMMEDIATE_BYTE;
    if (typer == 6)
        return Typer::IMMEDIATE_WORD;
    if (typer == 7)
        return Typer::IMMEDIATE_DWORD;
    if (typer == 8)
        return Typer::IMMEDIATE_QWORD;
    return Typer::UNKNOWN;
}

byte TyperToByte(Typer typer, long long op) {
    switch (typer) {
    case Typer::CONSTANT:
        if (((unsigned long long)op) >= INT_MAX) {
            return 2;
        }
        else {
            return 1;
        }
    case Typer::VARIABLE:
        if (((unsigned long long)op) >= INT_MAX) {
            return 4;
        }
        else {
            return 3;
        }
    case Typer::IMMEDIATE_BYTE:
        return 5;
    case Typer::IMMEDIATE_WORD:
        return 6;
    case Typer::IMMEDIATE_DWORD:
        return 7;
    case Typer::IMMEDIATE_QWORD:
        return 8;
    default:
        return 0xff;
    }
}

bool accept(neb::CJsonObject accepts, Typer typer) {
    for (int i = 0, a_t ; i < accepts.GetArraySize() ; i ++) {
        accepts.Get(i, a_t);
        if (toTyper(a_t) == typer)
            return true;
    }
    return false;
}

std::pair<int, byte*> transIns(std::string ins, char typer, long long op) {
    if (! translator.KeyExist(ins))
        throw (std::string)"Unknown instruction" + ins;
    neb::CJsonObject inst = translator[ins];
    int code;
    inst.Get("code", code);
    Typer ty = toTyper(typer);
    if (! accept(inst["type"], ty))
        throw (std::string)"Wrong type";
    if (ty == Typer::NONE) {
        byte* b = new byte[2];
        b[0] = code;
        b[1] = 0;
        return std::make_pair(2, b);
    }
    else {
        byte b_t = TyperToByte(ty, op);
        byte b_op[16];
        asByte(op, b_op);
        if (b_t % 2 == 0) {
            if (b_t == 6) {
                byte* b = new byte[4];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[0];
                b[3] = b_op[1];
                return std::make_pair(4, b);
            }
            else {
                byte* b = new byte[10];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[0];
                b[3] = b_op[1];
                b[4] = b_op[2];
                b[5] = b_op[3];
                b[6] = b_op[4];
                b[7] = b_op[5];
                b[8] = b_op[6];
                b[9] = b_op[7];
                return std::make_pair(10, b);
            }
        }
        else {
            if (b_t == 5) {
                byte* b = new byte[3];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[0];
                return std::make_pair(3, b);
            }
            else {
                byte* b = new byte[6];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[0];
                b[3] = b_op[1];
                b[4] = b_op[2];
                b[5] = b_op[3];
                return std::make_pair(6, b);
            }
        }
    }
}
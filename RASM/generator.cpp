#include "generator.h"
#include "translator.h"
#include "json/CJsonObject.hpp"
#include <iostream>
#include "utils/bytehelper.h"
#include <map>

neb::CJsonObject generator(
#include "instructions.jstr"
);

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

std::pair<int, byte*> genIns(std::string ins, Typer typer, long long op) {
    if (! generator.KeyExist(ins))
        throw (std::string)"Unknown instruction" + ins;
    neb::CJsonObject inst = generator[ins];
    int code;
    inst.Get("code", code);
    if (! accept(inst["type"], typer))
        throw (std::string)"Wrong type with " + ins;
    if (typer == Typer::NONE) {
        byte* b = new byte[2];
        b[0] = code;
        b[1] = 0;
        return std::make_pair(2, b);
    }
    else {
        byte b_t = TyperToByte(typer, op);
        byte b_op[16];
        asByte(op, b_op);
        if (b_t % 2 == 0) {
            if (b_t == 6) {
                byte* b = new byte[4];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[6];
                b[3] = b_op[7];
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
                b[2] = b_op[7];
                return std::make_pair(3, b);
            }
            else {
                byte* b = new byte[6];
                b[0] = code;
                b[1] = b_t;
                b[2] = b_op[4];
                b[3] = b_op[5];
                b[4] = b_op[6];
                b[5] = b_op[7];
                return std::make_pair(6, b);
            }
        }
    }
}

inline byte CA2B(RainClass clazz) {
    byte b;
    b = (clazz.access == "public" ? 0
        : clazz.access == "friendly" ? 1
        : clazz.access == "protected" ? 2
        : clazz.access == "private" ? 3 : -1) + (clazz.is_member << 2) + (clazz.parents.size() << 3);
    return b;
}

inline byte FA2B(Field field) {
    byte b;
    b = (field.access == "public" ? 0
        : field.access == "friendly" ? 1
        : field.access == "protected" ? 2
        : field.access == "private" ? 3 : -1) + (field.is_static << 2) + (field.is_const << 3);
    return b;
}

inline byte MA2B(Method method) {
    byte b;
    b = (method.access == "public" ? 0
        : method.access == "friendly" ? 1
        : method.access == "protected" ? 2
        : method.access == "private" ? 3 : -1) + (method.is_static << 2) + (method.is_final << 3);
    return b;
}

void generate(std::ostream& ostream, RainClass clazz, std::vector<std::string> insList) {
    std::map<std::string, int> name2no;
    for (Field field : clazz.fields) {
        name2no[field.name] = clazz.const_pool.size();
        clazz.const_pool.push_back(field.name);
    }
    for (Method method : clazz.methods) {
        name2no[method.name] = clazz.const_pool.size();
        clazz.const_pool.push_back(method.name);
    }
    for (std::string memberClass : clazz.memberClasses) {
        name2no[memberClass] = clazz.const_pool.size();
        clazz.const_pool.push_back(memberClass);
    }
    for (std::string parent : clazz.parents) {
        name2no[parent] = clazz.const_pool.size();
        clazz.const_pool.push_back(parent);
    }for (std::string attr : clazz.attributes) {
        name2no[attr] = clazz.const_pool.size();
        clazz.const_pool.push_back(attr);
    }
    std::vector<Ins> instructions;
    for (auto str : insList) {
        instructions.push_back(translate(str, clazz.const_pool));
    }

    byte* b = new byte[65536];
    ostream.write(asByte((int)clazz.const_pool.size(), b), 4);

    for (auto str : clazz.const_pool) {
        ostream.write(asByte((short)str.length(), b), 2);
        ostream.write(str.c_str(), str.length());
    }

    byte b_ca = CA2B(clazz);
    ostream.write(&b_ca, 1);
    for (auto par : clazz.parents) {
        ostream.write(asByte((short)name2no[par], b), 2);
    }

    b_ca = clazz.attributes.size();
    ostream.write(&b_ca, 1);
    for (auto attr : clazz.attributes) {
        ostream.write(asByte((short)name2no[attr], b), 2);
    }

    ostream.write(asByte((short)clazz.fields.size(), b), 2);
    for (auto field : clazz.fields) {
        b_ca = FA2B(field);
        ostream.write(&b_ca, 1);
        ostream.write(asByte((short)name2no[field.name], b), 2);
    }

    ostream.write(asByte((short)clazz.memberClasses.size(), b), 2);
    for (auto memberClass : clazz.memberClasses) {
        ostream.write(asByte((short)name2no[memberClass], b), 2);
    }

    ostream.write(asByte((short)clazz.methods.size(), b), 2);
    for (auto method : clazz.methods) {
        b_ca = MA2B(method);
        ostream.write(&b_ca, 1);
        ostream.write(asByte((short)name2no[method.name], b), 2);
    }

    std::vector<std::pair<int, byte*>> codes;
    int code_length = 0;
    for (auto ins : instructions) {
        try {
            auto p = genIns(ins.ins, ins.typer, ins.op);
            code_length += p.first;
            codes.push_back(p);
        }
        catch (std::string str) {
            std::cout << str << std::endl;
        }
    }

    ostream.write(asByte(code_length, b), 4);
    for (auto p : codes) {
        ostream.write(p.second, p.first);
        delete[] p.second;
    }
    delete b;
}
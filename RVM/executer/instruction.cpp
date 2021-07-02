#include "instruction.h"
#include "executer.h"
#include <cstdio>
#include <iostream>
#include <algorithm>

namespace Runtime {
    std::map<byte, ins_handle> ins_map;
    std::map<ins_handle, std::string> name_map;

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
    TyperValue getByTyper(Environment *env, byte typer, long long op) {
        switch (typer) {
        case 1:
        case 2:
            return makeTyper(env->getContext().currentClass.const_pool[op]);
        case 3:
        case 4:
            return makeTyper(env->getContext().variablePool[op]);
        case 5:
        case 6:
        case 7:
        case 8:
            return makeTyper(op);
        default:
            return makeTyper();
        }
    }

    inline bool checkNative(Method method, RainClass clazz) {
        std::vector<std::string> attr = clazz.sub_attach_attr[method.name];
        return std::find(attr.begin(), attr.end(), "native") != attr.end();
    }

    void _ret(Environment* env, Instruction ins);

    void __test_printer(Environment* env, Instruction ins) {
        printf("Test output:%lld\n", ins.op);
    }
    void _nop(Environment* env, Instruction ins) {
    }
    void _add(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() + num2->getAsNumber())));
    }
    void _sub(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() - num2->getAsNumber())));
    }
    void _mul(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() * num2->getAsNumber())));
    }
    void _div(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() / num2->getAsNumber())));
    }
    void _mod(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((int)num1->getAsNumber()) % ((int)num2->getAsNumber()))));
    }
    void _shr(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((int)num1->getAsNumber()) >> ((int)num2->getAsNumber()))));
    }
    void _shl(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((int)num1->getAsNumber()) << ((int)num2->getAsNumber()))));
    }
    void _push(Environment* env, Instruction ins) {
        TyperValue tv = getByTyper(env, ins.typer, ins.op);
        if (tv.isValue)
            env->pushValue(Reference(std::make_shared<Value>(tv.value)));
        if (tv.isCon)
            env->pushValue(Reference(std::make_shared<Value>(tv.con)));
        if (tv.isRef)
            env->pushValue(tv.ref);
    }
    void _pop(Environment* env, Instruction ins) {
        env->getContext().variablePool[ins.op] = env->popValue();
    }
    void _call(Environment* env, Instruction ins) {
        env->getExecuter().pushPi();
        std::string methodpath = env->getContext().currentClass.const_pool[ins.op];
        std::string package = methodpath.substr(0, methodpath.find_last_of('.'));
        std::string methodName = methodpath.substr(methodpath.find_last_of('.') + 1);
        if (env->getContext().currentClass.package != package) {
            env->setClass(package);
        }
        Method method = env->getContext().currentClass.method_pool[methodName];
        env->setMethod(method);
        if (checkNative(method, env->getContext().currentClass)) {
            std::cout << "It's native method";
            _ret(env, ins);
            return;
        }
        env->getExecuter().jmp(method.attributes.start);
    }
    void _sml(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() < num2->getAsNumber())));
    }
    void _big(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() > num2->getAsNumber())));
    }
    void _equ(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() == num2->getAsNumber())));
    }
    void _seq(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() <= num2->getAsNumber())));
    }
    void _beq(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(num1->getAsNumber() >= num2->getAsNumber())));
    }
    void _not(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();

        if (num1->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(!(bool)num1->getAsNumber())));
    }
    void _neg(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();

        if (num1->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(-num1->getAsNumber())));
    }
    void _and(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((bool)num1->getAsNumber()) & ((bool)num2->getAsNumber()))));
    }
    void _or(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((bool)num1->getAsNumber()) | ((bool)num2->getAsNumber()))));
    }
    void _xor(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();
        Reference num2 = env->popValue();

        if (num1->getType() != Value::NUMBER || num2->getType() != Value::NUMBER)
            return;

        env->pushValue(Reference(std::make_shared<Value>(((bool)num1->getAsNumber()) ^ ((bool)num2->getAsNumber()))));
    }
    void _jmp(Environment* env, Instruction ins) {
        env->getExecuter().jmp(ins.op);
    }
    void _jt(Environment* env, Instruction ins) {
        Reference ref = env->popValue();
        if (ref->getType() != Value::NUMBER)
            return;
        if (! ref->getAsNumber())
            return;
        _jmp(env, ins);
    }
    void _jf(Environment* env, Instruction ins) {
        Reference ref = env->popValue();
        if (ref->getType() != Value::NUMBER)
            return;
        if (ref->getAsNumber())
            return;
        _jmp(env, ins);
    }
    void _ret(Environment* env, Instruction ins) {
        if (env->getContext().methodStack.empty()) {
            env->getExecuter().end();
            return;
        }
        auto info = env->getContext().methodStack.top();
        env->getContext().methodStack.pop();
        env->setClass(info.first.first, info.first.first.package);
        env->setMethod(info.first.second);
        env->getExecuter().jmp(info.second);
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
        ins_map[0x15] = _jmp;
        ins_map[0x16] = _jt;
        ins_map[0x17] = _jf;
        ins_map[0x18] = _ret;
        ins_map[0xff] = __test_printer;
        name_map[_nop] = "nop";
        name_map[_add] = "add";
        name_map[_sub] = "sub";
        name_map[_mul] = "mul";
        name_map[_div] = "div";
        name_map[_mod] = "mod";
        name_map[_shr] = "shr";
        name_map[_shl] = "shl";
        name_map[_push] = "push";
        name_map[_pop] = "pop";
        name_map[_call] = "call";
        name_map[_sml] = "sml";
        name_map[_big] = "big";
        name_map[_equ] = "equ";
        name_map[_seq] = "seq";
        name_map[_beq] = "beq";
        name_map[_not] = "not";
        name_map[_neg] = "neg";
        name_map[_and] = "and";
        name_map[_or] = "or";
        name_map[_jmp] = "jmp";
        name_map[_jt] = "jt";
        name_map[_jf] = "jf";
        name_map[_ret] = "ret";
        name_map[__test_printer] = "test_printer";
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
            op = reader.getAsLong();
        }
        return Instruction{ins_map[ins], typer, op};
    }
}
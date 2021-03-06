#include "instruction.h"
#include "executer.h"
#include "../utils/rni_util.h"
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
        return _VHAS(attr, "native");
    }

    void _ret(Environment* env, Instruction ins);

    void __test_printer(Environment* env, Instruction ins) {
        printf("Test output:%lld\n", ins.op);
    }
    void _nop(Environment* env, Instruction ins) {
    }
    template<typename Func> Reference __calc_helper(Reference num1, Func op) {
        if (num1->getType() == Value::REAL)
            return Reference(std::make_shared<Value>(op(num1->getAsReal())));
        if (num1->getType() == Value::BYTE)
            return Reference(std::make_shared<Value>(op(num1->getAsByte())));
        if (num1->getType() == Value::SHORT)
            return Reference(std::make_shared<Value>(op(num1->getAsShort())));
        if (num1->getType() == Value::INT)
            return Reference(std::make_shared<Value>(op(num1->getAsInt())));
        if (num1->getType() == Value::LONG)
            return Reference(std::make_shared<Value>(op(num1->getAsLong())));
        throw "Invalid Value Type for Calc";
    }
    template<typename Func> Reference __calc_helper(Reference num1, Reference num2, Func op) {
        if (num1->getType() == Value::REAL && num2->getType() == Value::REAL)
            return Reference(std::make_shared<Value>(op(num1->getAsReal(), num2->getAsReal())));
        if (num1->getType() == Value::BYTE && num2->getType() == Value::BYTE)
            return Reference(std::make_shared<Value>(op(num1->getAsByte(), num2->getAsByte())));
        if (num1->getType() == Value::SHORT && num2->getType() == Value::SHORT)
            return Reference(std::make_shared<Value>(op(num1->getAsShort(), num2->getAsShort())));
        if (num1->getType() == Value::INT && num2->getType() == Value::INT)
            return Reference(std::make_shared<Value>(op(num1->getAsInt(), num2->getAsInt())));
        if (num1->getType() == Value::LONG && num2->getType() == Value::LONG)
            return Reference(std::make_shared<Value>(op(num1->getAsLong(), num2->getAsLong())));
        throw "Invalid Value Type for Calc";
    }
    template<typename Func> Reference __int_calc_helper(Reference num1, Func op) {
        if (num1->getType() == Value::BYTE)
            return Reference(std::make_shared<Value>(op(num1->getAsByte())));
        if (num1->getType() == Value::SHORT)
            return Reference(std::make_shared<Value>(op(num1->getAsShort())));
        if (num1->getType() == Value::INT)
            return Reference(std::make_shared<Value>(op(num1->getAsInt())));
        if (num1->getType() == Value::LONG)
            return Reference(std::make_shared<Value>(op(num1->getAsLong())));
        throw "Invalid Value Type for Calc";
    }
    template<typename Func> Reference __int_calc_helper(Reference num1, Reference num2, Func op) {
        if (num1->getType() == Value::BYTE && num2->getType() == Value::BYTE)
            return Reference(std::make_shared<Value>(op(num1->getAsByte(), num2->getAsByte())));
        if (num1->getType() == Value::SHORT && num2->getType() == Value::SHORT)
            return Reference(std::make_shared<Value>(op(num1->getAsShort(), num2->getAsShort())));
        if (num1->getType() == Value::INT && num2->getType() == Value::INT)
            return Reference(std::make_shared<Value>(op(num1->getAsInt(), num2->getAsInt())));
        if (num1->getType() == Value::LONG && num2->getType() == Value::LONG)
            return Reference(std::make_shared<Value>(op(num1->getAsLong(), num2->getAsLong())));
        throw "Invalid Value Type for Calc";
    }
    r_long __getValueAsLong(Reference num1) {
        if (num1->getType() == Value::REAL)
            return num1->getAsReal();
        if (num1->getType() == Value::BYTE)
            return num1->getAsByte();
        if (num1->getType() == Value::SHORT)
            return num1->getAsShort();
        if (num1->getType() == Value::INT)
            return num1->getAsInt();
        if (num1->getType() == Value::LONG)
            return num1->getAsLong();
        throw "Invalid Value Type for Calc";
    }
    void _add(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a + b;}));
    }
    void _sub(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a - b;}));
    }
    void _mul(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a * b;}));
    }
    void _div(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a / b;}));
    }
    void _mod(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a % b;}));
    }
    void _shr(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a >> b;}));
    }
    void _shl(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a << b;}));
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
        auto r_m = env->getContext().currentClass.findMethod(env, methodName);
        auto method = r_m.second;
        env->setClass(r_m.first);
        env->setMethod(method);
        if (checkNative(method, env->getContext().currentClass)) {
            MethodInfo info = findMethod("RdkNative", package.c_str(), methodName.c_str());
            if (info.method) {
                callMethod(env, methodName, info.method);
            }
            _ret(env, ins);
            return;
        }
        env->getExecuter().jmp(method.attributes.start);
    }
    void _sml(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a < b;}));
    }
    void _big(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a > b;}));
    }
    void _equ(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a == b;}));
    }
    void _seq(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a <= b;}));
    }
    void _beq(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, num2, [](auto a, auto b){return a >= b;}));
    }
    void _not(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, [](auto a){return !a;}));
    }
    void _neg(Environment* env, Instruction ins) {
        Reference num1 = env->popValue();

        env->pushValue(__calc_helper(num1, [](auto a){return -a;}));
    }
    void _and(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a & b;}));
    }
    void _or(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a | b;}));
    }
    void _xor(Environment* env, Instruction ins) {
        Reference num2 = env->popValue();
        Reference num1 = env->popValue();

        env->pushValue(__int_calc_helper(num1, num2, [](auto a, auto b){return a ^ b;}));
    }
    void _jmp(Environment* env, Instruction ins) {
        env->getExecuter().jmp(ins.op);
    }
    void _jt(Environment* env, Instruction ins) {
        Reference ref = env->popValue();
        if (__getValueAsLong(ref))
            _jmp(env, ins);
    }
    void _jf(Environment* env, Instruction ins) {
        Reference ref = env->popValue();
        if (! __getValueAsLong(ref))
            _jmp(env, ins);
    }
    void _ret(Environment* env, Instruction ins) {
        if (env->getContext().methodStack.empty()) {
            env->getExecuter().end();
            return;
        }
        auto info = env->getContext().methodStack.top();
        env->getContext().methodStack.pop();
        env->setClass(info.first.first);
        env->setMethod(info.first.second);
        env->getExecuter().jmp(info.second);
        env->getContext().variablePool = env->getContext().vpStack.top();
        env->getContext().vpStack.pop();
    }

    void _lfd(Environment* env, Instruction ins) {
        auto obj = env->popValue();
        auto name = env->popValue();
        RainReference& fd = obj->getAsObject().getValue(name->getAsString());
        env->getContext().variablePool[ins.op] = Reference(fd);
    }

    void _lst(Environment* env, Instruction ins) {
        auto name = env->popValue()->getAsString();
        auto clazz = name.substr(0, name.find_last_of('.'));
        auto var_name = name.substr(name.find_last_of('.') + 1);
        env->loadStatic(clazz);
        env->getContext().variablePool[ins.op] = env->getContext().staticPool[clazz][var_name];
    }

    void _pfd(Environment* env, Instruction ins) {
        auto obj = env->popValue();
        auto name = env->getContext().currentClass.const_pool[ins.op];
        RainReference& fd = obj->getAsObject().getValue(name);
        env->pushValue(Reference(fd));
    }

    void _pst(Environment* env, Instruction ins) {
        auto name = env->getContext().currentClass.const_pool[ins.op];
        auto clazz = name.substr(0, name.find_last_of('.'));
        auto var_name = name.substr(name.find_last_of('.') + 1);
        env->loadStatic(clazz);
        env->pushValue(env->getContext().staticPool[clazz][var_name]);
    }

    template<typename Func> void __arr_helper(Reference num1, Func op) {
        if (num1->getType() == Value::REAL)
            op(num1->getAsRealArr());
        if (num1->getType() == Value::BYTE)
            op(num1->getAsByteArr());
        if (num1->getType() == Value::SHORT)
            op(num1->getAsShortArr());
        if (num1->getType() == Value::INT)
            op(num1->getAsIntArr());
        if (num1->getType() == Value::LONG)
            op(num1->getAsLongArr());
        if (num1->getType() == Value::STRING)
            op(num1->getAsStringArr());
        if (num1->getType() == Value::OBJECT)
            op(num1->getAsObjectArr());
        throw "Invalid Value Type";
    }

    template<typename Func> void __normal_arr_helper(Reference num1, Func op) {
        if (num1->getType() == Value::REAL)
            op(num1->getAsRealArr());
        if (num1->getType() == Value::BYTE)
            op(num1->getAsByteArr());
        if (num1->getType() == Value::SHORT)
            op(num1->getAsShortArr());
        if (num1->getType() == Value::INT)
            op(num1->getAsIntArr());
        if (num1->getType() == Value::LONG)
            op(num1->getAsLongArr());
        if (num1->getType() == Value::STRING)
            op(num1->getAsStringArr());
        throw "Invalid Value Type";
    }

    void _par(Environment* env, Instruction ins) {
        auto arr = env->popValue();
        int no = 0;
        TyperValue tv = getByTyper(env, ins.typer, ins.op);
        if (tv.isValue)
            no = tv.value;
        if (tv.isCon)
            no = atoi(tv.con.c_str());
        if (tv.isRef)
            no = tv.ref->getAsLong();
        if (arr->getType() != RainValue::ARRAY)
            __arr_helper(arr, [no, env](auto arr){env->pushValue(Reference(std::make_shared<Value>(arr[no])));});
        else
            env->pushValue(Reference(arr->getAsArrArr()+no));
    }

    void _ptar(Environment* env, Instruction ins) {
        auto arr = env->popValue();
        int no = 0;
        TyperValue tv = getByTyper(env, ins.typer, ins.op);
        if (tv.isValue)
            no = tv.value;
        if (tv.isCon)
            no = atoi(tv.con.c_str());
        if (tv.isRef)
            no = tv.ref->getAsLong();
        __normal_arr_helper(arr, [no, env](auto arr){
            __calc_helper(env->popValue(), [&arr, no](auto num){
                arr[no]=num;
                return 0;});
            }
        );
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
        ins_map[0x19] = _lfd;
        ins_map[0x1A] = _lst;
        ins_map[0x1B] = _pfd;
        ins_map[0x1C] = _pst;
        ins_map[0x1D] = _par;
        ins_map[0x1E] = _ptar;
        ins_map[0xFF] = __test_printer;
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
        name_map[_lfd] = "lfd";
        name_map[_lst] = "lst";
        name_map[_pfd] = "pfd";
        name_map[_pst] = "pst";
        name_map[_par] = "par";
        name_map[_ptar] = "ptar";
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
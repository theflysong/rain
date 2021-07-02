#include "executer.h"
#include "../utils/stringhelper.h"
#include "../utils/bytehelper.h"
#include <iostream>

namespace Runtime {
    std::pair<std::pair<RainClass, Method>, int> makeMethodInfo(RainClass clazz, Method method, int ins) {
        return std::make_pair(std::make_pair(clazz, method), ins);
    }

    void Environment::pushValue(Reference ref) {
        this->context.runtimeStack.push(ref);
    }

    Reference Environment::popValue() {
        Reference ref = this->context.runtimeStack.top();
        this->context.runtimeStack.pop();
        return ref;
    }

    void Environment::setClass(std::string package) {
        FileByteReader reader((workDir + p2cp(package) + ".rc"));
        setClass(ClassCreator::createClass(reader), package);
    }

    void Environment::setClass(RainClass clazz, std::string package) {
        clazz.package = package;
        this->context.currentClass = clazz;
    }


    void Environment::setMethod(std::string methodName) {
        setMethod(context.currentClass.method_pool[methodName]);
    }

    void Environment::setMethod(Method method) {
        context.currentMethod = method;
    }

    Context& Environment::getContext() {
        return this->context;
    }

    Executer& Environment::getExecuter() {
        return this->executer;
    }

    Environment::Environment(std::string workDirIn) : workDir(workDirIn), executer(context) {
    }

    Executer::Executer(Context &contextIn) : context(contextIn) {
    }

    void Executer::step(Environment *env) {
        ins[pi].handle(env, ins[pi ++]);
    }

    void Executer::run(Environment *env) {
        pi = env->getContext().currentMethod.attributes.start;
        while (ins.size() > pi)
            step(env);
    }

    void Executer::pushPi() {
        context.methodStack.push(makeMethodInfo(context.currentClass, context.currentMethod, pi));
    }

    void Executer::init() {
        __ins_init();
        ins = __generateIns(context.currentClass.codes.first.get(), context.currentClass.codes.second);
        pi = 0;
    }

    void Executer::jmp(int pi) {
        this->pi = pi;
    }

    void Executer::end() {
        jmp(ins.size());
    }

    std::vector<Instruction> Executer::getInstructions() {
        return ins;
    }

    inline int getOpLen(byte typer) {
        switch (typer) {
        case 0:
            return 0;
        case 5:
            return 1;
        case 6:
            return 2;
        case 1:
        case 3:
        case 7:
            return 4;
        default:
            return 8;
        }
    }

    std::vector<Instruction> Executer::__generateIns(byte* ins, int insLen) {
        std::vector<Instruction> insList;
        for (int i = 0 ; i < insLen ;) {
            byte opCode = ins[i ++];
            byte typer = ins[i ++];
            int oplen = getOpLen(typer);
            if (oplen == 0) {
                insList.push_back({ins_map[opCode], 0, 0});
                continue;
            }
            byte *b_op = new byte[oplen];
            for (int j = 0 ; j < oplen ; j ++, i ++) {
                b_op[j] = ins[i];
            }
            r_long op;
            switch (oplen) {
                case 1:
                    op = b_op[0];
                    break;
                case 2:
                    op = asShort(b_op);
                    break;
                case 4:
                    op = asInt(b_op);
                    break;
                case 8:
                    op = asLong(b_op);
                    break;
            }
            delete[] b_op;
            insList.push_back({ins_map[opCode], typer, op});
        }
        return insList;
    }

    std::string p2cp(std::string package) {
        return replaceAll(package, ".", "/");
    }
}
#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/stringhelper.h"
#include <iostream>
#include <cstring>
#include "./utils/rni_util.h"
#include "./utils/infohelper.h"

int main(int argc, char** argv) {
    Runtime::Environment env("./");
    /*Runtime::RainClass clazz;
    clazz.const_pool.push_back("rain.lang.Object.finalize(V;)V");
    Runtime::__ins_init();
    Runtime::Instruction ins{Runtime::ins_map[0x0A], 0, 0};
    env.setClass(clazz, "rain.lang.Object");
    ins.handle(&env, ins);*/
    //env.setClass("test1");
    //Runtime::RainClass& clazz = env.getContext().currentClass;
    //env.getExecuter().init();
    //printClassInfo(clazz);
    //printInstructions(env.getExecuter().getInstructions());
    //env.setMethod("main([S)V#static");
    //env.getExecuter().run(&env);
    return 0;
}
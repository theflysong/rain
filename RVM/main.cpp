#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/stringhelper.h"
#include <iostream>
#include <cstring>
#include "./utils/rni_util.h"
#include "./utils/infohelper.h"

int main(int argc, char** argv) {
    Runtime::Environment env("./");
    //env.setClass("test1");
    //Runtime::RainClass& clazz = env.getContext().currentClass;
    //env.getExecuter().init();
    //printClassInfo(clazz);
    //printInstructions(env.getExecuter().getInstructions());
    //env.setMethod("main([s)V#static");
    //env.getExecuter().run(&env);
    env.pushValue(Runtime::Reference(std::make_shared<Runtime::Value>("YESSSSS")));
    auto mi = findMethod("RdkNative", "rain.lang.System", "println(s)V#static");
    callMethod(&env, "println(s)V#static", mi.method);
    return 0;
}
#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/stringhelper.h"
#include <iostream>
#include <cstring>
#include "./utils/rni_util.h"
#include "./utils/infohelper.h"

int main(int argc, char** argv) {
    auto args = Runtime::Reference(std::make_shared<Runtime::Value>("", false, true, argc - 1));
    for (int i = 1 ; i < argc ; i ++) {
        args->getAsStringArr()[i - 1] = "";
        args->getAsStringArr()[i - 1] += argv[i];
    }
    Runtime::Environment env("./");
    env.setClass("test1");
    Runtime::RainClass& clazz = env.getContext().currentClass;
    env.getExecuter().init();
    printClassInfo(clazz);
    printInstructions(env.getExecuter().getInstructions());
    // env.pushValue(args);
    // env.setMethod("main([s)V#static");
    // env.getContext().variablePool[1] = Runtime::Reference(std::make_shared<Runtime::Value>(2));
    // env.getExecuter().debug(&env);
    // env.pushValue(Runtime::Reference(std::make_shared<Runtime::Value>("YESSSSS")));
    // auto mi = findMethod("RdkNative", "rain.lang.System", "println(s)V#static");
    // callMethod(&env, "println(s)V#static", mi.method);
    return 0;
}
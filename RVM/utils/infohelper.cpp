#include "infohelper.h"
#include "stringhelper.h"
#include <iostream>

void printClassInfo(Runtime::RainClass clazz) {
    std::cout << "Class:" << clazz.package << std::endl;
    std::cout << "accese:" << acceseToString(clazz.attributes.accese) << std::endl;
    std::cout << "is_member:" << toString((bool)clazz.attributes.is_member) << std::endl;
    std::cout << "parents:";
    for (auto p : clazz.parents)
        std::cout << p << " ";
    std::cout << std::endl;
    std::cout << "attributes:";
    for (auto a : clazz.attach_attr)
        std::cout << a << " ";
    std::cout << std::endl;
    printConstPool(clazz.const_pool);
    for (auto f : clazz.feild_pool)
        printFieldInfo(f.second, clazz);
    for (auto m : clazz.method_pool)
        printMethodInfo(m.second, clazz);
}
void printMethodInfo(Runtime::Method method, Runtime::RainClass clazz) {
    std::cout << "-------" << std::endl;
    std::cout << "Method: " << method.name << std::endl;
    std::cout << "accese:" << acceseToString(method.attributes.accese) << std::endl;
    std::cout << "final:" << toString((bool)method.attributes.is_final) << std::endl;
    std::cout << "static:" << toString((bool)method.attributes.is_static) << std::endl;
    std::cout << "start:" << method.attributes.start << std::endl;
    std::cout << "attributes:";
    for (auto a : clazz.sub_attach_attr[method.name])
        std::cout << a << " ";
    std::cout << std::endl;
}
void printFieldInfo(Runtime::Field field, Runtime::RainClass clazz) {
    std::cout << "-------" << std::endl;
    std::cout << "Field: " << field.name << std::endl;
    std::cout << "accese:" << acceseToString(field.attributes.accese) << std::endl;
    std::cout << "const:" << toString((bool)field.attributes.is_const) << std::endl;
    std::cout << "static:" << toString((bool)field.attributes.is_static) << std::endl;
    for (auto a : clazz.sub_attach_attr[field.name])
        std::cout << a << " ";
    std::cout << std::endl;
}
void printConstPool(std::vector<std::string> const_pool) {
    std::cout << "-------" << std::endl;
    std::cout << "Const Pool:" << std::endl;
    for (auto s : const_pool)
        std::cout << s << std::endl;
}
void printInstructions(std::vector<Runtime::Instruction> ins) {
    std::cout << "-------" << std::endl;
    std::cout << "Instructions:" << std::endl;
    for (auto i : ins) {
        std::cout << Runtime::name_map[i.handle] << " " << typerToString(i.typer);
        if (i.typer)
            std::cout << i.op;
        std::cout << std::endl;
    }
}

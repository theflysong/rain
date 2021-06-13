#include "./reader/reader.h"
#include "./executer/executer.h"
#include "./utils/tostringhelper.h"
#include <iostream>

int main(int argc, char** argv) {
    Executer executer;
    //FileByteReader reader(argv[1]);
    /*RainClass rclass = ClassCreator::createClass(reader);
    for (std::string con : rclass.const_pool) {
        std::cout << con << " ";
    }
    RainClass::Attributes attr = rclass.attributes;
    std::cout << std::endl << acceseToString(attr.accese);
    std::cout << std::endl << toString(attr.is_member);
    std::cout << std::endl << (int)attr.parent_num;
    for (short pa : attr.parents) {
        std::cout << rclass.const_pool[pa] << " ";
    }*/
    __ins_init();
    executer.pushValue(Reference(std::make_shared<Value>(2)));
    executer.pushValue(Reference(std::make_shared<Value>(7)));

    ins_map[0x07](&executer, Instruction());

    std::cout << executer.popValue().getValue()->getAsNumber() << std::endl;
    return 0;
}
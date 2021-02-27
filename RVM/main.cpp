#include "./reader/reader.h"
#include "./executer/executer.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string name;
    std::cin >> name;
    FileByteReader reader(name);
    RainClass rclass = ClassCreator::createClass(reader);
    for (std::string con : rclass.const_pool) {
        std::cout << con;
    }
    return 0;
}
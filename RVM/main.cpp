#include "./reader/reader.h"
#include <iostream>

int main(int argc, char** argv) {
    std::string name;
    std::cin >> name;
    FileByteReader reader(name);
    while (! isEOR(reader.peek())) {
        std::cout << reader.peek();
        reader.next();
    }
    return 0;
}
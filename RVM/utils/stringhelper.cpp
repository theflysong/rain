#include "stringhelper.h"

std::string acceseToString(byte accese) {
    switch(accese) {
    case 0:
        return "public";
    case 1:
        return "friendly";
    case 2:
        return "protected";
    case 3:
        return "private";
    }
    return "unknow";
}

std::string toString(bool flag) {
    return flag ? "true" : "false";
}

std::string replaceAll(std::string source, std::string from, std::string to) {
    register int pos = source.find(from);
    while (pos != std::string::npos) {
        source.replace(pos, pos + from.length(), to);
        pos = source.find(from);
    }
    return source;
}
#include "tostringhelper.h"

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
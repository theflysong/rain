#ifndef __CLASS_INFO__
#define __CLASS_INFO__

#include <vector>
#include "./const/defs.h"

struct Field {
    std::string name;
    std::string access;
    bool is_const;
    bool is_static;
    std::vector<std::string> attributes;
};

struct Method {
    std::string name;
    std::string access;
    bool is_final;
    bool is_static;
    std::vector<std::string> attributes;
};

struct RainClass {
    std::string access;
    bool is_member;
    std::vector<std::string> parents;
    std::vector<std::string> attributes;

    std::vector<std::string> const_pool;
    std::vector<Field> fields;
    std::vector<Method> methods;
    std::vector<std::string> memberClasses;
};

#endif
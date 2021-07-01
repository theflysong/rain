#ifndef __METHOD_HEADER__
#define __METHOD_HEADER__

#include "../const/defs.h"
#include <string>

namespace Runtime {
    struct Method {
        struct Attributes {
            unsigned char accese : 2;
            bool is_final : 1;
            bool is_static : 1;
            unsigned : 4;
            r_int start;
        };
        Attributes attributes;
        std::string name;
    };
}


#endif
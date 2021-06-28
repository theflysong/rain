#ifndef __FIELD_HEADER__
#define __FIELD_HEADER__

#include "../const/defs.h"

namespace Runtime {
    struct Field {
        struct Attributes {
            unsigned char accese : 2;
            bool is_const : 1;
            bool is_static : 1;
            unsigned : 4;
        };
        Attributes attributes;
    };
}

#endif
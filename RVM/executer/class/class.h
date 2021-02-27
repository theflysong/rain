#ifndef __CLASS_HEADER__
#define __CLASS_HEADER__

#include "../../const/defs.h"
#include "../../reader/reader.h"
#include <string>
#include <vector>

class RainClass {
public:
    std::vector<std::string> const_pool;
};

namespace ClassCreator {
    RainClass createClass(IByteReader& rclass);
}

#endif
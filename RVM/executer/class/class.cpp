#include "./class.h"

namespace ClassCreator {
    RainClass createClass(IByteReader& rclass) {
        RainClass rc;
        short num = rclass.getAsShort();
        for (short i = 0 ; i < num ; i ++) {
            short bnum = rclass.getAsShort();
            byte* rcon = new byte[bnum];
            std::string str = rclass.gets(rcon, bnum);
            delete rcon;
            rc.const_pool.push_back(str);
        }
        return rc;
    }
}
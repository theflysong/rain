#include "./class.h"
#include <iostream>

namespace ClassCreator {
    RainClass createClass(IByteReader& rclass) {
        RainClass rc;
        short num = rclass.getAsShort();
        for (short i = 0 ; i < num ; i ++) {
            rc.const_pool.push_back(createEntry(rclass));
        }
        rc.attributes = loadAtrribute(rclass);
        return rc;
    }

    std::string createEntry(IByteReader& rclass) {
        short num = rclass.getAsShort();
        byte* b_entry = new byte[num];
        std::string entry = rclass.gets(b_entry, num);
        delete b_entry;
        return entry;
    }

    RainClass::Attributes loadAtrribute(IByteReader& rclass) {
        RainClass::Attributes attr;
        byte attribute = rclass.next();
        attr.accese = attribute & 3; // attribute & 00000011
        attr.is_member = (attribute >> 2) & 1; // (attribute >> 2) & 000001
        attr.parent_num = (attribute >> 3) & 31; // (attribute >> 3) & 11111
        for (int i = 0 ; i < attr.parent_num ; i ++) {
            attr.parents.push_back(rclass.getAsShort());
        }
        return attr;
    }

    //std::pair<std::string, Field> createField(IByteReader& rclass);
    //std::pair<std::string, Method> createMethod(IByteReader& rclass);
    //std::vector<std::string> createMemberClasses(IByteReader& rclass);
}
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

    std::pair<short, Field> createField(IByteReader& rclass) {
        Field::Attributes attr;
        byte attribute = rclass.next();
        attr.accese = attribute & 3;
        attr.is_static = (attribute >> 2) & 1;
        attr.is_const = (attribute >> 3) & 1;
        return std::make_pair(rclass.getAsShort(), Field{attr});
    }

    std::pair<short, Method> createMethod(IByteReader& rclass) {
        Method::Attributes attr;
        byte attribute = rclass.next();
        attr.accese = attribute & 3;
        attr.is_static = (attribute >> 2) & 1;
        attr.is_final = (attribute >> 3) & 1;
        short name = rclass.getAsShort();
        attr.start = rclass.getAsInt();
        return std::make_pair(name, Method{attr});
    }

    std::vector<short> createMemberClasses(IByteReader& rclass) {
        short num = rclass.getAsShort();
        std::vector<short> classes;
        for (int i = 0 ; i < num ; i ++) {
            classes.push_back(rclass.getAsShort());
        }
        return classes;
    }
    
    //std::vector<int> loadAttachAttribue(IByteReader& rclass);
    //std::vector<int> loadSubAttachAttribue(IByteReader& rclass);
    //std::vector<byte> loadCodes(IByteReader& rclass);
}
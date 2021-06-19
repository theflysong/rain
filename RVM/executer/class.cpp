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
        std::vector<int> _attach_attr = loadAttachAttribue(rclass);
        for (int _attr : _attach_attr) {
            rc.attach_attr.push_back(rc.const_pool[_attr]);
        }

        short fields_num = rclass.getAsShort();
        for (int i = 0 ; i < fields_num ; i ++) {
            auto e = createField(rclass);
            rc.feild_pool[rc.const_pool[e.first]] = e.second;
        }

        short method_num = rclass.getAsShort();
        for (int i = 0 ; i < method_num ; i ++) {
            auto e = createMethod(rclass);
            rc.method_pool[rc.const_pool[e.first]] = e.second;
        }

        std::vector<short> memberClasses = createMemberClasses(rclass);
        for (short mc : memberClasses) {
            rc.member_classes.push_back(rc.const_pool[mc]);
        }

        rc.codes = loadCodes(rclass);

        std::map<short, std::vector<int>> _subattach_attr = loadSubAttachAttribue(rclass);
        for (auto e : _subattach_attr) {
            for (int _attr : e.second) {
                rc.sub_attach_attr[rc.const_pool[e.first]].push_back(rc.const_pool[_attr]);
            }
        }
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

    std::vector<int> loadAttachAttribue(IByteReader& rclass) {
        byte num = rclass.next();
        std::vector<int> attrs;
        for (int i = 0 ; i < num ; i ++) {
            attrs.push_back(rclass.getAsInt());
        }
        return attrs;
    }

    std::map<short, std::vector<int>> loadSubAttachAttribue(IByteReader& rclass) {
        short num = rclass.getAsShort();
        std::map<short, std::vector<int>> attr_map;
        for (int i = 0 ; i < num ; i ++) {
            short name = rclass.getAsShort();
            byte attr_num = rclass.next();

            std::vector<int> attrs;
            for (int i = 0 ; i < num ; i ++) {
                attrs.push_back(rclass.getAsInt());
            }
            attr_map[name] = attrs;
        }
        return attr_map;
    }

    std::unique_ptr<byte[]> loadCodes(IByteReader& rclass) {
        int length = rclass.getAsInt();
        std::unique_ptr<byte[]> ptr(new byte[length]);
        rclass.gets(ptr.get(), length);
        return ptr;
    }
}
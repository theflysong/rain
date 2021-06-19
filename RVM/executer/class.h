#ifndef __CLASS_HEADER__
#define __CLASS_HEADER__

#include "../reader/reader.h"
#include <vector>
#include <map>

#include "field.h"
#include "method.h"
#include "instruction.h"

class RainClass {
public:
    struct Attributes {
        unsigned char accese : 2;
        bool is_member : 1;
        unsigned char parent_num : 2;
        std::vector<short> parents;
    };
    Attributes attributes;
    std::vector<std::string> attach_attr;
    std::vector<std::string> const_pool;
    std::map<std::string, Field> feild_pool;
    std::map<std::string, Method> method_pool;
    std::vector<std::string> member_classes;
    std::map<std::string, std::vector<std::string>> sub_attach_attr;
    std::vector<byte> codes;
};

namespace ClassCreator {
    RainClass createClass(IByteReader& rclass);
    std::string createEntry(IByteReader& rclass);
    RainClass::Attributes loadAtrribute(IByteReader& rclass);
    std::pair<short, Field> createField(IByteReader& rclass);
    std::pair<short, Method> createMethod(IByteReader& rclass);
    std::vector<short> createMemberClasses(IByteReader& rclass);
    std::vector<int> loadAttachAttribue(IByteReader& rclass);
    std::vector<int> loadSubAttachAttribue(IByteReader& rclass);
    std::vector<byte> loadCodes(IByteReader& rclass);
}

#endif
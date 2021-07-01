#ifndef __CLASS_HEADER__
#define __CLASS_HEADER__

#include "../reader/reader.h"
#include <vector>
#include <map>
#include <memory>

#include "field.h"
#include "method.h"
#include "instruction.h"
namespace Runtime {
    class RainClass {
    public:
        struct Attributes {
            unsigned char accese : 2;
            bool is_member : 1;
        };
        Attributes attributes;
        std::vector<std::string> parents;
        std::vector<std::string> attach_attr;
        std::vector<std::string> const_pool;
        std::map<std::string, Field> feild_pool;
        std::map<std::string, Method> method_pool;
        std::vector<std::string> member_classes;
        std::map<std::string, std::vector<std::string>> sub_attach_attr;
        std::pair<std::shared_ptr<byte[]>, int> codes;
        std::string package;
    };

    namespace ClassCreator {
        RainClass createClass(IByteReader& rclass);
        std::string createEntry(IByteReader& rclass);
        void loadAtrribute(IByteReader& rclass, RainClass& clazz);
        std::pair<r_short, Field> createField(IByteReader& rclass);
        std::pair<r_short, Method> createMethod(IByteReader& rclass);
        std::vector<r_short> createMemberClasses(IByteReader& rclass);
        std::vector<r_int> loadAttachAttribue(IByteReader& rclass);
        std::map<r_short, std::vector<r_int>> loadSubAttachAttribue(IByteReader& rclass);
        std::pair<std::shared_ptr<byte[]>, int> loadCodes(IByteReader& rclass);
    }
}

#endif
#ifndef __VALUE_HEADER__
#define __VALUE_HEADER__

#include "../const/defs.h"
#include <rni.h>
#include <map>

namespace Runtime {
    class Reference;
    class Object : public RainObject {
        std::map<std::string, Reference> values;
        std::string class_type;
    public:
        Object();
        Object(RainObject* obj);
        Object(RainObject& obj);
        std::map<std::string, RainReference*> getValues() override;
        RainReference& getValue(std::string name) override;
        std::string getClassType() override;
    };

    class Value : public RainValue {
    private:
        Type type;
        bool iconst;
        bool iarr;
        int arrlen;
        union {
            r_byte* pByte;
            r_short* pShort;
            r_int* pInt;
            r_long* pLong;
            r_real* pReal;
            std::string* pStr;
            RainObject* pObj;
            RainReference* pArr;
            void* pointer;
        };
    public:
        Value();
        Value(r_byte value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(r_short value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(r_int value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(r_long value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(r_real value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(std::string value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(RainObject& value, bool is_const = false, bool is_arr = false, int arrLen = 0);
        Value(RainReference* value, int arrLen, bool is_const = false);
        ~Value();
        Type getType() override;
        void setType(Type type) override;
        void* getPointer() override;
        r_byte& getAsByte() override;
        r_short& getAsShort() override;
        r_int& getAsInt() override;
        r_long& getAsLong() override;
        r_real& getAsReal() override;
        RainObject& getAsObject() override;
        std::string& getAsString() override;
        RainReference& getAsArr() override;
        r_byte* getAsByteArr() override;
        r_short* getAsShortArr() override;
        r_int* getAsIntArr() override;
        r_long* getAsLongArr() override;
        r_real* getAsRealArr() override;
        RainObject* getAsObjectArr() override;
        std::string* getAsStringArr() override;
        RainReference* getAsArrArr() override;
        void set(r_byte value) override;
        void set(r_short value) override;
        void set(r_int value) override;
        void set(r_long value) override;
        void set(r_real value) override;
        void set(std::string value) override;
        void set(RainObject& value) override;
        void set(RainReference& value) override;
        bool isConst() override;
        bool isArray() override;
        int getArrLen() override;
    };

    class Reference : public RainReference{
        std::shared_ptr<RainValue> ptr;
    public:
        Reference();
        Reference(RainReference& ref);
        Reference(RainReference* ref);
        Reference(std::shared_ptr<Value> _ptr);
        Reference(std::shared_ptr<RainValue> _ptr);
        std::shared_ptr<RainValue> getValue() override;
        Reference copy();
        std::shared_ptr<RainValue> operator->() override;
        bool operator==(RainReference& ref) override;
        bool operator!=(RainReference& ref) override;
    };
}

#endif
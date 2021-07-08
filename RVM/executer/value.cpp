#include "value.h"

namespace Runtime {
    Object::Object() {

    }

    Object::Object(Object* obj) {
        this->values = obj->values;
        this->class_type = obj->class_type;
    }

    Object::Object(Object& obj) {
        this->values = obj.values;
        this->class_type = obj.class_type;
    }


    RainReference& Object::getValue(std::string name) {
        return this->values[name];
    }

    std::string Object::getClassType() {
        return this->class_type;
    }

    Value::Type Value::getType() {
        return this->type;
    }

    void Value::setType(Type type) {
        this->type = type;
    }

    void* Value::getPointer() {
        return this->pointer;
    }

    r_byte& Value::getAsByte() {
        return *pByte;
    }

    r_short& Value::getAsShort() {
        return *pShort;
    }

    r_int& Value::getAsInt() {
        return *pInt;
    }

    r_long& Value::getAsLong() {
        return *pLong;
    }

    r_real& Value::getAsReal() {
        return *pReal;
    }

    std::string& Value::getAsString() {
        return *pStr;
    }

    RainReference& Value::getAsArr() {
        return *pArr;
    }

    RainObject& Value::getAsObject() {
        return *pObj;
    }

    r_byte* Value::getAsByteArr() {
        return pByte;
    }

    r_short* Value::getAsShortArr() {
        return pShort;
    }

    r_int* Value::getAsIntArr() {
        return pInt;
    }

    r_long* Value::getAsLongArr() {
        return pLong;
    }

    r_real* Value::getAsRealArr() {
        return pReal;
    }

    RainObject* Value::getAsObjectArr() {
        return pObj;
    }

    RainReference* Value::getAsArrArr() {
        return pArr;
    }

    std::string* Value::getAsStringArr() {
        return pStr;
    }

    int Value::getArrLen() {
        return arrlen;
    }

    void Value::set(r_byte value) {
        if (this->type != BYTE) {
            if (pointer != NULL)
                delete pByte;
            pByte = new r_byte;
        }
        *pByte = value;
    }

    void Value::set(r_short value) {
        if (this->type != SHORT) {
            if (pointer != NULL)
                delete pShort;
            pShort = new r_short;
        }
        *pShort = value;
    }

    void Value::set(r_int value) {
        if (this->type != INT) {
            if (pointer != NULL)
                delete pInt;
            pInt = new r_int;
        }
        *pInt = value;
    }

    void Value::set(r_long value) {
        if (this->type != LONG) {
            if (pointer != NULL)
                delete pLong;
            pLong = new r_long;
        }
        *pLong = value;
    }

    void Value::set(r_real value) {
        if (this->type != REAL) {
            if (pointer != NULL)
                delete pReal;
            pReal = new r_real;
        }
        *pReal = value;
    }

    void Value::set(std::string value) {
        if (this->type != STRING) {
            if (pointer != NULL)
                delete pStr;
            pStr = new std::string;
        }
        *pStr = value;
    }

    void Value::set(RainObject& value) {
        if (this->type != OBJECT) {
            if (pointer != NULL)
                delete pObj;
            pObj = new Object;
        }
        *pObj = value;
    }

    void Value::set(RainReference& value) {
        if (this->type != ARRAY) {
            if (pointer != NULL)
                delete pArr;
            pArr = new Reference;
        }
        *pArr = value;
    }

    Value::Value() {
        pointer = NULL;
    }

    Value::Value(r_byte value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pByte = new r_byte[arrLen];
        }
        else
            pByte = new r_byte(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = BYTE;
    }

    Value::Value(r_short value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pShort = new r_short[arrLen];
        }
        else
            pShort = new r_short(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = SHORT;
    }

    Value::Value(r_int value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pInt = new r_int[arrLen];
        }
        else
            pInt = new r_int(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = INT;
    }

    Value::Value(r_long value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pLong = new r_long[arrLen];
        }
        else
            pLong = new r_long(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = LONG;
    }

    Value::Value(r_real value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pReal = new r_real[arrLen];
        }
        else
            pReal = new r_real(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = REAL;
    }

    Value::Value(std::string value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pStr = new std::string[arrLen];
        }
        else
            pStr = new std::string(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = STRING;
    }

    Value::Value(Object value, bool is_const, bool is_arr, int arrLen) {
        if (is_arr) {
            arrlen = arrLen;
            pObj = new Object[arrLen];
        }
        else
            pObj = new Object(value);
        this->iconst = is_const;
        this->iarr = is_arr;
        this->type = OBJECT;
    }

    Value::Value(Reference value, int arrLen, bool is_const) {
        arrlen = arrLen;
        pArr = new Reference[arrLen];
        this->iconst = is_const;
        this->iarr = true;
        this->type = ARRAY;
    }

    Value::~Value() {
        if (pointer != NULL)
            if (iarr)
                delete (int*)pointer;
            else
                delete[] pointer;
    }

    bool Value::isConst() {
        return iconst;
    }

    bool Value::isArray() {
        return iarr;
    }

    Reference::Reference() {
    }

    Reference::Reference(std::shared_ptr<RainValue> _ptr) : ptr(_ptr){
    }

    Reference::Reference(std::shared_ptr<Value> _ptr) : ptr(_ptr){

    }

    std::shared_ptr<RainValue> Reference::getValue() {
        return ptr;
    }

    Reference Reference::copy() {
        return *this;
    }

    std::shared_ptr<RainValue> Reference::operator->() {
        return ptr;
    }

    bool Reference::operator==(RainReference& ref) {
        return ref.getValue() == this->getValue();
    }

    bool Reference::operator!=(RainReference& ref) {
        return ! (ref == *this);
    }
}
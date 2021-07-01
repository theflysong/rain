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

    Value::Type Value::getType() {
        return this->type;
    }

    void Value::setType(Type type) {
        this->type = type;
    }

    void* Value::getPointer() {
        return this->pointer;
    }

    r_real& Value::getAsNumber() {
        return *((r_real*)pointer);
    }

    std::string& Value::getAsString() {
        return *((std::string*)pointer);
    }

    Object& Value::getAsObject() {
        return *((Object*)pointer);
    }

    void Value::set(r_real value) {
        if (this->type != NUMBER) {
            delete (r_real*)pointer;
            pointer = (void*)new r_real;
        }
        *((r_real*)pointer) = value;
    }

    void Value::set(std::string value) {
        if (this->type != STRING) {
            delete (std::string*)pointer;
            pointer = (void*)new std::string;
        }
        *((std::string*)pointer) = value;
    }

    void Value::set(Object value) {
        if (this->type != OBJECT) {
            delete (Object*)pointer;
            pointer = (void*)new Object;
        }
        *((Object*)pointer) = value;
    }

    Value::Value() {
        pointer = NULL;
    }

    Value::Value(r_real value, bool is_const) {
        pointer = (void*)new r_real(value);
        this->iconst = is_const;
        this->type = NUMBER;
    }

    Value::Value(std::string value, bool is_const) {
        pointer = (void*)new std::string(value);
        this->iconst = is_const;
        this->type = STRING;
    }

    Value::Value(Object value, bool is_const) {
        pointer = (void*)new Object(value);
        this->iconst = is_const;
        this->type = OBJECT;
    }

    Value::~Value() {
        if (pointer != NULL)
            delete (int*)pointer;
    }

    Reference::Reference() {
    }

    Reference::Reference(std::shared_ptr<Value> _ptr) : ptr(_ptr){
    }

    std::shared_ptr<Value> Reference::getValue() {
        return ptr;
    }

    Reference Reference::copy() {
        return *this;
    }

    std::shared_ptr<Value> Reference::operator->() {
        return ptr;
    }
}
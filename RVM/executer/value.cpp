#include "value.h"

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

float& Value::getAsNumber() {
    return *((float*)pointer);
}

std::string& Value::getAsString() {
    return *((std::string*)pointer);
}

Object& Value::getAsObject() {
    return *((Object*)pointer);
}

void Value::set(float value) {
    if (this->type != NUMBER) {
        delete (float*)pointer;
        pointer = (void*)new float;
    }
    *((float*)pointer) = value;
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

Value::Value(float value, bool is_const) {
    pointer = (void*)new float(value);
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

Reference::Reference(std::shared_ptr<Value> _ptr) : ptr(_ptr){
}

std::shared_ptr<Value> Reference::getValue() {
    return ptr;
}

Reference Reference::copy() {
    return *this;
}
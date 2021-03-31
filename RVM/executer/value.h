#ifndef __VALUE_HEADER__
#define __VALUE_HEADER__

#include "../const/defs.h"
#include <string>
#include <memory>
#include <map>

struct Refence;

struct Object {
    std::map<std::string, Refence> values;
    std::string class_type;
    Object();
    Object(Object* obj);
    Object(Object& obj);
};

struct Value {
    enum Type {
        INTEGER,
        DECIMAL,
        STRING,
        OBJECT
    };
private:
    Type type;
    bool iconst;
    void* pointer;
public:
    Value();
    Value(int value, bool is_const = false);
    Value(float value, bool is_const = false);
    Value(std::string value, bool is_const = false);
    Value(Object value, bool is_const = false);
    ~Value();
    Type getType();
    void setType(Type type);
    void* getPointer();
    int& getAsInteger();
    float& getAsDecimal();
    Object& getAsObject();
    std::string& getAsString();
    void set(int value);
    void set(float value);
    void set(std::string value);
    void set(Object value);
};

struct Refence {
    std::shared_ptr<Value> ptr;
public:
    Refence(std::shared_ptr<Value> _ptr);
    std::shared_ptr<Value> getValue();
    Refence copy();
};

#endif
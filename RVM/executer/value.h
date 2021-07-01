#ifndef __VALUE_HEADER__
#define __VALUE_HEADER__

#include "../const/defs.h"
#include <string>
#include <memory>
#include <map>

namespace Runtime {
    struct Reference;
    struct Object {
        std::map<std::string, Reference> values;
        std::string class_type;
        Object();
        Object(Object* obj);
        Object(Object& obj);
    };

    struct Value {
        enum Type {
            NUMBER,
            STRING,
            OBJECT
        };
    private:
        Type type;
        bool iconst;
        void* pointer;
    public:
        Value();
        Value(r_real value, bool is_const = false);
        Value(std::string value, bool is_const = false);
        Value(Object value, bool is_const = false);
        ~Value();
        Type getType();
        void setType(Type type);
        void* getPointer();
        r_real& getAsNumber();
        Object& getAsObject();
        std::string& getAsString();
        void set(r_real value);
        void set(std::string value);
        void set(Object value);
    };

    struct Reference {
        std::shared_ptr<Value> ptr;
    public:
        Reference();
        Reference(std::shared_ptr<Value> _ptr);
        std::shared_ptr<Value> getValue();
        Reference copy();
        std::shared_ptr<Value> operator->();
    };
}

#endif
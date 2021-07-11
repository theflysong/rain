#ifndef __RNI_H__
#define __RNI_H__

#include <stdint.h>
#include <string>
#include <memory>
#include <map>

#include "types.h"


class RainObject;
class RainReference;

class RainValue {
public:
    enum Type {
        BYTE,
        SHORT,
        INT,
        LONG,
        REAL,
        STRING,
        OBJECT,
        ARRAY
    };
    virtual Type getType() = 0;
    virtual void setType(Type type) = 0;
    virtual void* getPointer() = 0;
    virtual r_byte& getAsByte() = 0;
    virtual r_short& getAsShort() = 0;
    virtual r_int& getAsInt() = 0;
    virtual r_long& getAsLong() = 0;
    virtual r_real& getAsReal() = 0;
    virtual RainObject& getAsObject() = 0;
    virtual std::string& getAsString() = 0;
    virtual RainReference& getAsArr() = 0;
    virtual r_byte* getAsByteArr() = 0;
    virtual r_short* getAsShortArr() = 0;
    virtual r_int* getAsIntArr() = 0;
    virtual r_long* getAsLongArr() = 0;
    virtual r_real* getAsRealArr() = 0;
    virtual RainObject* getAsObjectArr() = 0;
    virtual std::string* getAsStringArr() = 0;
    virtual RainReference* getAsArrArr() = 0;
    virtual void set(r_byte value) = 0;
    virtual void set(r_short value) = 0;
    virtual void set(r_int value) = 0;
    virtual void set(r_long value) = 0;
    virtual void set(r_real value) = 0;
    virtual void set(std::string value) = 0;
    virtual void set(RainObject& value) = 0;
    virtual void set(RainReference& value) = 0;
    virtual bool isConst() = 0;
    virtual bool isArray() = 0;
    virtual int getArrLen() = 0;
};

class RainUtil {
public:
    virtual std::shared_ptr<RainReference> make_value() = 0;
    virtual std::shared_ptr<RainReference> call_method(std::string method_path, RainReference* args, int argNum)  = 0;
    virtual RainReference& getNullReference() = 0;
    virtual RainReference* nxtArg(RainReference* args) = 0;
};

class RainObject {
public:
    virtual std::map<std::string, RainReference*> getValues() = 0;
    virtual RainReference& getValue(std::string name) = 0;
    virtual std::string getClassType() = 0;
};

class RainReference {
public:
    virtual std::shared_ptr<RainValue> operator->() = 0;
    virtual std::shared_ptr<RainValue> getValue() = 0;
    virtual bool operator==(RainReference& ref) = 0;
    virtual bool operator!=(RainReference& ref) = 0;
};

#include <map>
#include <string>

typedef std::shared_ptr<RainReference>(*MethodPointer)(RainUtil*, RainReference*, int);

struct MethodInfo {
    const char* name;
    MethodPointer method;
};

struct ClassInfo {
    const char* name;
    MethodInfo* method;
};

#define NULL_METHOD_INFO {"",(MethodPointer)0}
#define NULL_CLASS_INFO {"",(MethodInfo*)0}

typedef ClassInfo*(*GetInstFunc)();

#endif
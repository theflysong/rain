#include "info_gen.h"

std::string getStr(std::istream& in, char& last) {
    std::string str = "";
    char ch;
    if (in.peek() == '"') {
        in.get();
        while (true) {
            in.get(ch);
            if (ch == '"' || ch == '\n' || ch == '\r' || in.eof())
                break;
            str += ch;
        }
        str = str.substr(0, str.size());
        last = ch;
        if (str == "" || str == "\0")
            return "";
        return str;
    }
    while (true) {
        in.get(ch);
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || in.eof())
            break;
        str += ch;
    }
    last = ch;
    if (str == "" || str == "\0")
        return "";
    return str;
}

std::vector<std::string> getLineStr(std::istream& in) {
    std::vector<std::string> strs;
    char last;
    while (! in.eof()) {
        std::string str = getStr(in, last);
        if (str == "" || str == "\0") {
            if (last == '\n')
                break;
            continue;
        }
        strs.push_back(str);
        if (last == '\n')
            break;
    }
    return strs;
}

void _clazzGen(std::istream& in, RainClass& clazz) {
    std::vector<std::string> _clazz = getLineStr(in);
    bool f1 = false, f2 = false;
    int now = 0;
    for (; now < _clazz.size() - 1 ; now ++) {
        if (_clazz[now] == "from")
            break;
        if (_clazz[now] == "public" || _clazz[now] == "public" || _clazz[now] == "public") {
            if (f1)
                throw "don't write accese attribute twice";
            clazz.access = _clazz[now];
            f1 = true;
            continue;
        }
        else if (_clazz[now] == "member") {
            if (f2)
                throw "don't write member attribute twice";
            clazz.is_member = true;
            f2 = true;
            continue;
        }
        clazz.attributes.push_back(_clazz[now]);
    }
    for (; now < _clazz.size() - 1 ; now ++) {
        clazz.parents.push_back(_clazz[now]);
    }
}

void _fieldGen(std::vector<std::string> _field, RainClass& clazz) {
    Field field;
    bool f1 = false, f2 = false, f3 = false;
    int now = 1;
    for (; now < _field.size() - 1 ; now ++) {
        if (_field[now] == "from")
            break;
        if (_field[now] == "public" || _field[now] == "public" || _field[now] == "public") {
            if (f1)
                throw "don't write accese attribute twice";
            field.access = _field[now];
            f1 = true;
            continue;
        }
        else if (_field[now] == "const") {
            if (f2)
                throw "don't write const attribute twice";
            field.is_const = true;
            f2 = true;
            continue;
        }else if (_field[now] == "static") {
            if (f3)
                throw "don't write static attribute twice";
            field.is_static = true;
            f3 = true;
            continue;
        }
        field.attributes.push_back(_field[now]);
    }
    field.name = _field[_field.size() - 1];
    clazz.fields.push_back(field);
}

void _methodGen(std::vector<std::string> _method, RainClass& clazz) {
    Method method;
    bool f1 = false, f2 = false, f3 = false;
    int now = 1;
    for (; now < _method.size() - 1 ; now ++) {
        if (_method[now] == "from")
            break;
        if (_method[now] == "public" || _method[now] == "public" || _method[now] == "public") {
            if (f1)
                throw "don't write accese attribute twice";
            method.access = _method[now];
            f1 = true;
            continue;
        }
        else if (_method[now] == "final") {
            if (f2)
                throw "don't write final attribute twice";
            method.is_final = true;
            f2 = true;
            continue;
        }else if (_method[now] == "static") {
            if (f3)
                throw "don't write static attribute twice";
            method.is_static = true;
            f3 = true;
            continue;
        }
        method.attributes.push_back(_method[now]);
    }
    method.name = _method[_method.size() - 1];
    clazz.methods.push_back(method);
}

inline std::string VECTOR2STR(std::vector<std::string> vec) {
    std::string str = "";
    for (auto s : vec) {
        str = str + " " + s;
    }
    return str;
}

void _codeGen(std::istream& in, std::vector<std::string>& insList) {
    while (true) {
        std::vector<std::string> _code = getLineStr(in);
        if (_code.size() == 1 && _code[0] == "end")
            break;
        insList.push_back(VECTOR2STR(_code));
    }
}

void _memberClassGen(std::vector<std::string> _memberClass, RainClass& clazz) {
    clazz.memberClasses.push_back(_memberClass[1]);
}

void _memberGen(std::istream& in, std::vector<std::string>& insList, RainClass& clazz) {
    std::vector<std::string> _member = getLineStr(in);
#define _head _member[0]
    if (_head == "field") {
        _fieldGen(_member, clazz);
    }
    else if (_head == "method") {
        _methodGen(_member, clazz);
        _codeGen(in, insList);
    }
    else if(_head == "class") {
        _memberClassGen(_member, clazz);
    }
#undef _head
}
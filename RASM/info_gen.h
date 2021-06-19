#ifndef __INFO_GEN__
#define __INFO_GEN__

#include "class_info.h"
#include <string>
#include <iostream>

std::string getStr(std::istream& in, char& last);
std::vector<std::string> getLineStr(std::istream& in);
void _clazzGen(std::istream& in, RainClass& clazz);
void _fieldGen(std::vector<std::string> _field, RainClass& clazz);
void _methodGen(std::vector<std::string> _method, RainClass& clazz);
void _memberClassGen(std::vector<std::string> _memberClass, RainClass& clazz);
void _memberGen(std::istream& in, std::vector<std::string> insList, RainClass& clazz);

#endif
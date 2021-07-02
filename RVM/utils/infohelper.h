#ifndef __INFOHELPER_H__
#define __INFOHELPER_H__

#include "../executer/executer.h"

void printClassInfo(Runtime::RainClass clazz);
void printMethodInfo(Runtime::Method method, Runtime::RainClass clazz);
void printFieldInfo(Runtime::Field field, Runtime::RainClass clazz);
void printConstPool(std::vector<std::string> const_pool);
void printInstructions(std::vector<Runtime::Instruction> ins);

#endif
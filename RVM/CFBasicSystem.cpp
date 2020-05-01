#include "CFBasicSystem.h"

Value* sleep(Program* program){
	int num=program->getFromTop()->getNumber();
	program->pop();
	Sleep(num);
	return NULL;
}

#include "CFBasicMath.h"

Value* atoi(Program* program)
{
	string s = program->getFromTop()->getStr();
	program->pop();
	return new Value(atoi(s.c_str()));	
}

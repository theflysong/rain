#include "CFBasicIO.h"

Value* print(Program* program)
{ 
	int num = program->getFromTop()->getNumber();
	program->pop();
	while(num--){
		Value* v = program->getFromTop();
		switch(v->getType()){
		case Value::TYPE_STRING:
			cout<<v->getStr();
			break;
		case Value::TYPE_NUMBER:
			cout<<v->getNumber();
			break;
		case Value::TYPE_DECIMAL:
			cout<<v->getDecimal();
			break;
		}
		program->pop();
	}
	return NULL;
}

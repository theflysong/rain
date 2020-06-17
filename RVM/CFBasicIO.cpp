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
		case Value::TYPE_ID:
			Value* v1 = program->getVariable(v->getID());
			switch(v1->getType()){
			case Value::TYPE_STRING:
				cout<<v1->getStr();
				break;
			case Value::TYPE_NUMBER:
				cout<<v1->getNumber();
				break;
			case Value::TYPE_DECIMAL:
				cout<<v1->getDecimal();
				break;
			}
		}
		program->pop();
	}
	return NULL;
}

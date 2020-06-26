#include "ITranslator.h"

ITranslator::ITranslator(){
	
}

ITranslator::~ITranslator(){
	
}
 
ITranslator::codes ITranslator::newCode(int length){
	short* codeArray=new short[length];
	codes code={codeArray,length};
	return code;
}

void ITranslator::delCode(codes code){
	delete code.code;
	code.code=NULL;
}

void ITranslator::del(codes code){
	delCode(code);
}sss

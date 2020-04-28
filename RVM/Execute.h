#ifndef __EXECUTE__
#define __EXECUTE__

#include "head.h"
#include "SCI.h"
#include "Main.h"

class Executer
{
private:
	ICStream* stream;
	SCIInstruction getSource();
	std::map<string,SCIInstruction::OptCode> optCodeMap;
public:
	Executer(ICStream* stream);
	int execute();
}; 

#endif

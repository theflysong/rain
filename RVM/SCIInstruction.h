#ifndef __SCI_INSTRUCTION__
#define __SCI_INSTRUCTION__

class SCIInstruction
{
public:
	enum OptCode{
		NOP =-1,
		MOV,
		PUSH,
		POP,
		CALL,
		JMP,
		EXIT
	};
	OptCode opt;
	int arg1;
	int arg2;
	int arg3;
	SCIInstruction(OptCode opt,int parma1,int parma2,int parma3);
};

#endif

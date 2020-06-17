#ifndef __SCI_INSTRUCTION__
#define __SCI_INSTRUCTION__

#include<cstddef>
 
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
		NEW,
		DEL,
		JPT,
		JPF,
		CMP, 
		EXIT,
		ADD,
		SUB,
		MUL,
		DEV,
		MOD,
		SET,
		INC,
		DEC,
		DEF
	};
	OptCode opt;
	size_t arg1;
	size_t arg2;
	size_t arg3;
	SCIInstruction(OptCode opt,size_t parma1,size_t parma2,size_t parma3);
};

#endif

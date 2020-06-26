#include "Main.h"

class ITranslator{
public:
	struct codes{
		short* code;
		int length;
	};
private:
	static codes newCode(int length);
	static void delCode(codes code);
public:
	static void del(codes code);
	ITranslator();
	virtual ~ITranslator();
	virtual short* translate(string word)=0;
};

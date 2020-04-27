#ifndef __ICSTREAM__
#define __ICSTREAM__

#include "head.h"

/*
	×Ö·ûÁ÷ 
*/
class ICStream
{
protected:
	bool eos;
public:
	virtual char read()=0;
	virtual char peek()=0;
	virtual void back(int index=1)=0;
};

#endif

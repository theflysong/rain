#ifndef __ICSTREAM__
#define __ICSTREAM__

#include "head.h"

/*
	字符流 
*/
class ICStream
{
public:
	//End Of Stream(流结束标志)
	static int eos;
	virtual char read()=0; //读取下一个字符 
	virtual char peek()=0; //查看下一个字符
	virtual void back(int index=1)=0; //回到上index个字符的位置 
};

#endif

#ifndef __ICSTREAM__
#define __ICSTREAM__

#include "head.h"

/*
	�ַ��� 
*/
class ICStream
{
public:
	//End Of Stream(��������־)
	static int eos;
	virtual char read()=0; //��ȡ��һ���ַ� 
	virtual char peek()=0; //�鿴��һ���ַ�
	virtual void back(int index=1)=0; //�ص���index���ַ���λ�� 
};

#endif

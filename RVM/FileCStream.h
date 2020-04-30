#ifndef __FILESTREAM__
#define __FILESTREAM__

#include "ICStream.h"

/*
	�ļ��ַ��� 
*/ 
class FileCStream : 
	public ICStream
{
private:
	//�ַ��� 
	vector<char> data;
	//�ַ���ָ�� 
	int next;
public:
	FileCStream(string FileIn);
	string setStrings(string FileIn);
	virtual char read(); //��ȡ��һ���ַ� 
	virtual char peek(); //�鿴��һ���ַ� 
	virtual void back(int index=1); //�ص���index���ַ���λ�� 
	bool eof(); //�Ƿ����
	virtual ~FileCStream();
};

#endif


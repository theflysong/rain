#ifndef __FILESTREAM__
#define __FILESTREAM__

#include "ICStream.h"

/*
	文件代码类 
*/ 
class FileCStream : 
	public ICStream
{
private:
	vector<char> data;
	int next;
public:
	FileCStream(string FileIn);
	string setStrings(string FileIn);
	virtual char read();
	virtual char peek();
	virtual void back(int index=1);
	bool eof();
};

#endif


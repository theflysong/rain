#ifndef __FILESTREAM__
#define __FILESTREAM__

#include "ICStream.h"

/*
	文件字符流 
*/ 
class FileCStream : 
	public ICStream
{
private:
	//字符流 
	vector<char> data;
	//字符流指针 
	int next;
public:
	FileCStream(string FileIn);
	string setStrings(string FileIn);
	virtual char read(); //读取下一个字符 
	virtual char peek(); //查看下一个字符 
	virtual void back(int index=1); //回到上index个字符的位置 
	bool eof(); //是否结束
	virtual ~FileCStream();
};

#endif


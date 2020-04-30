#include "FileCStream.h"

/*
	从文件里获取代码 
*/
FileCStream::FileCStream(string FileIn) : next(0)
{
	ifstream fin(FileIn.c_str());
	while(!fin.eof()){
		data.push_back(fin.get());
	}
	data.push_back(ICStream::eos);
	fin.close();
}

/*
	读取下一个字符 
*/
char FileCStream::read()
{
	return data[next++];
} 
	
/*
	查看下一个字符 
*/	
char FileCStream::peek()
{
	return data[next];	
}

/*
	回到前面第index个字符 
*/
void FileCStream::back(int index)
{
	next-=index;
}

/*
	重新设置FileStream的文件代码 
*/
string FileCStream::setStrings(string FileIn)
{
	ifstream fin(FileIn.c_str());
	while(!fin.eof()){
		data.push_back(fin.get());
	}
	fin.close();
}

/*
	文件是否结束 
*/
bool FileCStream::eof()
{
	return next>=data.size();
}

FileCStream::~FileCStream()
{
	
}

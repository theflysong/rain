#include "FileCStream.h"

/*
	���ļ����ȡ���� 
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
	��ȡ��һ���ַ� 
*/
char FileCStream::read()
{
	return data[next++];
} 
	
/*
	�鿴��һ���ַ� 
*/	
char FileCStream::peek()
{
	return data[next];	
}

/*
	�ص�ǰ���index���ַ� 
*/
void FileCStream::back(int index)
{
	next-=index;
}

/*
	��������FileStream���ļ����� 
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
	�ļ��Ƿ���� 
*/
bool FileCStream::eof()
{
	return next>=data.size();
}

FileCStream::~FileCStream()
{
	
}

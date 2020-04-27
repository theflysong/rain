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
	eos=false;
	fin.close();
}

/*
	��ȡ��һ���ַ� 
*/
char FileCStream::read()
{
	eos = (next+1>=data.size());
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
	eos=(next>=data.size());
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
	return eos;
}

#ifndef __HEAD__
#define __HEAD__
/*
	һ��ѿ��п��޵�ͷ�ļ���using 
*/ 
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <windows.h>
using std::ios;
using std::vector;
using std::cin;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::istream;
using std::ostream;
using std::iostream;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::string;
using std::map;
using std::stack;
using std::queue;
using std::cerr;
using std::endl;

/*
	���ƶ��� 
*/
void _assert(bool condition,string fileIn,int lineIn);

/*
	�� 
*/
#define null (0)

/*
	ֻҪ����DEBUG��ʽ����Ϳ���ʹ�� 
*/
#ifdef __DEBUG__
	#define assert(condition) _assert(condition,__FILE__,__LINE__)
	#define assertNull(condition) assert(condition != null)
#else
	#define assert(condition)
	#define assertNull(condtion)
#endif

/*
	�����˳� 
*/
inline void ErrorExit() {
    Sleep(10000);
    exit(-1);
}
/*
	�����˳� 
*/
inline void NormalExit() {
    Sleep(1000);
    exit(0);
}
/*
	ת���ַ��� 
*/ 
void escape(string& str);

/*
	ת������쳣 
*/
struct EscapeException : public std::exception
{
private:
    char errorCharacter;
public:
    const char* what() const throw ();
    EscapeException(char c);
};

/*
	ת������쳣 
*/
struct TooBigNumException : public std::exception
{
private:
    int errorNum;
public:
    const char* what() const throw ();
    TooBigNumException(int num);
};

inline bool isNumber(string str)
{
	for(int i=0;i<str.length();i++){
		if(str[i]=='-'||str[i]=='+'){
			if(i==0)
				continue;
			return false;
		}
		if(!isdigit(str[i]))
			return false;
	}
	return true;
}

inline int toNumber(string str)
{
	return atoi(str.c_str());
}

inline bool isDecimal(string str)
{
	bool b=false;
	for(int i=0;i<str.length();i++){
		if(str[i]=='-'||str[i]=='+'){
			if(i==0)
				continue;
			return false;
		}
		if(!(isdigit(str[i])||str[i]=='.'))
			return false;
		if(str[i]=='.')
			if(b)
				return false;
			else
				b=true;
	}
	return true;
}

inline double toDecimal(string str)
{
	return atof(str.c_str());
}

inline bool isString(string str)
{
	return str[0]=='"'&&str[str.length()-1]=='"';
}

inline string toString(string str)
{
	string s="";
	for(int i=1;i<str.length()-1;i++)
	{
		s+=str[i];
	}
	escape(s);
	return s;
}

#endif

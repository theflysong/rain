#ifndef __SCI_VALUE__
#define __SCI_VALUE__
#include "head.h"

/*
	值类 
*/ 
class Value
{
public:
	enum VTYPE{
		TYPE_NULL=0, //空值 
		TYPE_NUMBER, //整数 
		TYPE_DECIMAL, //小数 
		TYPE_STRING, //字符串 
		TYPE_FUNCTION, //函数 
		TYPE_CLASS //类 
	};
private:
	VTYPE type;
	union{
		int* number;
		double* decimal;
		string* str;
	};
public:
	Value();
	Value(int number);
	Value(string str);
	Value(double decimal);
	~Value();
	int getNumber();
	void setNumber(int number);
	string getStr();
	void setStr(int str);
	double getDecimal();
	void setDecimal(double decimal);
	VTYPE getType();
};

#endif

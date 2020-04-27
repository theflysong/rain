#ifndef __SCI_VALUE__
#define __SCI_VALUE__
#include "head.h"

/*
	ֵ�� 
*/ 
class Value
{
public:
	enum VTYPE{
		TYPE_NULL=0, //��ֵ 
		TYPE_NUMBER, //���� 
		TYPE_DECIMAL, //С�� 
		TYPE_STRING, //�ַ��� 
		TYPE_FUNCTION, //���� 
		TYPE_CLASS //�� 
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

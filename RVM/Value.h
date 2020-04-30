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
		TYPE_CLASS, //�� 
		TYPE_ID
	};
	static string toString(VTYPE type);
	Value();
	Value(int number);
	Value(string str,VTYPE type);
	Value(double decimal);
	/*��������*/
	~Value();
	/*��ֵ��������*/ 
	int getNumber();
	void setNumber(int number);
	string getStr();
	void setStr(string str);
	double getDecimal();
	void setDecimal(double decimal);
	string getID();
	void setID(int ID);
	string getFunction();
	void setFunction(string function);
	/*�������*/
	VTYPE getType();
	void setType(VTYPE type);
private:
	VTYPE type;
	/*ֵ������һ��Valueֻ���ܶ�Ӧһ�����ͣ�����ʹ��union*/
	union{
		int* number;
		double* decimal;
		string* str;
		string* ID;
		string* FunctionName;
		void* ptr;
	};
};

#endif

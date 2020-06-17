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
		TYPE_CLASS, //类&类型 
		TYPE_ID
	};
	static string toString(VTYPE type);
	Value();
	Value(int number);
	Value(string str,VTYPE type);
	Value(double decimal);
	Value(VTYPE type);
	Value(VTYPE clazz,string name);
	/*析构函数*/
	~Value();
	/*数值操作方法*/ 
	int getNumber();
	void setNumber(int number);
	string getStr();
	void setStr(string str);
	double getDecimal();
	void setDecimal(double decimal);
	string getID();
	void setID(string ID);
	string getFunction();
	void setFunction(string function);
	VTYPE getClass();
	void setClass(VTYPE clazz);
	/*获得类型*/
	VTYPE getType();
	void setType(VTYPE type);
	/*获得指针*/
	void* getPtr(); 
private:
	VTYPE type;
	/*值，由于一个Value只可能对应一种类型，所以使用union*/
	union{
		int* number;
		double* decimal;
		string* str;
		string* ID;
		string* FunctionName;
		VTYPE* clazz;
		void* ptr;
	};
};

#endif

#include "Value.h"

/*
	构造函数 
*/
Value::Value() : type(TYPE_NULL)
{
}

string Value::toString(VTYPE type){
	switch(type){
	case TYPE_FUNCTION:
		return "function";
	case TYPE_NUMBER:
		return "number";
	case TYPE_CLASS:
		return "class";
	case TYPE_STRING:
		return "string";
	case TYPE_DECIMAL:
		return "decimal";
	case TYPE_ID:
		return "ID";
	case TYPE_NULL:
		return "null"; 
	}
	return "unknowType";
}

Value::Value(int number) : type(TYPE_NUMBER)
{
	this->number = new int(number);
}

Value::Value(string str,VTYPE type) : type(type)
{
	this->str = new string(str);
}

Value::Value(double decimal) : type(TYPE_DECIMAL)
{
	this->decimal = new double(decimal);
}

/*
	对值操作 
*/
int Value::getNumber()
{
	return *(this->number);
}

void Value::setNumber(int number)
{
	*(this->number)=number;
}

string Value::getStr()
{
	return *(this->str);
}

void Value::setStr(string str)
{
	*(this->str)=str;
}

double Value::getDecimal()
{
	return *(this->decimal);
}

void Value::setDecimal(double decimal)
{
	*(this->decimal)=decimal;
}

string Value::getID()
{
	return *(this->ID);
}

void Value::setID(int ID)
{
	*(this->ID)=ID;
}

string Value::getFunction()
{
	return *(this->FunctionName);
}

void Value::setFunction(string function)
{
	*(this->FunctionName)=function;
}

/*
	获得Value类型 
*/
Value::VTYPE Value::getType()
{
	return this->type;
} 

void Value::setType(Value::VTYPE type)
{
	this->type=type;
}

/*
	析构函数
*/
Value::~Value()
{
	delete this->ptr;
}

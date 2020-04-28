#include "Value.h"

/*
	构造函数 
*/
Value::Value() : type(TYPE_NULL)
{
}

Value::Value(int number) : type(TYPE_NUMBER)
{
	this->number = new int(number);
}

Value::Value(string str) : type(TYPE_STRING)
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

void Value::setStr(int str)
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

void Value::setFunction(int function)
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
	switch(type)
	{
		case TYPE_NUMBER:
			delete this->number;
			break;
		case TYPE_DECIMAL:
			delete this->decimal;
			break;
		case TYPE_STRING:
			delete this->str;
			break;
		case TYPE_ID:
			delete this->ID;
			break;
		case TYPE_FUNCTION:
			delete this->FunctionName;
			break; 
		default:
			break;
	}
}

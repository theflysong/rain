#include "head.h"

/*
	自制断言 
*/ 
void _assert(bool condition,string fileIn,int lineIn)
{
#ifdef __DEBUG__
	if(!condition){
		cerr<<"Has error in "<<fileIn<<" line "<<lineIn;
		exit(-1);
	}
#endif
}

/*
	抛出异常 
*/
const char*  EscapeException::what() const throw () {
    string s("Wrong escape character \'");
    s += errorCharacter;
    s += "\' before \\.";
    return s.c_str();
}

/*
	构造函数 
*/
EscapeException::EscapeException(char c) {
    this->errorCharacter = c;
}

/*
	抛出异常 
*/
const char* TooBigNumException::what() const throw () {
    string s;
    s += this->errorNum;
    s += "is to big of Character.";
    return s.c_str();
}

/*
	构造函数 
*/
TooBigNumException::TooBigNumException(int num) {
    this->errorNum = num;
}

/*
	转义字符串 
*/ 
void escape(string& str)
{
    int value;
    string s;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] != '\\') {
            s += str[i];
        }
        else {
            i++;
            switch (str[i]) {
            case 'a':case 'A': s += "\a"; break;
            case 'b':case 'B': s += "\b"; break;
            case 'f':case 'F': s += "\f"; break;
            case 'n':case 'N': s += "\n"; break;
            case 'r':case 'R': s += "\r"; break;
            case 't':case 'T': s += "\t"; break;
            case 'v':case 'V': s += "\v"; break;
            case '\\': s += "\\"; break;
            case '\'': s += "\'"; break;
            case '\"': s += "\""; break;
            case '?': s += "\?"; break;
            case '0': s += "\0"; break;
            case 'x':case 'X':
                i++;
                value = 0;
                for (int j = 0; j < 2; j++, i++) {
                    if (str[i] >= '0' && str[i] <= '9') {
                        value = value * 16 + str[i] - '0';
                        i++;
                    }
                    else if (str[i] >= 'a' && str[i] <= 'f') {
                        value = value * 16 + str[i] - 'a' + 10;
                    }
                    else if (str[i] >= 'A' && str[i] <= 'F') {
                        value = value * 16 + str[i] - 'A' + 10;
                    }
                    else {
                        throw EscapeException(str[i]);
                    }
                }
                if (value > 255) {
                    throw TooBigNumException(value);
                }
                s += (char)value;
                break;
            default:
                if (str[i] >= '0' && str[i] < '8') {
                    value = str[i] - '0';
                    i++;
                    for (int j = 0; j < 2; j++, i++) {
                        if (str[i] >= '0' && str[i] < '8') {
                            value = value * 8 + str[i] - '0';
                        }
                        else {
                            break;
                        }
                    }
                    if (value > 255) {
                        throw TooBigNumException(value);
                    }
                    s += (char)value;
                }
                else {
                    throw EscapeException(str[i]);
                }
            }
        }
    }
    str = s;
}

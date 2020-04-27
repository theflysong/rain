#include "Main.h"

/*
	程序栈 
*/
class Program
{
private:
	RuntimeStack ValueStack; //运行时程序值栈 
};

/*
	程序开始 
*/
int main()
{
	string where;
	cin>>where;
	FileCStream file(where);
	while(!file.eof()){
		cout<<file.read();
	}
	return 0;
}

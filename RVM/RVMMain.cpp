#include "Main.h"

/*
	����ջ 
*/
class Program
{
private:
	RuntimeStack ValueStack; //����ʱ����ֵջ 
};

/*
	����ʼ 
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

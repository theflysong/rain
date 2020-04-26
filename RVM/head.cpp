#include "head.h"

void _assert(bool condition,string fileIn,int lineIn)
{
#ifdef __DEBUG__
	if(!condition){
		cerr<<"Has error in "<<fileIn<<" line "<<lineIn;
		exit(-1);
	}
#endif
}

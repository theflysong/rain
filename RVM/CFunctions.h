#ifndef __CFUN__
#define __CFUN__

#include "CFBasicIO.h"
#include "CFBasicSystem.h"
#include "Main.h"

typedef Value*(*CFunction)(Program*);

extern map<std::string,CFunction> CFunctionMap; 

#endif

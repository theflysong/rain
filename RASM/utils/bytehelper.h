#ifndef __BYTEHELPER_HEADER__
#define __BYTEHELPER_HEADER__

#include "../const/defs.h"

short asShort(byte* bytes);
short asShort(byte b1, byte b2);
int asInt(byte* bytes);
int asInt(byte b1, byte b2, byte b3, byte b4);
long long asLongLong(byte* bytes);
long long asLongLong(byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7, byte b8);
byte* asByte(short num, byte* out);
byte* asByte(int num, byte* out);
byte* asByte(long long num, byte* out);

#endif
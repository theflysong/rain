#ifndef __BYTEHELPER_HEADER__
#define __BYTEHELPER_HEADER__

#include "../const/defs.h"

r_short asShort(byte* bytes);
r_short asShort(byte b1, byte b2);
r_int asInt(byte* bytes);
r_int asInt(byte b1, byte b2, byte b3, byte b4);
r_long asLong(byte* bytes);
r_long asLong(byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7, byte b8);
byte* asByte(r_short num, byte* out);
byte* asByte(r_int num, byte* out);
byte* asByte(r_long num, byte* out);

#endif
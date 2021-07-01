#include "bytehelper.h"

r_short asShort(byte* bytes) {
    return asShort(bytes[0], bytes[1]);
}

r_short asShort(byte b1, byte b2) {
    return (((r_int)b1) << 8) + (((r_int)b2));
}

r_int asInt(byte* bytes) {
    return asInt(bytes[0], bytes[1], bytes[2], bytes[3]);
}

r_int asInt(byte b1, byte b2, byte b3, byte b4) {
    return (((r_int)b1) << 24) + (((r_int)b2) << 16) + (((r_int)b3) << 8) + ((r_int)b4);
}

r_long asLongLong(byte* bytes) {
    return asLongLong(bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
}

r_long asLongLong(byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7, byte b8) {
    return (((r_long)b1) << 56) + (((r_long)b2) << 48) + (((r_long)b3) << 40) + (((r_long)b4) << 32) + (((r_long)b5) << 24) + (((r_long)b6) << 16) + (((r_long)b7) << 8) + ((r_long)b8);
}

byte* asByte(r_short num, byte* out) {
    out[1] = (num & 0x00FF);
    out[0] = (num & 0xFF00) >> 8;
    return out;
}

byte* asByte(r_int num, byte* out) {
    out[3] = (num & 0x000000FF);
    out[2] = (num & 0x0000FF00) >> 8;
    out[1] = (num & 0x00FF0000) >> 16;
    out[0] = (num & 0xFF000000) >> 24;
    return out;
}

byte* asByte(r_long num, byte* out) {
    out[7] = (num & 0x00000000000000FF);
    out[6] = (num & 0x000000000000FF00) >> 8;
    out[5] = (num & 0x0000000000FF0000) >> 16;
    out[4] = (num & 0x00000000FF000000) >> 24;
    out[3] = (num & 0x000000FF00000000) >> 32;
    out[2] = (num & 0x0000FF0000000000) >> 40;
    out[1] = (num & 0x00FF000000000000) >> 48;
    out[0] = (num & 0xFF00000000000000) >> 56;
    return out;
}
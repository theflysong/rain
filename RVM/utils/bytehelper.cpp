#include "bytehelper.h"

short asShort(byte* bytes) {
    return asShort(bytes[0], bytes[1]);
}

short asShort(byte b1, byte b2) {
    return (((int)b1) << 16) + (((int)b2));
}

int asInt(byte* bytes) {
    return asInt(bytes[0], bytes[1], bytes[2], bytes[3]);
}

int asInt(byte b1, byte b2, byte b3, byte b4) {
    return (((int)b1) << 24) + (((int)b2) << 16) + (((int)b3) << 8) + ((int)b4);
}

long long asLongLong(byte* bytes) {
    return asLongLong(bytes[0], bytes[1], bytes[2], bytes[3], bytes[4], bytes[5], bytes[6], bytes[7]);
}

long long asLongLong(byte b1, byte b2, byte b3, byte b4, byte b5, byte b6, byte b7, byte b8) {
    return (((long long)b1) << 56) + (((long long)b2) << 48) + (((long long)b3) << 40) + (((long long)b4) << 32) + (((long long)b5) << 24) + (((long long)b6) << 16) + (((long long)b7) << 8) + ((long long)b8);
}

byte* asByte(short num, byte* out) {
    out[0] = (num & 0x00FF);
    out[1] = (num & 0xFF00) >> 8;
    return out;
}

byte* asByte(int num, byte* out) {
    out[0] = (num & 0x000000FF);
    out[1] = (num & 0x0000FF00) >> 8;
    out[2] = (num & 0x00FF0000) >> 16;
    out[3] = (num & 0xFF000000) >> 24;
    return out;
}

byte* asByte(long long num, byte* out) {
    out[0] = (num & 0x00000000000000FF);
    out[1] = (num & 0x000000000000FF00) >> 8;
    out[2] = (num & 0x0000000000FF0000) >> 16;
    out[3] = (num & 0x00000000FF000000) >> 24;
    out[4] = (num & 0x000000FF00000000) >> 32;
    out[5] = (num & 0x0000FF0000000000) >> 40;
    out[6] = (num & 0x00FF000000000000) >> 48;
    out[7] = (num & 0xFF00000000000000) >> 56;
    return out;
}
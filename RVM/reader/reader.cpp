#include "reader.h"
#include "../utils/bytehelper.h"
#include <fstream>

FileByteReader::FileByteReader(std::string filename) {
    this->load(filename);
}

byte FileByteReader::next() {
    return datas[cr_pos ++];
}

byte FileByteReader::peek() {
    return datas[cr_pos];
}

byte FileByteReader::last() {
    return datas[-- cr_pos];
}

byte FileByteReader::jmp(int pos) {
    return datas[cr_pos = pos];
}

byte FileByteReader::skip(int num) {
    return datas[cr_pos += num];
}

bool FileByteReader::clr() {
    datas.clear();
    return true;
}

bool FileByteReader::load(std::string filename) {
    this->cr_pos = 0;
    std::ifstream fin(filename.c_str());
    if (fin.bad()) {
        return false;
    }
    while (! fin.eof()) {
        datas.push_back(fin.get());
    }
    return true;
}

byte* FileByteReader::gets(byte* out, int num) {
    for (int i = 0 ; i < num ; i ++) {
        out[i] = next();
    }
    return out;
}

short FileByteReader::getAsShort() {
    byte *value = new byte[2];
    short result = asShort(gets(value, 2));
    delete value;
    return result;
}

int FileByteReader::getAsInt() {
    byte *value = new byte[4];
    int result = asInt(gets(value, 4));
    delete value;
    return result;
}

long long FileByteReader::getAsLongLong() {
    byte *value = new byte[8];
    long long result = asLongLong(gets(value, 8));
    delete value;
    return result;
}
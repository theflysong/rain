#include "reader.h"
#include "../utils/bytehelper.h"
#include <fstream>
#include <iostream>

FileByteReader::FileByteReader(std::string filename) {
    this->load(filename);
}

FileByteReader::~FileByteReader() {
    clr();
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
    if (datas == NULL)
        return true;
    delete[] datas;
    datas = NULL;
    return true;
}

bool FileByteReader::load(std::string filename) {
    this->cr_pos = 0;
    std::ifstream fin(filename.c_str(), std::ios::binary);
    if (fin.bad()) {
        return false;
    }
    fin.seekg(0, std::ifstream::end);
    int size = fin.tellg();
    fin.close();
    fin.open(filename.c_str(), std::ios::binary);
    if (fin.bad()) {
        return false;
    }
    datas = new byte[size];
    fin.read(datas, size);
    return true;
}

byte* FileByteReader::gets(byte* out, int num) {
    for (int i = 0 ; i < num ; i ++) {
        out[i] = next();
    }
    return out;
}

r_short FileByteReader::getAsShort() {
    byte *value = new byte[2];
    short result = asShort(gets(value, 2));
    delete[] value;
    return result;
}

r_int FileByteReader::getAsInt() {
    byte *value = new byte[4];
    gets(value, 4);
    int result = asInt(value);
    delete[] value;
    return result;
}

r_long FileByteReader::getAsLong() {
    byte *value = new byte[8];
    r_long result = asLong(gets(value, 8));
    delete[] value;
    return result;
}
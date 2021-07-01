#ifndef __READER_HEADER__
#define __READER_HEADER__

#include "../const/defs.h"
#include <string>
#include <vector>

#ifndef __IREADER_INTERFACE__
#define __IREADER_INTERFACE__
template<class T> interface IReader {
public:
    virtual T next() = 0;
    virtual T peek() = 0;
    virtual T last() = 0;
    virtual T jmp(int pos) = 0;
    virtual T skip(int num) = 0;
    virtual bool clr() = 0;
};
#endif

#ifndef __READER_CLASS__
#define __READER_CLASS__

abstract class IByteReader : implement IReader<byte> {
public:
    virtual byte* gets(byte* out, int num) = 0;
    virtual r_short getAsShort() = 0;
    virtual r_int getAsInt() = 0;
    virtual r_long getAsLong() = 0;
};

class FileByteReader : public IByteReader {
    std::vector<byte> datas;
    int cr_pos;
public:
    FileByteReader(std::string filename);
    byte* gets(byte* out, int num) override final;
    r_short getAsShort() override final;
    r_int getAsInt() override final;
    r_long getAsLong() override final;
    byte next() override final;
    byte peek() override final;
    byte last() override final;
    byte jmp(int pos) override final;
    byte skip(int num) override final;
    bool clr() override final;
    bool load(std::string filename);
};

#endif

#endif
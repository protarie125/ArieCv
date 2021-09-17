#include "BitmapFileHeader.h"

ahs::codec::BitmapFileHeader::BitmapFileHeader() = default;

ahs::codec::BitmapFileHeader::BitmapFileHeader(int fileSize, int offset)
    : fileSize_{ fileSize }
    , offset_{ offset }
{
}

ahs::codec::BitmapFileHeader::~BitmapFileHeader() = default;

std::string ahs::codec::BitmapFileHeader::getMagicNumber() const noexcept
{
    std::string ret{ "12" };
    ret[0] = h1_;
    ret[1] = h2_;

    return ret;
}

int ahs::codec::BitmapFileHeader::getFileSize() const noexcept
{
    return fileSize_;
}

int ahs::codec::BitmapFileHeader::getOffset() const noexcept
{
    return offset_;
}
#include "BitmapInfoHeader.h"

ahs::codec::BitmapInfoHeader::BitmapInfoHeader() = default;

ahs::codec::BitmapInfoHeader::BitmapInfoHeader(int width, int height, short bpp, int imageSize)
    : width_{ width }
    , height_{ height }
    , bpp_{ bpp }
    , imageSize_{ imageSize }
{
}

ahs::codec::BitmapInfoHeader::~BitmapInfoHeader() = default;

int ahs::codec::BitmapInfoHeader::getHeaderSize() const noexcept
{
    return headerSize_;
}

int ahs::codec::BitmapInfoHeader::getWidth() const noexcept
{
    return width_;
}

int ahs::codec::BitmapInfoHeader::getHeight() const noexcept
{
    return height_;
}

int ahs::codec::BitmapInfoHeader::getBpp() const noexcept
{
    return bpp_;
}

int ahs::codec::BitmapInfoHeader::getNumColors() const noexcept
{
    return numColors_;
}

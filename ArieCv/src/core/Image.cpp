#include "Image.h"

#include "codec/BmpDecoder.h"
#include "codec/BmpEncoder.h"

#include <iostream>

ahs::Image::Image() = default;

ahs::Image::Image(int width, int height, int stride, char* data)
    : rawData_{ data }
    , width_{ width }
    , height_{ height }
    , stride_{ stride }
{
}

ahs::Image::Image(const ahs::Image & copy)
    : width_{ copy.width_ }
    , height_{ copy.height_ }
    , stride_{ copy.stride_ }
{
    std::cout << "Copy Constructor...\n";

    auto cb = copy.stride_ * copy.height_;
    rawData_ = new char[cb];

    memcpy_s(rawData_, cb, copy.rawData_, cb);
}

ahs::Image::Image(ahs::Image && move) noexcept
    : rawData_{ move.rawData_ }
    , width_{ move.width_ }
    , height_{ move.height_ }
    , stride_{ move.stride_ }
{
    std::cout << "Move Constructor...\n";

    move.rawData_ = nullptr;
}

ahs::Image::~Image()
{
    if (rawData_ != nullptr) delete[] rawData_;
}

ahs::Image& ahs::Image::operator=(const ahs::Image & copy)
{
    if (this != &copy)
    {
        std::cout << "Copy Assign...\n";

        width_ = copy.width_;
        height_ = copy.height_;
        stride_ = copy.stride_;

        if (rawData_ != nullptr) delete[] rawData_;

        auto cb = stride_ * height_;
        rawData_ = new char[cb];
        memcpy_s(rawData_, cb, copy.rawData_, cb);
    }

    return *this;
}

ahs::Image& ahs::Image::operator=(ahs::Image && move) noexcept
{
    if (this != &move)
    {
        delete[] rawData_;
        rawData_ = move.rawData_;
        move.rawData_ = nullptr;

        width_ = move.width_;
        height_ = move.height_;
        stride_ = move.stride_;
    }

    return *this;
}

const int& ahs::Image::getWidth() const noexcept
{
    return width_;
}

const int& ahs::Image::getHeight() const noexcept
{
    return height_;
}

const int& ahs::Image::getStride() const noexcept
{
    return stride_;
}

const char* ahs::Image::getRawData() const noexcept
{
    return rawData_;
}

bool ahs::Image::isInitialized() const noexcept
{
    return (rawData_ != nullptr);
}

void ahs::Image::write(const char* filename) const
{
    ahs::codec::BmpEncoder encoder;

    encoder.encode(*this, filename);
}

ahs::Image ahs::Image::fromFile(const char* filename)
{
    ahs::codec::BmpDecoder decoder;

    return decoder.decode(filename);
}
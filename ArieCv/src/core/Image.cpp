#include "Image.h"

#include "codec/BmpDecoder.h"
#include "codec/BmpEncoder.h"

#include <iostream>

ahs::Image::Image() = default;

ahs::Image::Image(const ahs::Image & copy)
    : width_{ copy.width_ }
    , height_{ copy.height_ }
    , numberOfChannels_{ copy.numberOfChannels_ }
    , bytePerData_{ copy.bytePerData_ }
{
    std::cout << "Copy Constructor...\n";

    rawData_ = new void* [copy.numberOfChannels_];

    auto cb = copy.width_ * copy.height_ * copy.bytePerData_;
    for (int i = 0; i < copy.numberOfChannels_; ++i)
    {
        rawData_[i] = new __int8[cb];
        memcpy_s(rawData_[i], cb, copy.rawData_[i], cb);
    }
}

ahs::Image::Image(ahs::Image && move) noexcept
    : rawData_{ move.rawData_ }
    , width_{ move.width_ }
    , height_{ move.height_ }
    , numberOfChannels_{ move.numberOfChannels_ }
    , bytePerData_{ move.bytePerData_ }
{
    std::cout << "Move Constructor...\n";

    move.rawData_ = nullptr;
}

ahs::Image::~Image()
{
    if (rawData_ != nullptr)
    {
        for (int i = 0; i < numberOfChannels_; ++i)
        {
            delete[] rawData_[i];
        }
        delete[] rawData_;
    }
}

ahs::Image& ahs::Image::operator=(const ahs::Image & copy)
{
    if (this != &copy)
    {
        std::cout << "Copy Assign...\n";

        width_ = copy.width_;
        height_ = copy.height_;
        numberOfChannels_ = copy.numberOfChannels_;
        bytePerData_ = copy.bytePerData_;

        if (rawData_ != nullptr)
        {
            for (int i = 0; i < numberOfChannels_; ++i)
            {
                delete[] rawData_[i];
            }
            delete[] rawData_;
        }

        rawData_ = new void* [numberOfChannels_];

        auto cb = copy.width_ * copy.height_ * copy.bytePerData_;
        for (int i = 0; i < copy.numberOfChannels_; ++i)
        {
            rawData_[i] = new __int8[cb];
            memcpy_s(rawData_[i], cb, copy.rawData_[i], cb);
        }
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
        numberOfChannels_ = move.numberOfChannels_;
        bytePerData_ = move.bytePerData_;
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

char* ahs::Image::getInterleavedData() const noexcept
{
    if (rawData_ == nullptr) return nullptr;

    if (numberOfChannels_ != 3) return nullptr;

    auto stride = width_ * numberOfChannels_ * bytePerData_;
    auto pad = (4 - (stride % 4)) % 4;
    stride += pad;
    auto cb = stride * height_;
    char* result = new char[cb];

    for (int r = 0; r < height_; ++r)
        for (int c = 0; c < width_; ++c)
        {
            result[r * stride + 3 * c] = std::bit_cast<char*>(rawData_[0])[r * width_ + c];
            result[r * stride + 3 * c + 1] = std::bit_cast<char*>(rawData_[1])[r * width_ + c];
            result[r * stride + 3 * c + 2] = std::bit_cast<char*>(rawData_[2])[r * width_ + c];
        }

    return result;
}

bool ahs::Image::isInitialized() const noexcept
{
    return (rawData_ != nullptr);
}

int ahs::Image::countChannels() const noexcept
{
    return numberOfChannels_;
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

ahs::Image ahs::Image::fromInterleavedBgr8(int width, int height, int stride, const __int8* data)
{
    ahs::Image result{};
    result.width_ = width;
    result.height_ = height;

    const auto ch{ 3 };
    result.numberOfChannels_ = ch;
    result.bytePerData_ = 1;

    result.rawData_ = new void* [ch];
    auto cb = width * height;
    for (int i = 0; i < ch; ++i)
    {
        result.rawData_[i] = new __int8[cb];
    }

    for (int r = 0; r < height; ++r)
        for (int c = 0; c < width; ++c)
        {
            std::bit_cast<__int8*>(result.rawData_[0])[r * width + c] = data[r * stride + 3 * c];
            std::bit_cast<__int8*>(result.rawData_[1])[r * width + c] = data[r * stride + 3 * c + 1];
            std::bit_cast<__int8*>(result.rawData_[2])[r * width + c] = data[r * stride + 3 * c + 2];
        }

    return result;
}
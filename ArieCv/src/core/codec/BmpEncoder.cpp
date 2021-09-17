#include "BmpEncoder.h"

#include <fstream>
#include <bit>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

ahs::codec::BmpEncoder::~BmpEncoder() = default;

void ahs::codec::BmpEncoder::encode(const ahs::Image & image, const char* filename)
{
    std::ofstream ofs{ filename, std::ofstream::trunc | std::ofstream::binary };
    if (ofs.is_open())
    {
        if (ofs.good())
        {
            const auto& width = image.getWidth();
            const auto& height = image.getHeight();
            const auto& stride = image.getStride();

            auto cb = stride * height;
            auto offset = static_cast<int>(sizeof(ahs::codec::BitmapFileHeader) + sizeof(ahs::codec::BitmapInfoHeader));

            ahs::codec::BitmapFileHeader bfh{ offset + cb, offset };
            ofs.write(std::bit_cast<char*>(&bfh), sizeof(ahs::codec::BitmapFileHeader));

            ahs::codec::BitmapInfoHeader bih{ width, height, 24, cb };
            ofs.write(std::bit_cast<char*>(&bih), sizeof(ahs::codec::BitmapInfoHeader));

            ofs.write(image.getRawData(), cb);
        }

        ofs.close();
    }
}
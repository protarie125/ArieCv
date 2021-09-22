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
            auto stride = width * image.countChannels();
            auto pad = (4 - (stride % 4)) % 4;
            stride += 4;

            auto cb = stride * height;
            auto offset = static_cast<int>(sizeof(ahs::codec::BitmapFileHeader) + sizeof(ahs::codec::BitmapInfoHeader));

            ahs::codec::BitmapFileHeader bfh{ offset + cb, offset };
            ofs.write(std::bit_cast<char*>(&bfh), sizeof(ahs::codec::BitmapFileHeader));

            auto bpp = static_cast<short>(8 * image.countChannels());
            ahs::codec::BitmapInfoHeader bih{ width, height, bpp, cb };
            ofs.write(std::bit_cast<char*>(&bih), sizeof(ahs::codec::BitmapInfoHeader));

            auto data = image.getInterleavedData();
            ofs.write(data, cb);

            delete data;
        }

        ofs.close();
    }
}
#include "BmpDecoder.h"

#include <fstream>
#include <bit>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

#include <iostream>

ahs::codec::BmpDecoder::~BmpDecoder() = default;

ahs::Image ahs::codec::BmpDecoder::decode(const char* filename)
{
    std::string str{ filename };
    std::ifstream ifs{ str, std::ifstream::binary };

    if (ifs.is_open())
    {
        if (ifs.good())
        {
            ahs::codec::BitmapFileHeader bfh;
            ifs.read(std::bit_cast<char*>(&bfh), sizeof(ahs::codec::BitmapFileHeader));

            std::cout << "== Read Result..." << std::endl
                << "Magic Number = " << bfh.getMagicNumber() << std::endl
                << "File Size = " << bfh.getFileSize() << std::endl
                << "Offset = " << bfh.getOffset() << std::endl;

            int dibSize{ 0 };
            ifs.read(std::bit_cast<char*>(&dibSize), 4);

            if (40 == dibSize)
            {
                ahs::codec::BitmapInfoHeader bih;
                ifs.seekg(sizeof(ahs::codec::BitmapFileHeader), std::ifstream::beg);
                ifs.read(std::bit_cast<char*>(&bih), sizeof(ahs::codec::BitmapInfoHeader));

                std::cout << "==== DIB INFO..." << std::endl
                    << "Header Size = " << bih.getHeaderSize() << std::endl
                    << "Width = " << bih.getWidth() << std::endl
                    << "Height = " << bih.getHeight() << std::endl
                    << "BPP = " << bih.getBpp() << std::endl
                    << "Num. Colors = " << bih.getNumColors() << std::endl;

                const auto& width = bih.getWidth();
                auto pad = (4 - (width % 4)) % 4;
                auto stride = width + pad;

                const auto& height = bih.getHeight();
                auto cb = stride * height;

                char* data = new char[cb];
                ifs.seekg(bfh.getOffset(), std::ifstream::beg);
                ifs.read(data, cb);

                ahs::Image result{ width, height, stride, data };

                return result;
            }
            else
            {
                throw std::runtime_error("DIB Not Supported.");
            }
        }

        ifs.close();
    }

    return ahs::Image{};
}

#include "BmpEncoder.h"

#include <fstream>

ahs::codec::BmpEncoder::~BmpEncoder() = default;

void ahs::codec::BmpEncoder::encode(const char* filename)
{
    std::ofstream ofs{ filename, std::ofstream::trunc };
    if (ofs.is_open())
    {
        if (ofs.good())
        {

        }

        ofs.close();
    }
}
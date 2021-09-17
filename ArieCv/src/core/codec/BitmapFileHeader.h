#pragma once
#include <string>

namespace ahs {
    namespace codec {
#pragma pack(push, 1)
        class BitmapFileHeader final
        {
        public:
            BitmapFileHeader();

            BitmapFileHeader(int fileSize, int offset);

            ~BitmapFileHeader();

        private:
            __int8 h1_{ 'B' };
            __int8 h2_{ 'M' };
            __int32 fileSize_{ 0 };
            __int16 reserved1_{ 0 };
            __int16 reserved2_{ 0 };
            __int32 offset_{ 0 };

        public:
            std::string getMagicNumber() const noexcept;

            int getFileSize() const noexcept;

            int getOffset() const noexcept;
        };
#pragma pack(pop)
    }
}
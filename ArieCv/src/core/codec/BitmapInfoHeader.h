#pragma once

namespace ahs {
    namespace codec {
#pragma pack(push, 1)
        class BitmapInfoHeader final
        {
        public:
            BitmapInfoHeader();

            BitmapInfoHeader(int width, int height, short bpp, int imageSize);

            ~BitmapInfoHeader();

        private:
            __int32 headerSize_{ 40 };
            __int32 width_{ 0 };
            __int32 height_{ 0 };
            __int16 numColorPlanes{ 1 };
            __int16 bpp_{ 0 };
            __int32 compression_{ 0 };
            __int32 imageSize_{ 0 };
            __int32 horizontalResolution{ 0 };
            __int32 verticalResolution{ 0 };
            __int32 numColors_{ 0 };
            __int32 numImportantColors_{ 0 };

        public:
            int getHeaderSize() const noexcept;

            int getWidth() const noexcept;

            int getHeight() const noexcept;

            int getBpp() const noexcept;

            int getNumColors() const noexcept;
        };
#pragma pack(pop)
    }
}
#pragma once
#include "../framework.h"

namespace ahs {
    class ARIECV_API Image
    {
    public:
        Image();

        Image(const ahs::Image& copy);

        Image(ahs::Image&& move) noexcept;

        virtual ~Image();

    private:
        void** rawData_{ nullptr };

        int width_{ 0 };

        int height_{ 0 };

        int numberOfChannels_{ 0 };

        int bytePerData_{ 0 };

    public:
        ahs::Image& operator=(const ahs::Image& copy);

        ahs::Image& operator=(ahs::Image&& move) noexcept;

        virtual const int& getWidth() const noexcept;

        virtual const int& getHeight() const noexcept;

        virtual char* getInterleavedData() const noexcept;

        virtual bool isInitialized() const noexcept;

        virtual int countChannels() const noexcept;

        virtual void write(const char* filename) const;

        static ahs::Image fromFile(const char* filename);

        static ahs::Image fromInterleavedBgr8(int width, int height, int stride, const __int8* data);
    };
}
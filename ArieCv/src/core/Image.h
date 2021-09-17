#pragma once
#include "../framework.h"

namespace ahs {
    class ARIECV_API Image
    {
    public:
        Image();

        Image(int width, int height, int stride, char* data);

        Image(const ahs::Image& copy);

        Image(ahs::Image&& move) noexcept;

        virtual ~Image();

    private:
        char* rawData_{ nullptr };

        int width_{ 0 };

        int height_{ 0 };

        int stride_{ 0 };

    public:
        ahs::Image& operator=(const ahs::Image& copy);

        ahs::Image& operator=(ahs::Image&& move) noexcept;

        virtual const int& getWidth() const noexcept;

        virtual const int& getHeight() const noexcept;

        virtual const int& getStride() const noexcept;

        virtual const char* getRawData() const noexcept;

        virtual bool isInitialized() const noexcept;

        virtual void write(const char* filename) const;

        static ahs::Image fromFile(const char* filename);
    };
}
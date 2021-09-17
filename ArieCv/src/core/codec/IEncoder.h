#pragma once
#include "../../framework.h"

#include "../Image.h"

namespace ahs {
    namespace codec {
        class ARIECV_API IEncoder
        {
        public:
            virtual ~IEncoder();

            virtual void encode(const ahs::Image& image, const char* filename) = 0;
        };
    }
}

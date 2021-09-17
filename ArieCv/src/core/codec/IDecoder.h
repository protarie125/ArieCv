#pragma once
#include "../../framework.h"

#include "../Image.h"

namespace ahs {
    namespace codec {
        class ARIECV_API IDecoder
        {
        public:
            virtual ~IDecoder();

            virtual ahs::Image decode(const char* filename) = 0;
        };
    }
}

#pragma once
#include "../../framework.h"

#include <string>

#include "../Image.h"

namespace ahs {
    namespace codec {
        class ARIECV_API IEncoder
        {
        public:
            virtual ~IEncoder();

            virtual void encode(const char* filename) = 0;
        };
    }
}

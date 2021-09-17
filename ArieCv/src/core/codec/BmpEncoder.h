#pragma once
#include "../../framework.h"

#include "IEncoder.h"
#include "../Image.h"

namespace ahs {
    namespace codec {
        class ARIECV_API BmpEncoder : public IEncoder
        {
        public:
            ~BmpEncoder() override;

            void encode(const ahs::Image& image, const char* filename) override;
        };
    }
}

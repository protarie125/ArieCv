#pragma once
#include "../../framework.h"

#include "IDecoder.h"

namespace ahs {
    namespace codec {
        class ARIECV_API BmpDecoder : public IDecoder
        {
        public:
            ~BmpDecoder() override;

            ahs::Image decode(const char* filename) override;
        };
    }
}

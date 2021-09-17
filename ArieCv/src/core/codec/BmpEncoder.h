#pragma once
#include "../../framework.h"

#include "IEncoder.h"

namespace ahs {
    namespace codec {
        class ARIECV_API BmpEncoder : public IEncoder
        {
        public:
            ~BmpEncoder() override;

            void encode(const char* filename) override;
        };
    }
}

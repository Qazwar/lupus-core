#pragma once

#include "Utility.h"
#include <memory>

namespace Lupus {
    namespace Net {
        struct HttpListenerContext
        {
            const std::shared_ptr<class HttpListenerRequest> Request;
            const std::shared_ptr<class HttpListenerResponse> Response;
        };
    }
}

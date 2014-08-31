#pragma once

#include "Utility.h"
#include <memory>

namespace Lupus {
    namespace Net {
        struct HttpListenerContext
        {
            const std::shared_ptr<class HttpRequest> Request;
            const std::shared_ptr<class HttpResponse> Response;
        };
    }
}

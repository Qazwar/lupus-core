#pragma once

#include "Utility.h"
#include "HttpListenerContext.h"
#include <memory>
#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Net {
        class LUPUS_API HttpListener : public boost::noncopyable
        {
        public:

            HttpListener();
            ~HttpListener();

            bool IsListening() const;

            void Abort();
            void Close();
            HttpListenerContext GetContext();
            void Start();
            void Stop();

        private:
        };
    }
}

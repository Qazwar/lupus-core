#pragma once

#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <memory>
#include <unordered_map>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class ReadStream;

    namespace Net {
        namespace Sockets {
            class IPAddress;
            class TcpClient;
        }

        namespace Http {
            class Uri;
            class Cookie;

            class SWC_API HttpRequest : boost::noncopyable
            {
            public:

                HttpRequest(std::shared_ptr<Sockets::TcpClient>) throw(socket_error);
                virtual ~HttpRequest() = default;

                /*virtual void Abort() throw(socket_error);
                virtual std::shared_ptr<ReadStream> Body() const NOEXCEPT;
                virtual const std::string& ContentType() const NOEXCEPT;
                virtual const std::unordered_map<std::string, Cookie>& Cookies() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& Form() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& Headers() const NOEXCEPT;
                virtual std::shared_ptr<Sockets::IPAddress> HostAddress() const NOEXCEPT;
                virtual const std::string& Method() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& QueryString() const NOEXCEPT;
                virtual std::shared_ptr<Uri> Url() const NOEXCEPT;

                boost::any operator[](const std::string&) const NOEXCEPT;*/

            private:

                std::shared_ptr<Sockets::TcpClient> mClient;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

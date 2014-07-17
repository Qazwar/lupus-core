#pragma once

#include <boost/any.hpp>

#include <string>
#include <unordered_map>

#include "Stream.h"

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        namespace Http {
            class Uri;
            class Cookie;

            class Request : boost::noncopyable
            {
            public:

                Request(std::shared_ptr<Sockets::TcpClient>);
                virtual ~Request() = default;

                virtual const std::string& ContentType() const NOEXCEPT;
                virtual uint32_t ContentLength() const NOEXCEPT;
                virtual const std::unordered_map<std::string, Cookie>& Cookies() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& Form() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& Headers() const NOEXCEPT;
                virtual std::shared_ptr<ReadStream> InputStream() const NOEXCEPT;
                virtual const std::string& Method() const NOEXCEPT;
                virtual const std::unordered_map<std::string, std::string>& QueryString() const NOEXCEPT;
                virtual std::shared_ptr<Uri> Url() const NOEXCEPT;

                boost::any operator[](const std::string&) const NOEXCEPT;

            private:

                std::shared_ptr<Sockets::TcpClient> mClient;
            };
        }
    }
}

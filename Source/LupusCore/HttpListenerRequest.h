#pragma once

#include "Utility.h"
#include "Task.h"
#include <vector>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <boost/noncopyable.hpp>

namespace Lupus {
    class Stream;
    class Uri;
    class Version;

    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                class X509Certificate;
            }
        }
    }

    namespace Text {
        class Encoding;
    }

    namespace Net {
        namespace Sockets {
            class IPEndPoint;
        }

        class LUPUS_API HttpListenerRequest : public boost::noncopyable
        {
        public:

            HttpListenerRequest();
            ~HttpListenerRequest();

            std::vector<std::string> AcceptTypes() const NOEXCEPT;
            std::shared_ptr<Text::Encoding> ContentEncoding() const NOEXCEPT;
            int64_t ContentLength() const NOEXCEPT;
            std::string ContentType() const NOEXCEPT;
            std::unordered_map<std::string, std::string> Cookies() const NOEXCEPT;
            bool HasEntityBody() const NOEXCEPT;
            std::unordered_map<std::string, std::string> Headers() const NOEXCEPT;
            std::string HttpMethod() const NOEXCEPT;
            std::shared_ptr<Stream> InputStream() const NOEXCEPT;
            bool IsAuntheticated() const NOEXCEPT;
            bool IsLocal() const NOEXCEPT;
            bool IsSecureConnection() const NOEXCEPT;
            bool KeepAlive() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> LocalEndPoint() const NOEXCEPT;
            std::shared_ptr<Version> ProtocolVersion() const NOEXCEPT;
            std::unordered_map<std::string, std::string> QueryString() const NOEXCEPT;
            std::string RawUrl() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> RemoteEndPoint() const NOEXCEPT;
            std::string ServiceName() const NOEXCEPT;
            std::shared_ptr<Uri> Url() const NOEXCEPT;
            std::string UserAgend() const NOEXCEPT;
            std::string UserHostAddress() const NOEXCEPT;
            std::string UserHostName() const NOEXCEPT;
            std::vector<std::string> UserLanguages() const NOEXCEPT;

            Task<std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate>> GetClientCertificateAsync() const NOEXCEPT;

            std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> GetClientCertificate() const NOEXCEPT;

        private:
        };
    }
}

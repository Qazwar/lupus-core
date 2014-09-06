#pragma once

#include "String.h"
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

            std::vector<String> AcceptTypes() const NOEXCEPT;
            std::shared_ptr<Text::Encoding> ContentEncoding() const NOEXCEPT;
            int64_t ContentLength() const NOEXCEPT;
            String ContentType() const NOEXCEPT;
            std::unordered_map<String, String> Cookies() const NOEXCEPT;
            bool HasEntityBody() const NOEXCEPT;
            std::unordered_map<String, String> Headers() const NOEXCEPT;
            String HttpMethod() const NOEXCEPT;
            std::shared_ptr<Stream> InputStream() const NOEXCEPT;
            bool IsAuntheticated() const NOEXCEPT;
            bool IsLocal() const NOEXCEPT;
            bool IsSecureConnection() const NOEXCEPT;
            bool KeepAlive() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> LocalEndPoint() const NOEXCEPT;
            std::shared_ptr<Version> ProtocolVersion() const NOEXCEPT;
            std::unordered_map<String, String> QueryString() const NOEXCEPT;
            String RawUrl() const NOEXCEPT;
            std::shared_ptr<Sockets::IPEndPoint> RemoteEndPoint() const NOEXCEPT;
            String ServiceName() const NOEXCEPT;
            std::shared_ptr<Uri> Url() const NOEXCEPT;
            String UserAgend() const NOEXCEPT;
            String UserHostAddress() const NOEXCEPT;
            String UserHostName() const NOEXCEPT;
            std::vector<String> UserLanguages() const NOEXCEPT;

            Task<std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate>> GetClientCertificateAsync() const NOEXCEPT;

            std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> GetClientCertificate() const NOEXCEPT;

        private:
        };
    }
}

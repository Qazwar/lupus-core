#pragma once

#include "String.h"
#include "Task.h"
#include <vector>
#include <memory>
#include <cstdint>
#include <unordered_map>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class Stream;
    class InputStream;
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

            HttpListenerRequest() = delete;
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
            String UserAgent() const NOEXCEPT;
            String UserHostAddress() const NOEXCEPT;
            String UserHostName() const NOEXCEPT;
            std::vector<String> UserLanguages() const NOEXCEPT;

            Task<std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate>> GetClientCertificateAsync() const NOEXCEPT;

            std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> GetClientCertificate() const NOEXCEPT;

        private:

            friend class HttpListener;

            HttpListenerRequest(
                std::shared_ptr<Lupus::InputStream> stream, 
                std::shared_ptr<Sockets::IPEndPoint> localEP, 
                std::shared_ptr<Sockets::IPEndPoint> remoteEP);

            std::shared_ptr<Lupus::InputStream> mStream;
            std::shared_ptr<Sockets::IPEndPoint> mLocalEP;
            std::shared_ptr<Sockets::IPEndPoint> mRemoteEP;
            std::shared_ptr<Uri> mUrl;
            std::shared_ptr<Version> mVersion;
            std::shared_ptr<Text::Encoding> mEncoding;
            std::unordered_map<String, String> mCookies;
            std::unordered_map<String, String> mHeaders;
            std::unordered_map<String, String> mQuery;
            std::vector<String> mAcceptedTypes;
            std::vector<String> mLanguages;
            String mContentType;
            String mMethod;
            String mServiceName;
            String mUserAgent;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

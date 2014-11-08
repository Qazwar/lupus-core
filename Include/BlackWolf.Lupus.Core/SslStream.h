#pragma once

#include "AuthenticatedStream.h"
#include "SecurityAuthEnum.h"

#include <functional>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            class SymmetricCipher;

            namespace X509Certificates {
                class X509Certificate;
            }
        }
    }

    namespace Net {
        namespace Security {
            class LUPUSCORE_API SslStream : public AuthenticatedStream
            {
            public:

                SslStream(std::shared_ptr<Stream>);
                SslStream(std::shared_ptr<Stream>, bool);
                virtual ~SslStream();

                virtual bool CanRead() const NOEXCEPT override;
                virtual bool CanWrite() const NOEXCEPT override;
                virtual bool CanSeek() const NOEXCEPT override;

                virtual void Close() override;
                virtual int64_t Length() const override;
                virtual void Length(int64_t) throw(std::out_of_range) override;
                virtual int64_t Position() const override;
                virtual void Position(int64_t) throw(std::out_of_range) override;
                virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
                virtual int ReadByte() override;
                virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
                virtual void WriteByte(uint8_t byte) override;
                virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;

                virtual bool IsAuthenticated() const override;
                virtual bool IsEncrypted() const override;
                virtual bool IsMutuallyAuthenticated() const override;
                virtual bool IsServer() const override;
                virtual bool IsSigned() const override;

                virtual bool CheckCertRevocationStatus() const NOEXCEPT;
                virtual Lupus::Security::Authentication::CipherAlgorithmType CipherAlgorithm() const NOEXCEPT;
                virtual int CipherStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::HashAlgorithmType HashAlgorithm() const NOEXCEPT;
                virtual int HashStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::ExchangeAlgorithmType KeyExchangeAlgorithm() const NOEXCEPT;
                virtual int KeyExchangeStrength() const NOEXCEPT;
                virtual Lupus::Security::Authentication::SslProtocols SslProtocol() const NOEXCEPT;

                virtual void AuthenticateAsClientAsync(const String& host, std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsClientAsync(
                    const String& host,
                    std::vector<
                        std::shared_ptr<
                            Lupus::Security::Cryptography::X509Certificates::X509Certificate
                        >
                    > certificates,
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation,
                    std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsServerAsync(std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> certificate, std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;
                virtual void AuthenticateAsServerAsync(
                    std::shared_ptr<
                        Lupus::Security::Cryptography::X509Certificates::X509Certificate
                    > certificate,
                    bool clientCertRequired,
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation,
                    std::function<void(std::exception_ptr, SslStream*)>) NOEXCEPT;

                virtual void AuthenticateAsClient(const String& host);
                virtual void AuthenticateAsClient(
                    const String& host, 
                    std::vector<
                        std::shared_ptr<
                            Lupus::Security::Cryptography::X509Certificates::X509Certificate
                        >
                    > certificates, 
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation);
                virtual void AuthenticateAsServer(std::shared_ptr<Lupus::Security::Cryptography::X509Certificates::X509Certificate> certificate);
                virtual void AuthenticateAsServer(
                    std::shared_ptr<
                        Lupus::Security::Cryptography::X509Certificates::X509Certificate
                    > certificate, 
                    bool clientCertRequired, 
                    Lupus::Security::Authentication::SslProtocols protocols,
                    bool checkRevocation);

            private:

                std::shared_ptr<Lupus::Security::Cryptography::SymmetricCipher> mCipher;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

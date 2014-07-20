#pragma once

#include "AuthenticatedStream.h"
#include "NetSecurityEnum.h"

namespace StreamWolf {
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
            class SWC_API SslStream : public AuthenticatedStream
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
                virtual int32_t Read(std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(std::out_of_range) override;
                virtual int32_t ReadByte() override;
                virtual int32_t Write(const std::vector<uint8_t>& buffer, uint32_t offset, uint32_t size) throw(std::out_of_range) override;
                virtual void WriteByte(uint8_t byte) override;
                virtual int64_t Seek(int64_t offset, SeekOrigin origin) override;

                virtual bool IsAuthenticated() const override;
                virtual bool IsEncrypted() const override;
                virtual bool IsMutuallyAuthenticated() const override;
                virtual bool IsServer() const override;
                virtual bool IsSigned() const override;

                virtual bool CheckCertRevocationStatus() const NOEXCEPT;
                virtual CipherAlgorithmType CipherAlgorithm() const NOEXCEPT;
                virtual int32_t CipherStrength() const NOEXCEPT;
                virtual HashAlgorithmType HashAlgorithm() const NOEXCEPT;
                virtual int32_t HashStrength() const NOEXCEPT;
                virtual ExchangeAlgorithmType KeyExchangeAlgorithm() const NOEXCEPT;
                virtual int32_t KeyExchangeStrength() const NOEXCEPT;
                virtual SslProtocols SslProtocol() const NOEXCEPT;

                virtual void AuthenticateAsClient(const std::string&);

            private:

                std::shared_ptr<StreamWolf::Security::Cryptography::SymmetricCipher> mCipher;
            };
        }
    }
}

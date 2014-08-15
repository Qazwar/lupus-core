#pragma once

#include "Stream.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class Socket;

            class LUPUS_API NetworkStream : public Stream
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket) throw(null_pointer);
                virtual ~NetworkStream() = default;

                virtual size_t DataAvailable() const throw(socket_error);
                virtual std::shared_ptr<Socket> Socket() const NOEXCEPT;

                virtual Task<int> ReadAsync(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::invalid_argument) override;
                virtual Task<int> WriteAsync(const std::vector<uint8_t>& buffer, size_t offset, size_t size)  throw(std::invalid_argument) override;

                virtual bool CanRead() const NOEXCEPT override;
                virtual bool CanWrite() const NOEXCEPT override;
                virtual bool CanSeek() const NOEXCEPT override;
                
                virtual void Close() throw(socket_error) override;
                virtual void Close(size_t timeout) throw(socket_error);
                virtual int64_t Position() const NOEXCEPT override;
                virtual int64_t Length() const throw(socket_error) override;
                virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(socket_error, io_error, std::out_of_range) override;
                virtual int ReadByte() throw(socket_error, io_error) override;
                virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(socket_error, io_error, std::out_of_range) override;
                virtual void WriteByte(uint8_t byte) throw(socket_error, io_error) override;

                virtual bool Readable() const NOEXCEPT;
                virtual void Readable(bool) NOEXCEPT;
                virtual bool Writable() const NOEXCEPT;
                virtual void Writable(bool) NOEXCEPT;

            private:

                std::shared_ptr<Sockets::Socket> mSocket;
                bool mRead = true;
                bool mWrite = true;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

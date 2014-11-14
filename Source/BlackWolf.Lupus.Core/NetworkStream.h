/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
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

            class LUPUSCORE_API NetworkStream : public Stream
            {
            public:

                NetworkStream(std::shared_ptr<Socket> socket) throw(null_pointer);
                virtual ~NetworkStream() = default;

                virtual size_t DataAvailable() const throw(socket_error);
                virtual std::shared_ptr<Socket> Socket() const NOEXCEPT;

                virtual Task<int> ReadAsync(std::vector<uint8_t>& buffer, size_t offset, size_t size) NOEXCEPT override;
                virtual Task<int> WriteAsync(const std::vector<uint8_t>& buffer, size_t offset, size_t size)  NOEXCEPT override;

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

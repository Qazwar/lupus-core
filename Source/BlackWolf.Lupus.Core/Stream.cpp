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
#include "Stream.h"

#include <thread>



namespace Lupus {
    Task<void> Stream::CopyToAsync(Pointer<Stream> destination)
    {
        return Task<void>([this, destination]() {
            this->CopyTo(destination);
        });
    }

    Task<void> Stream::FlushAsync() throw(InvalidArgument)
    {
        return Task<void>([this]() {
            this->Flush();
        });
    }

    Task<int> Stream::ReadAsync(Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Read(buffer, offset, size);
        });
    }

    Task<int> Stream::WriteAsync(const Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Write(buffer, offset, size);
        });
    }

    void Stream::CopyTo(Pointer<Stream> destination)
    {
        if (!destination) {
            throw NullPointer("destination");
        }

        int64_t pos = Position();
        int64_t len = Length();
        int64_t dpos = destination->Position();
        int64_t dlen = destination->Length();
        int64_t size = len - pos;
        int64_t dsize = dlen - dpos;

        if (pos < 0 || len <= 0 || size <= 0 || dpos < 0 || dlen <= 0 || dsize <= 0) {
            return;
        } else if (size > dsize) {
            destination->Length(destination->Length() + size - dsize);
        }

        Vector<uint8_t> buffer((size_t)size);
        Read(buffer, 0, (size_t)size);
        destination->Write(buffer, 0, (size_t)size);
    }

    void Stream::Flush()
    {
        throw NotSupported();
    }

    void Stream::Length(int64_t length)
    {
        throw NotSupported();
    }

    void Stream::Position(int64_t)
    {
        throw NotSupported();
    }

    int64_t Stream::Seek(int64_t offset, SeekOrigin origin)
    {
        throw NotSupported();
    }

    InputStream::InputStream(Pointer<Stream> innerStream)
    {
        if (!innerStream) {
            throw NullPointer("innerStream");
        } else if (!innerStream->CanRead()) {
            throw InvalidArgument("innerStream");
        }

        mInnerStream = innerStream;
    }

    bool InputStream::CanRead() const
    {
        return true;
    }

    bool InputStream::CanWrite() const
    {
        return false;
    }

    bool InputStream::CanSeek() const
    {
        return mInnerStream->CanSeek();
    }

    void InputStream::Close()
    {
        mInnerStream->Close();
    }

    void InputStream::CopyTo(Pointer<Stream> destination)
    {
        mInnerStream->CopyTo(destination);
    }

    void InputStream::Flush()
    {
        mInnerStream->Flush();
    }

    int64_t InputStream::Length() const
    {
        return mInnerStream->Length();
    }

    void InputStream::Length(int64_t)
    {
        throw NotSupported();
    }

    int64_t InputStream::Position() const
    {
        return mInnerStream->Position();
    }

    void InputStream::Position(int64_t pos)
    {
        mInnerStream->Position(pos);
    }

    int InputStream::Read(Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return mInnerStream->Read(buffer, offset, size);
    }

    int InputStream::ReadByte()
    {
        return mInnerStream->ReadByte();
    }

    int InputStream::Write(const Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        throw NotSupported();
    }

    void InputStream::WriteByte(uint8_t byte)
    {
        throw NotSupported();
    }

    int64_t InputStream::Seek(int64_t offset, SeekOrigin origin)
    {
        return mInnerStream->Seek(offset, origin);
    }

    OutputStream::OutputStream(Pointer<Stream> innerStream)
    {
        if (!innerStream) {
            throw NullPointer("innerStream");
        } else if (!innerStream->CanWrite()) {
            throw InvalidArgument("innerStream");
        }

        mInnerStream = innerStream;
    }

    bool OutputStream::CanRead() const
    {
        return false;
    }

    bool OutputStream::CanWrite() const
    {
        return true;
    }

    bool OutputStream::CanSeek() const
    {
        return mInnerStream->CanSeek();
    }

    void OutputStream::Close()
    {
        mInnerStream->Close();
    }

    void OutputStream::CopyTo(Pointer<Stream> destination)
    {
        mInnerStream->CopyTo(destination);
    }

    void OutputStream::Flush()
    {
        mInnerStream->Flush();
    }

    int64_t OutputStream::Length() const
    {
        return mInnerStream->Length();
    }

    void OutputStream::Length(int64_t len)
    {
        mInnerStream->Length(len);
    }

    int64_t OutputStream::Position() const
    {
        return mInnerStream->Position();
    }

    void OutputStream::Position(int64_t pos)
    {
        mInnerStream->Position(pos);
    }

    int OutputStream::Read(Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        throw NotSupported();
    }

    int OutputStream::ReadByte()
    {
        throw NotSupported();
    }

    int OutputStream::Write(const Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return mInnerStream->Write(buffer, offset, size);
    }

    void OutputStream::WriteByte(uint8_t byte)
    {
        mInnerStream->WriteByte(byte);
    }

    int64_t OutputStream::Seek(int64_t offset, SeekOrigin origin)
    {
        return mInnerStream->Seek(offset, origin);
    }
}

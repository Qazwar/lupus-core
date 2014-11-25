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

    Task<int> Stream::ReadAsync(Vector<U8>& buffer, U32 offset, U32 size)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Read(buffer, offset, size);
        });
    }

    Task<int> Stream::WriteAsync(const Vector<U8>& buffer, U32 offset, U32 size)
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

        S64 pos = Position();
        S64 len = Length();
        S64 dpos = destination->Position();
        S64 dlen = destination->Length();
        S64 size = len - pos;
        S64 dsize = dlen - dpos;

        if (pos < 0 || len <= 0 || size <= 0 || dpos < 0 || dlen <= 0 || dsize <= 0) {
            return;
        } else if (size > dsize) {
            destination->Length(destination->Length() + size - dsize);
        }

        Vector<U8> buffer((U32)size);
        Read(buffer, 0, (U32)size);
        destination->Write(buffer, 0, (U32)size);
    }

    void Stream::Flush()
    {
        throw NotSupported();
    }

    void Stream::Length(S64 length)
    {
        throw NotSupported();
    }

    void Stream::Position(S64)
    {
        throw NotSupported();
    }

    S64 Stream::Seek(S64 offset, SeekOrigin origin)
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

    S64 InputStream::Length() const
    {
        return mInnerStream->Length();
    }

    void InputStream::Length(S64)
    {
        throw NotSupported();
    }

    S64 InputStream::Position() const
    {
        return mInnerStream->Position();
    }

    void InputStream::Position(S64 pos)
    {
        mInnerStream->Position(pos);
    }

    int InputStream::Read(Vector<U8>& buffer, U32 offset, U32 size)
    {
        return mInnerStream->Read(buffer, offset, size);
    }

    int InputStream::ReadByte()
    {
        return mInnerStream->ReadByte();
    }

    int InputStream::Write(const Vector<U8>& buffer, U32 offset, U32 size)
    {
        throw NotSupported();
    }

    void InputStream::WriteByte(U8 byte)
    {
        throw NotSupported();
    }

    S64 InputStream::Seek(S64 offset, SeekOrigin origin)
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

    S64 OutputStream::Length() const
    {
        return mInnerStream->Length();
    }

    void OutputStream::Length(S64 len)
    {
        mInnerStream->Length(len);
    }

    S64 OutputStream::Position() const
    {
        return mInnerStream->Position();
    }

    void OutputStream::Position(S64 pos)
    {
        mInnerStream->Position(pos);
    }

    int OutputStream::Read(Vector<U8>& buffer, U32 offset, U32 size)
    {
        throw NotSupported();
    }

    int OutputStream::ReadByte()
    {
        throw NotSupported();
    }

    int OutputStream::Write(const Vector<U8>& buffer, U32 offset, U32 size)
    {
        return mInnerStream->Write(buffer, offset, size);
    }

    void OutputStream::WriteByte(U8 byte)
    {
        mInnerStream->WriteByte(byte);
    }

    S64 OutputStream::Seek(S64 offset, SeekOrigin origin)
    {
        return mInnerStream->Seek(offset, origin);
    }
}

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

#include <vector>
#include <memory>
#include <future>
#include <cstdint>
#include <Exception>
#include <functional>

#include "Utility.h"
#include "Task.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    enum class SeekOrigin {
        Begin,
        Current,
        End
    };

    class LUPUSCORE_API Stream : NonCopyable
    {
    public:

        virtual ~Stream() = default;

        virtual Task<void> CopyToAsync(Pointer<Stream> destination) NOEXCEPT;
        virtual Task<void> FlushAsync() NOEXCEPT;
        virtual Task<int> ReadAsync(Vector<U8>& buffer, U32 offset, U32 size) NOEXCEPT;
        virtual Task<int> WriteAsync(const Vector<U8>& buffer, U32 offset, U32 size) NOEXCEPT;

        virtual bool CanRead() const = 0;
        virtual bool CanWrite() const = 0;
        virtual bool CanSeek() const = 0;

        virtual void Close() = 0;
        virtual void CopyTo(Pointer<Stream> destination) throw(NullPointer, NotSupported);
        virtual void Flush() throw(NotSupported);
        virtual S64 Length() const = 0;
        virtual void Length(S64) throw(NotSupported);
        virtual S64 Position() const = 0;
        virtual void Position(S64) throw(NotSupported);
        virtual int Read(Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) = 0;
        virtual int ReadByte() = 0;
        virtual int Write(const Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) = 0;
        virtual void WriteByte(U8 byte) = 0;
        virtual S64 Seek(S64 offset, SeekOrigin origin) throw(NotSupported);
    };

    //! Readonly adapter
    class LUPUSCORE_API InputStream : public Stream
    {
    public:

        InputStream() = delete;
        InputStream(Pointer<Stream> innerStream) throw(InvalidArgument, NullPointer);
        virtual ~InputStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() override;
        virtual void CopyTo(Pointer<Stream> destination) throw(NullPointer, NotSupported) override;
        virtual void Flush() override;
        virtual S64 Length() const override;
        virtual void Length(S64) throw(NotSupported) override;
        virtual S64 Position() const override;
        virtual void Position(S64) throw(NotSupported) override;
        virtual int Read(Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) override;
        virtual int ReadByte() override;
        virtual int Write(const Vector<U8>& buffer, U32 offset, U32 size) throw(NotSupported) override;
        virtual void WriteByte(U8 byte) throw(NotSupported) override;
        virtual S64 Seek(S64 offset, SeekOrigin origin) override;

    private:

        Pointer<Stream> mInnerStream;
    };

    // Writeonly adapter
    class LUPUSCORE_API OutputStream : public Stream
    {
    public:

        OutputStream() = delete;
        OutputStream(Pointer<Stream> innerStream) throw(InvalidArgument, NullPointer);
        virtual ~OutputStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() override;
        virtual void CopyTo(Pointer<Stream> destination) throw(NullPointer, NotSupported) override;
        virtual void Flush() override;
        virtual S64 Length() const override;
        virtual void Length(S64) throw(NotSupported) override;
        virtual S64 Position() const override;
        virtual void Position(S64) throw(NotSupported) override;
        virtual int Read(Vector<U8>& buffer, U32 offset, U32 size) throw(OutOfRange) override;
        virtual int ReadByte() override;
        virtual int Write(const Vector<U8>& buffer, U32 offset, U32 size) throw(NotSupported) override;
        virtual void WriteByte(U8 byte) throw(NotSupported) override;
        virtual S64 Seek(S64 offset, SeekOrigin origin) override;

    private:

        Pointer<Stream> mInnerStream;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

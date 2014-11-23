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
#pragma once

#include "Stream.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUSCORE_API MemoryStream : public Stream
    {
    public:

        MemoryStream() = default;
        MemoryStream(const Vector<uint8_t>&) NOEXCEPT;
        MemoryStream(size_t size) NOEXCEPT;
        MemoryStream(const Vector<uint8_t>&, bool writable) NOEXCEPT;
        MemoryStream(const Vector<uint8_t>&, size_t offset, size_t size) throw(OutOfRange);
        MemoryStream(const Vector<uint8_t>&, size_t offset, size_t size, bool writable) throw(OutOfRange);
        MemoryStream(const Vector<uint8_t>&, size_t offset, size_t size, bool writable, bool visible) throw(OutOfRange);
        virtual ~MemoryStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() NOEXCEPT override;
        virtual int64_t Length() const NOEXCEPT override;
        virtual void Length(int64_t) NOEXCEPT override;
        virtual int64_t Position() const NOEXCEPT override;
        virtual void Position(int64_t) NOEXCEPT override;
        virtual int Read(Vector<uint8_t>& buffer, size_t offset, size_t size) throw(OutOfRange) override;
        virtual int ReadByte() NOEXCEPT override;
        virtual int Write(const Vector<uint8_t>& buffer, size_t offset, size_t size) throw(NotSupported, OutOfRange) override;
        virtual void WriteByte(uint8_t byte) throw(NotSupported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) NOEXCEPT override;

        virtual size_t Capacity() const;
        virtual void Capacity(size_t);
        virtual const Vector<uint8_t>& GetBuffer() const throw(UnauthorizedAccess);

        virtual uint8_t& operator[](size_t);
        virtual const uint8_t& operator[](size_t) const;

    private:

        bool mWritable = true;
        bool mVisible = true;
        Vector<uint8_t> mBuffer;
        Vector<uint8_t>::iterator mIterator;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

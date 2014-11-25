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
#include "MemoryStream.h"
#include <iterator>

namespace Lupus {
    MemoryStream::MemoryStream(const Vector<U8>& buffer)
    {
        mBuffer = buffer;
        mIterator = Begin(mBuffer);
    }

    MemoryStream::MemoryStream(U32 length)
    {
        mBuffer = Vector<U8>(length);
        mIterator = Begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<U8>& buffer, bool canWrite)
    {
        mBuffer = buffer;
        mWritable = canWrite;
        mIterator = Begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<U8>& buffer, U32 offset, U32 size)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mBuffer = Vector<U8>(Begin(buffer) + offset, Begin(buffer) + offset + size);
        mIterator = Begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<U8>& buffer, U32 offset, U32 size, bool canWrite)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mWritable = canWrite;
        mBuffer = Vector<U8>(Begin(buffer) + offset, Begin(buffer) + offset + size);
        mIterator = Begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<U8>& buffer, U32 offset, U32 size, bool canWrite, bool visible)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mVisible = visible;
        mWritable = canWrite;
        mBuffer = Vector<U8>(Begin(buffer) + offset, Begin(buffer) + offset + size);
        mIterator = Begin(mBuffer);
    }

    bool MemoryStream::CanRead() const
    {
        return true;
    }

    bool MemoryStream::CanWrite() const
    {
        return mWritable;
    }

    bool MemoryStream::CanSeek() const
    {
        return true;
    }

    void MemoryStream::Close()
    {
        mBuffer.clear();
        mIterator = Begin(mBuffer);
    }

    S64 MemoryStream::Length() const
    {
        return (S64)mBuffer.size();
    }

    void MemoryStream::Length(S64 length)
    {
        mBuffer.resize((U32)length);
    }

    S64 MemoryStream::Position() const
    {
        return (S64)(mIterator - Begin(mBuffer));
    }

    void MemoryStream::Position(S64 position)
    {
        advance((mIterator = Begin(mBuffer)), (int)position);
    }

    int MemoryStream::Read(Vector<U8>& buffer, U32 offset, U32 size)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        } else if (mIterator >= End(mBuffer) || mIterator < Begin(mBuffer)) {
            return 0;
        } else if ((S64)size > (S64)mBuffer.size() - Position()) {
            size = (U32)((S64)mBuffer.size() - Position());
        }

        copy(mIterator, mIterator + size, Begin(buffer) + offset + size);
        advance(mIterator, size);
        return (int)size;
    }

    int MemoryStream::ReadByte()
    {
        if (End(mBuffer) <= mIterator || Begin(mBuffer) > mIterator) {
            return -1;
        }

        return *(mIterator++);
    }

    int MemoryStream::Write(const Vector<U8>& buffer, U32 offset, U32 size)
    {
        if (!mWritable) {
            throw NotSupported();
        } else if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        } else if (mIterator > End(mBuffer) || mIterator < Begin(mBuffer)) {
            return 0;
        } else if (size >(U32)mBuffer.capacity()) {
            mBuffer.reserve(mBuffer.capacity() + (size > 1024 ? (size / 1024 + 1) * 1024 : 1024));
        }

        mBuffer.insert(mIterator, Begin(buffer) + offset, Begin(buffer) + offset + size);
        mIterator += size;
        return (int)size;
    }

    void MemoryStream::WriteByte(U8 byte)
    {
        if (!mWritable) {
            throw NotSupported();
        } else if (mIterator == End(mBuffer)) {
            mBuffer.push_back(byte);
            mIterator++;
        } else if (mIterator < End(mBuffer) && mIterator >= Begin(mBuffer)) {
            *mIterator = byte;
        }
    }

    S64 MemoryStream::Seek(S64 offset, SeekOrigin origin)
    {
        switch (origin) {
            case SeekOrigin::Begin:
                advance((mIterator = Begin(mBuffer)), static_cast<Vector<U8>::difference_type>(offset));
                break;

            case SeekOrigin::Current:
                mIterator += static_cast<Vector<U8>::difference_type>(offset);
                break;

            case SeekOrigin::End:
                advance((mIterator = End(mBuffer)), static_cast<Vector<U8>::difference_type>(offset));
                break;
        }

        return Position();
    }

    U32 MemoryStream::Capacity() const
    {
        return (U32)mBuffer.capacity();
    }

    void MemoryStream::Capacity(U32 cap)
    {
        mBuffer.reserve(cap);
    }

    const Vector<U8>& MemoryStream::GetBuffer() const
    {
        if (!mVisible) {
            throw UnauthorizedAccess();
        }

        return mBuffer;
    }

    U8& MemoryStream::operator[](U32 i)
    {
        return mBuffer[i];
    }
    
    const U8& MemoryStream::operator[](U32 i) const
    {
        return mBuffer[i];
    }
}

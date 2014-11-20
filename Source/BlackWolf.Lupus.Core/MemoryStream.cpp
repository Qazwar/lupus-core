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
    MemoryStream::MemoryStream(const Vector<uint8_t>& buffer)
    {
        mBuffer = buffer;
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(size_t length)
    {
        mBuffer = Vector<uint8_t>(length);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<uint8_t>& buffer, bool canWrite)
    {
        mBuffer = buffer;
        mWritable = canWrite;
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mBuffer = Vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<uint8_t>& buffer, size_t offset, size_t size, bool canWrite)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mWritable = canWrite;
        mBuffer = Vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const Vector<uint8_t>& buffer, size_t offset, size_t size, bool canWrite, bool visible)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        }

        mVisible = visible;
        mWritable = canWrite;
        mBuffer = Vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
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
        mIterator = begin(mBuffer);
    }

    int64_t MemoryStream::Length() const
    {
        return (int64_t)mBuffer.size();
    }

    void MemoryStream::Length(int64_t length)
    {
        mBuffer.resize((size_t)length);
    }

    int64_t MemoryStream::Position() const
    {
        return (int64_t)(mIterator - begin(mBuffer));
    }

    void MemoryStream::Position(int64_t position)
    {
        advance((mIterator = begin(mBuffer)), (int)position);
    }

    int MemoryStream::Read(Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        } else if (mIterator >= end(mBuffer) || mIterator < begin(mBuffer)) {
            return 0;
        } else if ((int64_t)size > (int64_t)mBuffer.size() - Position()) {
            size = (size_t)((int64_t)mBuffer.size() - Position());
        }

        copy(mIterator, mIterator + size, begin(buffer) + offset + size);
        advance(mIterator, size);
        return (int)size;
    }

    int MemoryStream::ReadByte()
    {
        if (end(mBuffer) <= mIterator || begin(mBuffer) > mIterator) {
            return -1;
        }

        return *(mIterator++);
    }

    int MemoryStream::Write(const Vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (!mWritable) {
            throw NotSupported();
        } else if (offset > buffer.size()) {
            throw OutOfRange("offset");
        } else if (size > buffer.size() - offset) {
            throw OutOfRange("size");
        } else if (mIterator > end(mBuffer) || mIterator < begin(mBuffer)) {
            return 0;
        } else if (size >(size_t)mBuffer.capacity()) {
            mBuffer.reserve(mBuffer.capacity() + (size > 1024 ? (size / 1024 + 1) * 1024 : 1024));
        }

        mBuffer.insert(mIterator, begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator += size;
        return (int)size;
    }

    void MemoryStream::WriteByte(uint8_t byte)
    {
        if (!mWritable) {
            throw NotSupported();
        } else if (mIterator == end(mBuffer)) {
            mBuffer.push_back(byte);
            mIterator++;
        } else if (mIterator < end(mBuffer) && mIterator >= begin(mBuffer)) {
            *mIterator = byte;
        }
    }

    int64_t MemoryStream::Seek(int64_t offset, SeekOrigin origin)
    {
        switch (origin) {
            case SeekOrigin::Begin:
                advance((mIterator = begin(mBuffer)), offset);
                break;

            case SeekOrigin::Current:
                mIterator += offset;
                break;

            case SeekOrigin::End:
                advance((mIterator = end(mBuffer)), offset);
                break;
        }

        return Position();
    }

    size_t MemoryStream::Capacity() const
    {
        return (size_t)mBuffer.capacity();
    }

    void MemoryStream::Capacity(size_t cap)
    {
        mBuffer.reserve(cap);
    }

    const Vector<uint8_t>& MemoryStream::GetBuffer() const
    {
        if (!mVisible) {
            throw UnauthorizedAccess();
        }

        return mBuffer;
    }

    uint8_t& MemoryStream::operator[](size_t i)
    {
        return mBuffer[i];
    }
    
    const uint8_t& MemoryStream::operator[](size_t i) const
    {
        return mBuffer[i];
    }
}

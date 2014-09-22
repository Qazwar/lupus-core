#include "MemoryStream.h"

#include <iterator>

using namespace std;

namespace Lupus {
    MemoryStream::MemoryStream(const vector<uint8_t>& buffer)
    {
        mBuffer = buffer;
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(size_t length)
    {
        mBuffer = vector<uint8_t>(length);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, bool canWrite)
    {
        mBuffer = buffer;
        mWritable = canWrite;
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mBuffer = vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, size_t offset, size_t size, bool canWrite)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mWritable = canWrite;
        mBuffer = vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, size_t offset, size_t size, bool canWrite, bool visible)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mVisible = visible;
        mWritable = canWrite;
        mBuffer = vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
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

    int MemoryStream::Read(vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
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

    int MemoryStream::Write(const vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        if (!mWritable) {
            throw not_supported();
        } else if (mIterator > end(mBuffer) || mIterator < begin(mBuffer)) {
            return 0;
        } else if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        } else if (size > (size_t)mBuffer.capacity()) {
            mBuffer.reserve(mBuffer.capacity() + (size > 1024 ? (size / 1024 + 1) * 1024 : 1024));
        }

        mBuffer.insert(mIterator, begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator += size;
        return (int)size;
    }

    void MemoryStream::WriteByte(uint8_t byte)
    {
        if (!mWritable) {
            throw not_supported();
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

    const vector<uint8_t>& MemoryStream::GetBuffer() const
    {
        if (!mVisible) {
            throw unauthorized_access();
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

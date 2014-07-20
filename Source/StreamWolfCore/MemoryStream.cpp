#include "MemoryStream.h"

#include <iterator>

using namespace std;

namespace StreamWolf {
    MemoryStream::MemoryStream(const vector<uint8_t>& buffer)
    {
        mBuffer = buffer;
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(uint32_t length)
    {
        mBuffer = vector<uint8_t>(length);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, bool canWrite)
    {
        mBuffer = buffer;
        mIterator = begin(mBuffer);
        mWritable = canWrite;
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mBuffer = vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size, bool canWrite)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mBuffer = buffer;
        mBuffer = vector<uint8_t>(begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = begin(mBuffer);
    }

    MemoryStream::MemoryStream(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size, bool canWrite, bool visible)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mBuffer = buffer;
        mVisible = visible;
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
        if (length < 0) {
            throw out_of_range("length must be at least zero");
        }

        mBuffer.resize(length);
    }

    int64_t MemoryStream::Position() const
    {
        return (int64_t)(mIterator - begin(mBuffer));
    }

    void MemoryStream::Position(int64_t position)
    {
        if (position < 0 || position > (int64_t)mBuffer.size()) {
            throw out_of_range("position exceeds stream boundaries");
        }

        advance((mIterator = begin(mBuffer)), position);
    }

    int32_t MemoryStream::Read(vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
    {
        if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        } else if (mIterator >= end(mBuffer)) {
            return 0;
        } else if ((int64_t)size > (int64_t)mBuffer.size() - Position()) {
            size = (uint32_t)((int64_t)mBuffer.size() - Position());
        }

        copy(mIterator, mIterator + size, begin(buffer) + offset + size);
        advance(mIterator, size);
        return (int32_t)size;
    }

    int32_t MemoryStream::ReadByte()
    {
        if (end(mBuffer) <= mIterator) {
            return -1;
        }

        return *(mIterator++);
    }

    int32_t MemoryStream::Write(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
    {
        if (!mWritable) {
            throw not_supported();
        } else if (offset > buffer.size() || size > buffer.size() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        } else if (size > (uint32_t)mBuffer.capacity()) {
            mBuffer.reserve(mBuffer.capacity() + (size > 1024 ? size : 1024));
        }

        mBuffer.insert(mBuffer.end(), begin(buffer) + offset, begin(buffer) + offset + size);
        mIterator = end(mBuffer);
        return (int32_t)size;
    }

    void MemoryStream::WriteByte(uint8_t byte)
    {
        if (!mWritable) {
            throw not_supported();
        }

        mBuffer.push_back(byte);
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

    uint32_t MemoryStream::Capacity() const
    {
        return (uint32_t)mBuffer.capacity();
    }

    void MemoryStream::Capacity(uint32_t cap)
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

    uint8_t& MemoryStream::operator[](uint32_t i)
    {
        return mBuffer[i];
    }
    
    const uint8_t& MemoryStream::operator[](uint32_t i) const
    {
        return mBuffer[i];
    }
}

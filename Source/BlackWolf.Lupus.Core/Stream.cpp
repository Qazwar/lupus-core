/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#include "Stream.h"

#include <thread>

using namespace std;

namespace Lupus {
    Task<void> Stream::CopyToAsync(shared_ptr<Stream> destination)
    {
        return Task<void>([this, destination]() {
            this->CopyTo(destination);
        });
    }

    Task<void> Stream::FlushAsync() throw(std::invalid_argument)
    {
        return Task<void>([this]() {
            this->Flush();
        });
    }

    Task<int> Stream::ReadAsync(vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Read(buffer, offset, size);
        });
    }

    Task<int> Stream::WriteAsync(const vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Write(buffer, offset, size);
        });
    }

    void Stream::CopyTo(shared_ptr<Stream> destination)
    {
        if (!destination) {
            throw null_pointer("destination");
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

        vector<uint8_t> buffer((size_t)size);
        Read(buffer, 0, (size_t)size);
        destination->Write(buffer, 0, (size_t)size);
    }

    void Stream::Flush()
    {
        throw not_supported();
    }

    void Stream::Length(int64_t length)
    {
        throw not_supported();
    }

    void Stream::Position(int64_t)
    {
        throw not_supported();
    }

    int64_t Stream::Seek(int64_t offset, SeekOrigin origin)
    {
        throw not_supported();
    }

    InputStream::InputStream(shared_ptr<Stream> innerStream)
    {
        if (!innerStream) {
            throw null_pointer("innerStream");
        } else if (!innerStream->CanRead()) {
            throw invalid_argument("innerStream");
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

    void InputStream::CopyTo(std::shared_ptr<Stream> destination)
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
        throw not_supported();
    }

    int64_t InputStream::Position() const
    {
        return mInnerStream->Position();
    }

    void InputStream::Position(int64_t pos)
    {
        mInnerStream->Position(pos);
    }

    int InputStream::Read(std::vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        return mInnerStream->Read(buffer, offset, size);
    }

    int InputStream::ReadByte()
    {
        return mInnerStream->ReadByte();
    }

    int InputStream::Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        throw not_supported();
    }

    void InputStream::WriteByte(uint8_t byte)
    {
        throw not_supported();
    }

    int64_t InputStream::Seek(int64_t offset, SeekOrigin origin)
    {
        return mInnerStream->Seek(offset, origin);
    }

    OutputStream::OutputStream(shared_ptr<Stream> innerStream)
    {
        if (!innerStream) {
            throw null_pointer("innerStream");
        } else if (!innerStream->CanWrite()) {
            throw invalid_argument("innerStream");
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

    void OutputStream::CopyTo(std::shared_ptr<Stream> destination)
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

    int OutputStream::Read(std::vector<uint8_t>& buffer, size_t offset, size_t size)
    {
        throw not_supported();
    }

    int OutputStream::ReadByte()
    {
        throw not_supported();
    }

    int OutputStream::Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size)
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

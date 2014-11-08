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
        MemoryStream(const std::vector<uint8_t>&) NOEXCEPT;
        MemoryStream(size_t size) NOEXCEPT;
        MemoryStream(const std::vector<uint8_t>&, bool writable) NOEXCEPT;
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size) throw(std::out_of_range);
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size, bool writable) throw(std::out_of_range);
        MemoryStream(const std::vector<uint8_t>&, size_t offset, size_t size, bool writable, bool visible) throw(std::out_of_range);
        virtual ~MemoryStream() = default;

        virtual bool CanRead() const NOEXCEPT override;
        virtual bool CanWrite() const NOEXCEPT override;
        virtual bool CanSeek() const NOEXCEPT override;

        virtual void Close() NOEXCEPT override;
        virtual int64_t Length() const NOEXCEPT override;
        virtual void Length(int64_t) NOEXCEPT override;
        virtual int64_t Position() const NOEXCEPT override;
        virtual void Position(int64_t) NOEXCEPT override;
        virtual int Read(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::out_of_range) override;
        virtual int ReadByte() NOEXCEPT override;
        virtual int Write(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(not_supported, std::out_of_range) override;
        virtual void WriteByte(uint8_t byte) throw(not_supported) override;
        virtual int64_t Seek(int64_t offset, SeekOrigin origin) NOEXCEPT override;

        virtual size_t Capacity() const;
        virtual void Capacity(size_t);
        virtual const std::vector<uint8_t>& GetBuffer() const throw(unauthorized_access);

        virtual uint8_t& operator[](size_t);
        virtual const uint8_t& operator[](size_t) const;

    private:

        bool mWritable = true;
        bool mVisible = true;
        std::vector<uint8_t> mBuffer;
        std::vector<uint8_t>::iterator mIterator;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

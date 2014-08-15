#include "Stream.h"

#include <thread>

using namespace std;

namespace Lupus {
    Task<void> Stream::CopyToAsync(shared_ptr<Stream> destination) throw(std::invalid_argument)
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

    Task<int> Stream::ReadAsync(vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::invalid_argument)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Read(buffer, offset, size);
        });
    }

    Task<int> Stream::WriteAsync(const vector<uint8_t>& buffer, size_t offset, size_t size) throw(std::invalid_argument)
    {
        return Task<int>([this, &buffer, offset, size]() {
            return this->Write(buffer, offset, size);
        });
    }

    void Stream::CopyTo(shared_ptr<Stream> destination)
    {
        if (!destination) {
            throw null_pointer();
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
}

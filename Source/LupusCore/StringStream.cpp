#include "StringStream.h"

using namespace std;

namespace Lupus {
    namespace IO {
        StringStream::StringStream(String str) :
            mString(str)
        {
        }

        bool StringStream::CanRead() const 
        {
            return true;
        }
        
        bool StringStream::CanWrite() const 
        {
            return true;
        }
        
        bool StringStream::CanSeek() const 
        {
            return true;
        }

        void StringStream::Close() 
        {
            throw not_supported();
        }
        
        int64_t StringStream::Length() const 
        {
            return mString.Length();
        }
        
        void StringStream::Length(int64_t length) 
        {
            if (length < mString.Length()) {
                mString = mString.Substring(0, length);
            } else {
                for (size_t i = mString.Length(); i < length; i++) {
                    mString += 0;
                }
            }
        }
        
        int64_t StringStream::Position() const 
        {
            return mPosition - begin(mString);
        }
        
        void StringStream::Position(int64_t pos)
        {
            advance((mPosition = begin(mString)), pos);
        }
        
        int StringStream::Read(vector<uint8_t>& buffer, size_t offset, size_t size) 
        {
            if (offset > buffer.size() || size > buffer.size() - offset) {
                throw out_of_range("offset and size does not match buffer size");
            }

            int n = 0;
            auto it = begin(buffer);
            auto ite = begin(buffer);
            advance(it, offset);
            advance(ite, offset + size);

            for (; it != ite; it++, n++) {
                if (mPosition >= end(mString)) {
                    break;
                }

                *it = *(mPosition++);
            }

            return n;
        }
        
        int StringStream::ReadByte() 
        {
            if (mPosition >= end(mString)) {
                return -1;
            } else {
                return *mPosition;
            }
        }
        
        int StringStream::Write(const vector<uint8_t>& buffer, size_t offset, size_t size) 
        {
            if (offset > buffer.size() || size > buffer.size() - offset) {
                throw out_of_range("offset and size does not match buffer size");
            } else if (size > mPosition - begin(mString)) {
                Length(Length() + size);
            }

            int n = 0;
            auto it = begin(buffer);
            auto ite = begin(buffer);
            advance(it, offset);
            advance(ite, offset + size);

            for (; it != ite; it++, n++) {
                *(mPosition++) = *it;
            }

            return n;
        }
        
        void StringStream::WriteByte(uint8_t byte) 
        {
            if (mPosition >= end(mString)) {
                Length(Length() + 1024);
            }

            mString += byte;
        }
        
        int64_t StringStream::Seek(int64_t offset, SeekOrigin origin) 
        {
            switch (origin) {
                case SeekOrigin::Begin:
                    advance((mPosition = begin(mString)), offset);
                    break;

                case SeekOrigin::Current:
                    mPosition += offset;
                    break;

                case SeekOrigin::End:
                    advance((mPosition = end(mString)), offset);
                    break;
            }

            return Position();
        }
    }
}

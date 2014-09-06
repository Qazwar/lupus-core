#pragma once

#include "Utility.h"
#include <vector>
#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Text {
        class LUPUS_API Encoding : public boost::noncopyable
        {
        public:

            virtual String GetString(const std::vector<uint8_t>& buffer) const NOEXCEPT;
            virtual String GetString(
                const std::vector<uint8_t>& buffer, 
                size_t offset, size_t count) const NOEXCEPT;

            static std::shared_ptr<Encoding> ASCII() NOEXCEPT;
            static std::shared_ptr<Encoding> Default() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF32() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF16() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF8() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF7() NOEXCEPT;

            static std::vector<uint8_t> Convert(
                std::shared_ptr<Encoding> src,
                std::shared_ptr<Encoding> dst,
                const std::vector<uint8_t>& buffer);

            static std::vector<uint8_t> Convert(
                std::shared_ptr<Encoding> src,
                std::shared_ptr<Encoding> dst,
                const std::vector<uint8_t>& buffer,
                size_t offset, size_t count);

        protected:

            Encoding();
            Encoding(int32_t codePage);
            virtual ~Encoding();
        };
    }
}

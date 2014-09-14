#pragma once

#include "String.h"
#include "IClonable.h"
#include "EncodingEnum.h"
#include <vector>
#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Text {
        class LUPUS_API Encoding : public boost::noncopyable, public IClonable<Encoding>
        {
        public:

            Encoding(EncodingType = EncodingType::Default) throw(std::runtime_error);
            virtual ~Encoding();

            virtual std::shared_ptr<Encoding> Clone() const NOEXCEPT override;

            virtual String GetString(const std::vector<uint8_t>& buffer) const throw(format_error, std::runtime_error);
            virtual String GetString(
                const std::vector<uint8_t>& buffer,
                size_t offset, size_t count) const throw(format_error, std::runtime_error);
            virtual std::vector<uint8_t> GetBytes(const String& str) const throw(format_error, std::runtime_error);
            virtual std::vector<uint8_t> GetBytes(
                const String& str,
                size_t offset, size_t count) const throw(format_error, std::runtime_error);
            virtual EncodingType Type() const NOEXCEPT;

            static std::shared_ptr<Encoding> ASCII() NOEXCEPT;
            static std::shared_ptr<Encoding> Default() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF32() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF16() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF8() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF7() NOEXCEPT;

        private:

            UConverter* mConverter = nullptr;
            EncodingType mType = EncodingType::Default;
        };
    }
}

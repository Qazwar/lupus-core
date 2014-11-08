#pragma once

#include "String.h"
#include "IClonable.h"
#include <vector>
#include <boost/noncopyable.hpp>
#include <unicode/ucnv.h>

namespace Lupus {
    namespace Text {
        class LUPUSCORE_API Encoding : public boost::noncopyable, public IClonable<Encoding>
        {
        public:

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
            virtual String Name() const NOEXCEPT;

            static std::shared_ptr<Encoding> ASCII() NOEXCEPT;
            static std::shared_ptr<Encoding> Default() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF32() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF16() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF8() NOEXCEPT;
            static std::shared_ptr<Encoding> UTF7() NOEXCEPT;

            static std::shared_ptr<Encoding> GetEncoding(String encoding) NOEXCEPT;
            static std::vector<String> GetEncodings() NOEXCEPT;

        private:

            Encoding(String str) throw(std::runtime_error);

            UConverter* mConverter = nullptr;
        };
    }
}

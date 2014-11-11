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

#include "String.h"
#include "IClonable.h"
#include <vector>

namespace Lupus {
    namespace Text {
        class LUPUSCORE_API Encoding : public NonCopyable, public IClonable<Encoding>
        {
        public:

            Encoding(String str) throw(std::runtime_error);
            virtual ~Encoding();

            virtual std::shared_ptr<Encoding> Clone() const NOEXCEPT override;

            virtual String GetString(const std::vector<uint8_t>& buffer) const throw(format_error, std::runtime_error);
            virtual String GetString(
                const std::vector<uint8_t>& buffer,
                size_t offset, size_t count) const throw(format_error, std::runtime_error, std::out_of_range);
            virtual std::vector<uint8_t> GetBytes(const String& str) const throw(format_error, std::runtime_error);
            virtual std::vector<uint8_t> GetBytes(
                const String& str,
                size_t offset, size_t count) const throw(format_error, std::runtime_error, std::out_of_range);
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

            void* mConverter = nullptr;
        };
    }
}

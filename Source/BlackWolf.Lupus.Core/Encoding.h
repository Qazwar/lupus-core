/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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

            Encoding(String str) throw(RuntimeError);
            virtual ~Encoding();

            virtual Pointer<Encoding> Clone() const NOEXCEPT override;

            virtual String GetString(const Vector<uint8_t>& buffer) const throw(FormatError, RuntimeError);
            virtual String GetString(
                const Vector<uint8_t>& buffer,
                size_t offset, size_t count) const throw(FormatError, RuntimeError, OutOfRange);
            virtual Vector<uint8_t> GetBytes(const String& str) const throw(FormatError, RuntimeError);
            virtual Vector<uint8_t> GetBytes(
                const String& str,
                size_t offset, size_t count) const throw(FormatError, RuntimeError, OutOfRange);
            virtual String Name() const NOEXCEPT;

            static Pointer<Encoding> ASCII() NOEXCEPT;
            static Pointer<Encoding> Default() NOEXCEPT;
            static Pointer<Encoding> UTF32() NOEXCEPT;
            static Pointer<Encoding> UTF16() NOEXCEPT;
            static Pointer<Encoding> UTF8() NOEXCEPT;
            static Pointer<Encoding> UTF7() NOEXCEPT;

            static Pointer<Encoding> GetEncoding(String encoding) NOEXCEPT;
            static Vector<String> GetEncodings() NOEXCEPT;

        private:

            void* mConverter = nullptr;
        };
    }
}

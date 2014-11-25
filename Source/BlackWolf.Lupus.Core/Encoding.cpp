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
#include "Encoding.h"
#include <unicode/ucnv.h>



namespace Lupus {
    namespace Text {
        Pointer<Encoding> Encoding::ASCII()
        {
            return Pointer<Encoding>(new Encoding("US-ASCII"));
        }
        
        Pointer<Encoding> Encoding::Default()
        {
            return Pointer<Encoding>(new Encoding(""));
        }

        Pointer<Encoding> Encoding::UTF32()
        {
            return Pointer<Encoding>(new Encoding("UTF-32"));
        }

        Pointer<Encoding> Encoding::Unicode()
        {
            return Pointer<Encoding>(new Encoding("UTF-16"));
        }

        Pointer<Encoding> Encoding::UTF8()
        {
            return Pointer<Encoding>(new Encoding("UTF-8"));
        }

        Pointer<Encoding> Encoding::UTF7()
        {
            return Pointer<Encoding>(new Encoding("UTF-7"));
        }

        Encoding::Encoding(String str)
        {
            UErrorCode error = U_ZERO_ERROR;
            
            if (str.IsEmpty()) {
                mConverter = ucnv_openU(NULL, &error);
            } else {
                mConverter = ucnv_openU(str.Data(), &error);
            }

            if (error != U_ZERO_ERROR) {
                if (mConverter) {
                    ucnv_close((UConverter*)mConverter);
                    mConverter = nullptr;
                }

                throw RuntimeError("Could not create converter.");
            }
        }

        Encoding::~Encoding()
        {
            if (mConverter) {
                ucnv_close((UConverter*)mConverter);
                mConverter = nullptr;
            }
        }

        Pointer<Encoding> Encoding::Clone() const
        {
            return GetEncoding(Name());
        }

        String Encoding::GetString(const Vector<U8>& buffer) const
        {
            return GetString(buffer, 0, buffer.size());
        }

        String Encoding::GetString(const Vector<U8>& buffer, U32 offset, U32 size) const
        {
            if (offset > buffer.size()) {
                throw OutOfRange("offset");
            } else if (size > buffer.size() - offset) {
                throw OutOfRange("size");
            }

            UErrorCode error = U_ZERO_ERROR;
            S32 length = (S32)size * 4;
            UChar* dest = new UChar[length + 1];
            memset(dest, 0, length + 1);

            S32 outLength = ucnv_toUChars((UConverter*)mConverter, dest, length, (const char*)buffer.data() + offset, (S32)size, &error);

            if (error != U_ZERO_ERROR) {
                delete dest;

                switch (error) {
                    case U_INDEX_OUTOFBOUNDS_ERROR:
                        throw FormatError("Source data does not produce an Unicode character.");

                    case U_INVALID_CHAR_FOUND:
                        throw FormatError("No mapping was found from source to target encoding.");

                    case U_TRUNCATED_CHAR_FOUND:
                        throw FormatError("A character sequence was incomplete.");

                    case U_ILLEGAL_CHAR_FOUND:
                        throw FormatError("A character was found which is disallowed in the source encoding.");

                    case U_INVALID_TABLE_FORMAT:
                        throw FormatError("An error occured trying to read the backing data for the converter.");

                    case U_BUFFER_OVERFLOW_ERROR:
                        throw FormatError("More output characters were produced than fit in the target buffer.");

                    default:
                        throw RuntimeError("Could not convert buffer to string.");
                }
            }

            String result(dest);
            delete dest;
            return result;
        }

        Vector<U8> Encoding::GetBytes(const String& str) const
        {
            return GetBytes(str, 0, str.Length());
        }

        Vector<U8> Encoding::GetBytes(const String& str, U32 offset, U32 size) const
        {
            if (offset > str.Length()) {
                throw OutOfRange("offset");
            } else if (size > str.Length() - offset) {
                throw OutOfRange("size");
            }
            
            UErrorCode error = U_ZERO_ERROR;
            S32 length = UCNV_GET_MAX_BYTES_FOR_STRING(str.Length(), ucnv_getMaxCharSize((UConverter*)mConverter));
            char* dest = new char[length];
            memset(dest, 0, length);

            S32 outLength = ucnv_fromUChars((UConverter*)mConverter, dest, length, str.Data(), (S32)str.Length(), &error);

            if (error != U_ZERO_ERROR) {
                delete dest;

                switch (error) {
                    case U_INDEX_OUTOFBOUNDS_ERROR:
                        throw FormatError("Source data does not produce an Unicode character.");

                    case U_INVALID_CHAR_FOUND:
                        throw FormatError("No mapping was found from source to target encoding.");

                    case U_TRUNCATED_CHAR_FOUND:
                        throw FormatError("A character sequence was incomplete.");

                    case U_ILLEGAL_CHAR_FOUND:
                        throw FormatError("A character was found which is disallowed in the source encoding.");

                    case U_INVALID_TABLE_FORMAT:
                        throw FormatError("An error occured trying to read the backing data for the converter.");

                    case U_BUFFER_OVERFLOW_ERROR:
                        throw FormatError("More output characters were produced than fit in the target buffer.");

                    default:
                        throw RuntimeError("Could not convert buffer to string.");
                }
            }

            Vector<U8> result((U8*)dest, (U8*)dest + outLength);
            delete dest;
            return result;
        }

        String Encoding::Name() const
        {
            UErrorCode error = U_ZERO_ERROR;
            const char* result = ucnv_getName((UConverter*)mConverter, &error);

            if (error != U_ZERO_ERROR) {
                return "invalid converter";
            } else {
                return result;
            }
        }

        Pointer<Encoding> Encoding::GetEncoding(String encoding)
        {
            try {
                return Pointer<Encoding>(new Encoding(encoding));
            } catch (RuntimeError&) {
                return nullptr;
            }
        }

        Vector<String> Encoding::GetEncodings()
        {
            Vector<String> result;
            S32 count = ucnv_countAvailable();

            for (S32 i = 0; i < count; i++) {
                result.push_back(ucnv_getAvailableName(i));
            }

            return result;
        }
    }
}

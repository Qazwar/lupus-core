#pragma once

#include <unicode/ucnv.h>

namespace Lupus{
    namespace Text {
        enum class EncodingType {
            Default,
            UTF7,
            UTF8,
            UTF16,
            UTF16LE,
            UTF16BE,
            UTF32,
            UTF32LE,
            UTF32BE,
            ASCII
        };

        /*enum class EncodingConvertError {
            IndexOutOfBounds = U_INDEX_OUTOFBOUNDS_ERROR,
            InvalidCharFound = U_INVALID_CHAR_FOUND,
            TruncatedCharFound = U_TRUNCATED_CHAR_FOUND,
            IllegalCharFound = U_ILLEGAL_CHAR_FOUND,
            InvalidTableFormat = U_INVALID_TABLE_FORMAT,
            BufferOverflow = U_BUFFER_OVERFLOW_ERROR
        };*/
    }
}

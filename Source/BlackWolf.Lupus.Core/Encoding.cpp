#include "Encoding.h"
#include <unicode/ucnv.h>

using namespace std;

namespace Lupus {
    namespace Text {
        shared_ptr<Encoding> Encoding::ASCII()
        {
            return shared_ptr<Encoding>(new Encoding("US-ASCII"));
        }
        
        shared_ptr<Encoding> Encoding::Default()
        {
            return shared_ptr<Encoding>(new Encoding(""));
        }

        shared_ptr<Encoding> Encoding::UTF32()
        {
            return shared_ptr<Encoding>(new Encoding("UTF-32"));
        }

        shared_ptr<Encoding> Encoding::UTF16()
        {
            return shared_ptr<Encoding>(new Encoding("UTF-16"));
        }

        shared_ptr<Encoding> Encoding::UTF8()
        {
            return shared_ptr<Encoding>(new Encoding("UTF-8"));
        }

        shared_ptr<Encoding> Encoding::UTF7()
        {
            return shared_ptr<Encoding>(new Encoding("UTF-7"));
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
                    ucnv_close(mConverter);
                    mConverter = nullptr;
                }

                throw runtime_error("Could not create converter.");
            }
        }

        Encoding::~Encoding()
        {
            if (mConverter) {
                ucnv_close(mConverter);
                mConverter = nullptr;
            }
        }

        shared_ptr<Encoding> Encoding::Clone() const
        {
            return GetEncoding(Name());
        }

        String Encoding::GetString(const vector<uint8_t>& buffer) const
        {
            return GetString(buffer, 0, buffer.size());
        }

        String Encoding::GetString(const vector<uint8_t>& buffer, size_t offset, size_t size) const
        {
            if (offset > buffer.size() || size > buffer.size() - offset) {
                throw out_of_range("offset and size does not match buffer size");
            }

            UErrorCode error = U_ZERO_ERROR;
            int32_t length = (int32_t)size * 4;
            UChar* dest = new UChar[length + 1];
            memset(dest, 0, length + 1);

            int32_t outLength = ucnv_toUChars(mConverter, dest, length, (const char*)buffer.data() + offset, (int32_t)size, &error);

            if (error != U_ZERO_ERROR) {
                delete dest;

                switch (error) {
                    case U_INDEX_OUTOFBOUNDS_ERROR:
                        throw format_error("Source data does not produce an Unicode character.");

                    case U_INVALID_CHAR_FOUND:
                        throw format_error("No mapping was found from source to target encoding.");

                    case U_TRUNCATED_CHAR_FOUND:
                        throw format_error("A character sequence was incomplete.");

                    case U_ILLEGAL_CHAR_FOUND:
                        throw format_error("A character was found which is disallowed in the source encoding.");

                    case U_INVALID_TABLE_FORMAT:
                        throw format_error("An error occured trying to read the backing data for the converter.");

                    case U_BUFFER_OVERFLOW_ERROR:
                        throw format_error("More output characters were produced than fit in the target buffer.");

                    default:
                        throw runtime_error("Could not convert buffer to string.");
                }
            }

            String result(dest);
            delete dest;
            return result;
        }

        vector<uint8_t> Encoding::GetBytes(const String& str) const
        {
            return GetBytes(str, 0, str.Length());
        }

        vector<uint8_t> Encoding::GetBytes(const String& str, size_t offset, size_t size) const
        {
            if (offset > str.Length() || size > str.Length() - offset) {
                throw out_of_range("offset and size does not match string length");
            }
            
            UErrorCode error = U_ZERO_ERROR;
            int32_t length = UCNV_GET_MAX_BYTES_FOR_STRING(str.Length(), ucnv_getMaxCharSize(mConverter));
            char* dest = new char[length];
            memset(dest, 0, length);

            int32_t outLength = ucnv_fromUChars(mConverter, dest, length, str.Data(), (int32_t)str.Length(), &error);

            if (error != U_ZERO_ERROR) {
                delete dest;

                switch (error) {
                    case U_INDEX_OUTOFBOUNDS_ERROR:
                        throw format_error("Source data does not produce an Unicode character.");

                    case U_INVALID_CHAR_FOUND:
                        throw format_error("No mapping was found from source to target encoding.");

                    case U_TRUNCATED_CHAR_FOUND:
                        throw format_error("A character sequence was incomplete.");

                    case U_ILLEGAL_CHAR_FOUND:
                        throw format_error("A character was found which is disallowed in the source encoding.");

                    case U_INVALID_TABLE_FORMAT:
                        throw format_error("An error occured trying to read the backing data for the converter.");

                    case U_BUFFER_OVERFLOW_ERROR:
                        throw format_error("More output characters were produced than fit in the target buffer.");

                    default:
                        throw runtime_error("Could not convert buffer to string.");
                }
            }

            vector<uint8_t> result((uint8_t*)dest, (uint8_t*)dest + outLength);
            delete dest;
            return result;
        }

        String Encoding::Name() const
        {
            UErrorCode error = U_ZERO_ERROR;
            const char* result = ucnv_getName(mConverter, &error);

            if (error != U_ZERO_ERROR) {
                return "invalid converter";
            } else {
                return result;
            }
        }

        shared_ptr<Encoding> Encoding::GetEncoding(String encoding)
        {
            try {
                return shared_ptr<Encoding>(new Encoding(encoding));
            } catch (runtime_error&) {
                return nullptr;
            }
        }

        vector<String> Encoding::GetEncodings()
        {
            vector<String> result;
            int32_t count = ucnv_countAvailable();

            for (int32_t i = 0; i < count; i++) {
                result.push_back(ucnv_getAvailableName(i));
            }

            return result;
        }
    }
}

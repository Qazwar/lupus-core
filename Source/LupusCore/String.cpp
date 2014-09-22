#include "String.h"
#include <unicode/ustring.h>
#include <unicode/unistr.h>
#include <unicode/regex.h>

using namespace std;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4715)
#endif

namespace Lupus {
    const size_t String::Capacity = 1024;

    String::String()
    {
        mString = new UnicodeString();
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(Char ch, size_t count)
    {
        mString = new UnicodeString(ComputeCapacity(count), ch, count);
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const char* str)
    {
        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str, strlen(str))));
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const Char* str) : String(str, 0, u_strlen(str))
    {
    }
    
    String::String(const Char* str, size_t offset, size_t size)
    {
        size_t len = u_strlen(str);

        if (offset > len || size > len - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mString = new UnicodeString(str + offset, size);
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const string& str)
    {
        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str(), str.length())));
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const string& str, size_t offset, size_t size)
    {
        if (offset > str.length() || size > str.length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str() + offset, size)));
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const String& str)
    {
        mString = str.mString;
        mCount = str.mCount;
        AddRef();
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const String& str, size_t offset, size_t size)
    {
        if (offset > str.Length() || size > str.Length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        mString = new UnicodeString(*str.mString, offset, size);
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(String&& str)
    {
        mString = str.mString;
        mCount = str.mCount;
        str.mString = nullptr;
        str.mCount = nullptr;
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(UnicodeString* string)
    {
        mString = string;
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::~String()
    {
        if (mString && ReleaseRef() == 0) {
            delete mString;
            delete mCount;
            mString = nullptr;
            mCount = nullptr;
        }
    }

    Char& String::operator[](size_t index)
    {
        if (index > mString->length()) {
            throw out_of_range("index exceeds size of string");
        }

        return *(const_cast<Char*>(mString->getTerminatedBuffer() + index));
    }

    const Char& String::operator[](size_t index) const
    {
        if (index > mString->length()) {
            throw out_of_range("index exceeds size of internal buffer");
        }

        return *(mString->getTerminatedBuffer() + index);
    }

    String String::Clone() const
    {
        return String(new UnicodeString(*mString));
    }

    const Char* String::Data() const
    {
        return mString->getTerminatedBuffer();
    }

    const Char* String::Data(size_t startIndex) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        }

        return mString->getTerminatedBuffer() + startIndex;
    }

    bool String::IsEmpty() const
    {
        return mString->isEmpty() == TRUE;
    }

    size_t String::Length() const
    {
        return mString->length();
    }

    String String::Append(Char ch) const
    {
        auto result = new UnicodeString(*mString);
        result->append(ch);
        return String(result);
    }

    String String::Append(String str) const
    {
        auto result = new UnicodeString(*mString);
        result->append(*str.mString);
        return String(result);
    }

    String String::Append(String str, size_t offset, size_t size) const
    {
        if (offset > str.Length() || size > str.Length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        auto result = new UnicodeString(*mString);
        result->append(*str.mString, offset, size);
        return String(result);
    }

    int String::Compare(String str, StringCaseSensitivity sens) const
    {
        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return mString->compare(*str.mString);
            case StringCaseSensitivity::CaseInsensitive:
                return mString->caseCompare(*str.mString, 0);
        }
    }

    int String::Compare(String str, size_t offset, size_t size, StringCaseSensitivity sens) const
    {
        if (offset > str.Length() || size > str.Length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return mString->compare(0, mString->length(), *str.mString, offset, size);
            case StringCaseSensitivity::CaseInsensitive:
                return mString->caseCompare(0, mString->length(), *str.mString, offset, size, 0);
        }
    }

    int String::Compare(size_t offset, size_t size, String cmpStr, size_t cmpOffset, size_t cmpSize, StringCaseSensitivity sens) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        } else if (cmpOffset > cmpStr.Length() || cmpSize > cmpStr.Length() - cmpOffset) {
            throw out_of_range("cmpOffset and cmpSize does not match cmpBuffer size");
        }

        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return mString->compare(offset, size, *cmpStr.mString, offset, size);
            case StringCaseSensitivity::CaseInsensitive:
                return mString->caseCompare(offset, size, *cmpStr.mString, offset, size, 0);
        }
    }

    bool String::Contains(String str) const
    {
        return mString->indexOf(*str.mString) != -1;
    }

    void String::CopyTo(size_t srcIndex, std::vector<Char>& dst, size_t dstIndex, size_t dstSize) const
    {
        if (srcIndex > mString->length()) {
            throw out_of_range("srcIndex exceeds size of internal buffer");
        } else if (dstIndex > dst.size() || dstSize > dst.size() - dstIndex) {
            throw out_of_range("dstIndex of dstSize exceed given buffer");
        }

        mString->extract((int32_t)srcIndex, (int32_t)dstSize, &dst[0], (int32_t)dstIndex);
    }

    bool String::EndsWith(String str) const
    {
        return mString->endsWith(*str.mString) == TRUE;
    }

    bool String::EndsWith(String str, size_t offset, size_t size) const
    {
        if (offset > str.Length() || size > str.Length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->endsWith(*str.mString, offset, size) == TRUE;
    }

    int String::IndexOf(Char ch) const
    {
        return mString->indexOf(ch);
    }

    int String::IndexOf(String str) const
    {
        return mString->indexOf(*str.mString);
    }

    int String::IndexOf(Char ch, size_t offset) const
    {
        if (offset > mString->length()) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->indexOf(ch, offset);
    }

    int String::IndexOf(String str, size_t offset) const
    {
        if (offset > mString->length()) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->indexOf(*str.mString, offset);
    }

    int String::IndexOf(Char ch, size_t offset, size_t size) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->indexOf(ch, offset, size);
    }

    int String::IndexOf(String str, size_t offset, size_t size) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->indexOf(*str.mString, offset, size);
    }

    int String::IndexOfAny(const std::vector<Char>& chars) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::IndexOfAny(const std::vector<Char>& chars, size_t offset) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch, offset)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::IndexOfAny(const std::vector<Char>& chars, size_t offset, size_t size) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch, offset, size)) != -1) {
                break;
            }
        }

        return result;
    }

    String String::Insert(size_t startIndex, Char ch) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->insert(startIndex, ch);
        return String(result);
    }

    String String::Insert(size_t startIndex, String str) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->insert(startIndex, *str.mString);
        return String(result);
    }

    String String::Insert(size_t startIndex, String str, size_t offset, size_t size) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        } else if (offset > str.Length() || size > str.Length() - size) {
            throw out_of_range("offset or size exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->insert(startIndex, *str.mString, offset, size);
        return String(result);
    }

    int String::LastIndexOf(Char ch) const
    {
        return mString->lastIndexOf(ch);
    }

    int String::LastIndexOf(String str) const
    {
        return mString->lastIndexOf(*str.mString);
    }

    int String::LastIndexOf(Char ch, size_t offset) const
    {
        if (offset > mString->length()) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->lastIndexOf(ch, offset);
    }

    int String::LastIndexOf(String str, size_t offset) const
    {
        if (offset > mString->length()) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->lastIndexOf(*str.mString, offset);
    }

    int String::LastIndexOf(Char ch, size_t offset, size_t size) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->lastIndexOf(ch, offset, size);
    }

    int String::LastIndexOf(String str, size_t offset, size_t size) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset and size does not match buffer size");
        }

        return mString->lastIndexOf(*str.mString, offset, size);
    }

    int String::LastIndexOfAny(const std::vector<Char>& chars) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::LastIndexOfAny(const std::vector<Char>& chars, size_t offset) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch, offset)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::LastIndexOfAny(const std::vector<Char>& chars, size_t offset, size_t size) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch, offset, size)) != -1) {
                break;
            }
        }

        return result;
    }

    String String::Remove(size_t startIndex) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->remove(startIndex);
        return String(result);
    }

    String String::Remove(size_t startIndex, size_t count) const
    {
        if (startIndex > mString->length() || count > mString->length() - startIndex) {
            throw out_of_range("startIndex or count exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->remove(startIndex, count);
        return String(result);
    }

    String String::Replace(Char oldCh, Char newCh) const
    {
        auto result = new UnicodeString(*mString);
        result->findAndReplace(UnicodeString(oldCh), UnicodeString(newCh));
        return String(result);
    }

    String String::Replace(String oldStr, String newStr) const
    {
        auto result = new UnicodeString(*mString);
        result->findAndReplace(*oldStr.mString, *newStr.mString);
        return String(result);
    }

    String String::Reverse() const
    {
        auto result = new UnicodeString(*mString);
        result->reverse();
        return String(result);
    }

    String String::Reverse(size_t startIndex, size_t count) const
    {
        if (startIndex > mString->length() || count > mString->length() - startIndex) {
            throw out_of_range("startIndex or count exceeds size of internal buffer");
        }

        auto result = new UnicodeString(*mString);
        result->reverse(startIndex, count);
        return String(result);
    }

    vector<String> String::Split(const vector<Char>& delimiter, StringSplitOption option, StringCaseSensitivity sens) const
    {
        String str("[");
        UErrorCode status = U_ZERO_ERROR;

        for_each(std::begin(delimiter), std::end(delimiter), [&str](Char ch) {
            str += ch;
        });

        str += "]";

        RegexMatcher m(*str.mString, sens == StringCaseSensitivity::CaseInsensitive ? UREGEX_CASE_INSENSITIVE : 0, status);

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not create RegexMatcher");
        }

        vector<UnicodeString> dest(1024);
        int32_t count = m.split(*mString, &dest[0], 1024, status) / 2 + 1;
        int32_t n = 0;

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not split string with given pattern");
        }

        vector<String> result;

        for (auto& it : dest) {
            bool add = true;
            String tmp(it.getTerminatedBuffer());

            for (Char cmp : delimiter) {
                if (!(add = !(tmp == String(cmp)))) {
                    break;
                }
            }

            if (add) {
                if (!tmp.IsEmpty() || option == StringSplitOption::None) {
                    result.push_back(tmp);
                }

                if (result.size() == count || ++n == count) {
                    break;
                }
            }
        }

        return result;
    }

    vector<String> String::Split(const vector<Char>& delimiter, size_t count, StringSplitOption option, StringCaseSensitivity sens) const
    {
        String str("[");
        UErrorCode status = U_ZERO_ERROR;

        for_each(std::begin(delimiter), std::end(delimiter), [&str](Char ch) {
            str += ch;
        });

        str += "]";

        RegexMatcher m(*str.mString, sens == StringCaseSensitivity::CaseInsensitive ? UREGEX_CASE_INSENSITIVE : 0, status);

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not create RegexMatcher");
        }

        vector<UnicodeString> dest(count * 2);
        int32_t c = m.split(*mString, &dest[0], count * 2, status) / 2 + 1;

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not split string with given pattern");
        }

        vector<String> result;

        for (auto& it : dest) {
            bool add = true;
            String tmp(it.getTerminatedBuffer());

            for (Char cmp : delimiter) {
                if (!(add = !(tmp == String(cmp)))) {
                    break;
                }
            }

            if (add) {
                if (!tmp.IsEmpty() || option == StringSplitOption::None) {
                    result.push_back(tmp);
                }

                if (result.size() == c) {
                    break;
                }
            }
        }

        return result;
    }

    vector<String> String::Split(const vector<String>& delimiter, StringSplitOption option, StringCaseSensitivity sens) const
    {
        String str("(");
        UErrorCode status = U_ZERO_ERROR;

        for_each(std::begin(delimiter), std::end(delimiter), [&str](String s) {
            if (str.Length() == 1) {
                str += s;
            } else {
                str += "|" + s;
            }
        });

        str += ")";

        RegexMatcher m(*str.mString, sens == StringCaseSensitivity::CaseInsensitive ? UREGEX_CASE_INSENSITIVE : 0, status);

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not create RegexMatcher");
        }

        vector<UnicodeString> dest(1024);
        int32_t count = m.split(*mString, &dest[0], 1024, status) / 2 + 1;
        int32_t n = 0;

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not split string with given pattern");
        }

        vector<String> result;

        for (auto& it : dest) {
            bool add = true;
            String tmp(it.getTerminatedBuffer());

            for (String cmp : delimiter) {
                if (!(add = !(tmp == cmp))) {
                    break;
                }
            }

            if (add) {
                if (!tmp.IsEmpty() || option == StringSplitOption::None) {
                    result.push_back(tmp);
                }

                if (result.size() == count || ++n == count) {
                    break;
                }
            }
        }

        return result;
    }

    vector<String> String::Split(const vector<String>& delimiter, size_t count, StringSplitOption option, StringCaseSensitivity sens) const
    {
        String str("(");
        UErrorCode status = U_ZERO_ERROR;

        for_each(std::begin(delimiter), std::end(delimiter), [&str](String s) {
            if (str.Length() == 1) {
                str += s;
            } else {
                str += "|" + s;
            }
        });

        str += ")";

        RegexMatcher m(*str.mString, sens == StringCaseSensitivity::CaseInsensitive ? UREGEX_CASE_INSENSITIVE : 0, status);

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not create RegexMatcher");
        }

        vector<UnicodeString> dest(count * 2);
        int32_t c = m.split(*mString, &dest[0], count * 2, status) / 2 + 1;

        if (status != U_ZERO_ERROR) {
            throw format_error("Could not split string with given pattern");
        }

        vector<String> result;

        for (auto& it : dest) {
            bool add = true;
            String tmp(it.getTerminatedBuffer());

            for (String cmp : delimiter) {
                if (!(add = !(tmp == cmp))) {
                    break;
                }
            }

            if (add) {
                if (!tmp.IsEmpty() || option == StringSplitOption::None) {
                    result.push_back(tmp);
                }

                if (result.size() == c) {
                    break;
                }
            }
        }

        return result;
    }

    bool String::StartsWith(String str) const
    {
        return mString->startsWith(*str.mString) == TRUE;
    }

    bool String::StartsWith(String str, size_t offset, size_t size) const
    {
        if (offset > mString->length() || size > mString->length() - offset) {
            throw out_of_range("offset or size exceeds size of internal buffer");
        }

        return mString->startsWith(*str.mString, offset, size) == TRUE;
    }

    String String::Substring(size_t startIndex) const
    {
        if (startIndex > mString->length()) {
            throw out_of_range("startIndex exceeds size of internal buffer");
        }

        return String(new UnicodeString(mString->getTerminatedBuffer() + startIndex));
    }

    String String::Substring(size_t startIndex, size_t count) const
    {
        if (startIndex > mString->length() || count > mString->length() - startIndex) {
            throw out_of_range("startIndex or count exceeds size of internal buffer");
        }

        return String(new UnicodeString(mString->getTerminatedBuffer() + startIndex, count));
    }

    String String::ToLower() const
    {
        auto result = new UnicodeString(*mString);
        result->toLower();
        return String(result);
    }

    String String::ToUpper() const
    {
        auto result = new UnicodeString(*mString);
        result->toUpper();
        return String(result);
    }

    string String::ToUTF8() const
    {
        string result;
        return mString->toUTF8String<string>(result);
    }

    u16string String::ToUTF16() const
    {
        return u16string((const char16_t*)mString->getTerminatedBuffer());
    }

    u32string String::ToUTF32() const
    {
        UErrorCode errorCode;
        Char32* utf32 = new Char32[mString->countChar32()];
        mString->toUTF32(utf32, mString->countChar32(), errorCode);

        if (errorCode != U_ZERO_ERROR) {
            throw runtime_error("Error while converting to UTF32");
        }

        u32string result((char32_t*)utf32);
        delete utf32;
        return result;
    }

    String String::Trim() const
    {
        auto result = new UnicodeString(*mString);
        result->trim();
        return String(result);
    }

    bool String::operator==(String str) const
    {
        return mString->operator==(*str.mString) == TRUE;
    }

    bool String::operator!=(String str) const
    {
        return mString->operator!=(*str.mString) == TRUE;
    }

    bool String::operator<(String str) const
    {
        return mString->operator<(*str.mString) == TRUE;
    }

    bool String::operator>(String str) const
    {
        return mString->operator>(*str.mString) == TRUE;
    }

    bool String::operator<=(String str) const
    {
        return mString->operator<=(*str.mString) == TRUE;
    }

    bool String::operator>=(String str) const
    {
        return mString->operator>=(*str.mString) == TRUE;
    }

    String String::operator+(Char ch) const
    {
        auto result = new UnicodeString(*mString);
        result->append(ch);
        return String(result);
    }

    String String::operator+(const String& str) const
    {
        auto result = new UnicodeString(*mString);
        result->append(*str.mString);
        return String(result);
    }

    String& String::operator=(Char ch)
    {
        if (ReleaseRef() == 0) {
            delete mString;
            delete mCount;
        }

        mString = new UnicodeString(ch);
        mCount = new size_t(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String& String::operator=(const String& str)
    {
        if (ReleaseRef() == 0) {
            delete mString;
            delete mCount;
        }

        mString = str.mString;
        mCount = str.mCount;
        AddRef();
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String& String::operator=(String&& str)
    {
        mString = str.mString;
        mCount = str.mCount;
        str.mString = nullptr;
        str.mCount = nullptr;
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String& String::operator+=(Char ch)
    {
        *mString += ch;
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String& String::operator+=(const String& string)
    {
        *mString += *string.mString;
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String String::FromUTF8(const string& str)
    {
        return String(new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str(), str.length()))));
    }

    String String::FromUTF16(const u16string& str)
    {
        return String((const Char*)str.data());
    }

    String String::FromUTF32(const u32string& str)
    {
        return String(new UnicodeString(UnicodeString::fromUTF32((const Char32*)str.data(), str.length())));
    }

    size_t String::AddRef()
    {
        return (++(*mCount));
    }

    size_t String::ReleaseRef()
    {
        return (--(*mCount));
    }

    size_t String::RefCount() const
    {
        return *mCount;
    }

    size_t String::ComputeCapacity(size_t length)
    {
        return ((length / Capacity) + 1) * Capacity;
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

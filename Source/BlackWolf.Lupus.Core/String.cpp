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
#include "String.h"
#include "Encoding.h"
#include <unicode/uchar.h>
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

        if (offset > len) {
            throw out_of_range("offset");
        } else if (size > len - offset) {
            throw out_of_range("size");
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
        if (offset > str.length()) {
            throw out_of_range("offset");
        } else if (size > str.length() - offset) {
            throw out_of_range("size");
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
        if (offset > str.Length()) {
            throw out_of_range("offset");
        } else if (size > str.Length() - offset) {
            throw out_of_range("size");
        }

        mString = new UnicodeString(*((UnicodeString*)str.mString), offset, size);
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

    String::String(void* string)
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
            if (mCount) {
                delete mCount;
                mCount = nullptr;
            }

            delete mString;
            mString = nullptr;
        }
    }

    Char& String::operator[](size_t index)
    {
        if (index > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("index");
        }

        return *(const_cast<Char*>(((UnicodeString*)mString)->getTerminatedBuffer() + index));
    }

    const Char& String::operator[](size_t index) const
    {
        if (index > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("index");
        }

        return *(((UnicodeString*)mString)->getTerminatedBuffer() + index);
    }

    String String::Clone() const
    {
        return String(new UnicodeString(*((UnicodeString*)mString)));
    }

    const Char* String::Data() const
    {
        return ((UnicodeString*)mString)->getTerminatedBuffer();
    }

    const Char* String::Data(size_t startIndex) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        }

        return ((UnicodeString*)mString)->getTerminatedBuffer() + startIndex;
    }

    bool String::IsEmpty() const
    {
        return ((UnicodeString*)mString)->isEmpty() == TRUE;
    }

    size_t String::Length() const
    {
        return ((UnicodeString*)mString)->length();
    }

    String String::Append(Char ch) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->append(ch);
        return String(result);
    }

    String String::Append(String str) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->append(*((UnicodeString*)str.mString));
        return String(result);
    }

    String String::Append(String str, size_t offset, size_t size) const
    {
        if (offset > str.Length()) {
            throw out_of_range("offset");
        } else if (size > str.Length() - offset) {
            throw out_of_range("size");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->append(*((UnicodeString*)str.mString), offset, size);
        return String(result);
    }

    int String::Compare(String str, StringCaseSensitivity sens) const
    {
        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return ((UnicodeString*)mString)->compare(*((UnicodeString*)str.mString));
            case StringCaseSensitivity::CaseInsensitive:
                return ((UnicodeString*)mString)->caseCompare(*((UnicodeString*)str.mString), 0);
        }
    }

    int String::Compare(String str, size_t offset, size_t size, StringCaseSensitivity sens) const
    {
        if (offset > str.Length()) {
            throw out_of_range("offset");
        } else if (size > str.Length() - offset) {
            throw out_of_range("size");
        }

        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return ((UnicodeString*)mString)->compare(0, ((UnicodeString*)mString)->length(), *((UnicodeString*)str.mString), offset, size);
            case StringCaseSensitivity::CaseInsensitive:
                return ((UnicodeString*)mString)->caseCompare(0, ((UnicodeString*)mString)->length(), *((UnicodeString*)str.mString), offset, size, 0);
        }
    }

    int String::Compare(size_t offset, size_t size, String cmpStr, size_t cmpOffset, size_t cmpSize, StringCaseSensitivity sens) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        } else if (cmpOffset > cmpStr.Length()) {
            throw out_of_range("cmpOffset");
        } else if (cmpSize > cmpStr.Length() - cmpOffset) {
            throw out_of_range("cmpSize");
        }

        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return ((UnicodeString*)mString)->compare(offset, size, *((UnicodeString*)cmpStr.mString), offset, size);
            case StringCaseSensitivity::CaseInsensitive:
                return ((UnicodeString*)mString)->caseCompare(offset, size, *((UnicodeString*)cmpStr.mString), offset, size, 0);
        }
    }

    bool String::Contains(String str) const
    {
        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString)) != -1;
    }

    void String::CopyTo(size_t srcIndex, std::vector<Char>& dst, size_t dstIndex, size_t dstSize) const
    {
        if (srcIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("srcIndex");
        } else if (dstIndex > dst.size()) {
            throw out_of_range("dstIndex");
        } else if (dstSize > dst.size() - dstIndex) {
            throw out_of_range("dstSize");
        }

        ((UnicodeString*)mString)->extract((int32_t)srcIndex, (int32_t)dstSize, &dst[0], (int32_t)dstIndex);
    }

    bool String::EndsWith(String str) const
    {
        return ((UnicodeString*)mString)->endsWith(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::EndsWith(String str, size_t offset, size_t size) const
    {
        if (offset > str.Length()) {
            throw out_of_range("offset");
        } else if (size > str.Length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->endsWith(*((UnicodeString*)str.mString), offset, size) == TRUE;
    }

    int String::IndexOf(Char ch) const
    {
        return ((UnicodeString*)mString)->indexOf(ch);
    }

    int String::IndexOf(String str) const
    {
        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString));
    }

    int String::IndexOf(Char ch, size_t offset) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        }

        return ((UnicodeString*)mString)->indexOf(ch, offset);
    }

    int String::IndexOf(String str, size_t offset) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        }

        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString), offset);
    }

    int String::IndexOf(Char ch, size_t offset, size_t size) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->indexOf(ch, offset, size);
    }

    int String::IndexOf(String str, size_t offset, size_t size) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString), offset, size);
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
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->insert(startIndex, ch);
        return String(result);
    }

    String String::Insert(size_t startIndex, String str) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->insert(startIndex, *((UnicodeString*)str.mString));
        return String(result);
    }

    String String::Insert(size_t startIndex, String str, size_t offset, size_t size) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        } else if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->insert(startIndex, *((UnicodeString*)str.mString), offset, size);
        return String(result);
    }

    int String::LastIndexOf(Char ch) const
    {
        return ((UnicodeString*)mString)->lastIndexOf(ch);
    }

    int String::LastIndexOf(String str) const
    {
        return ((UnicodeString*)mString)->lastIndexOf(*((UnicodeString*)str.mString));
    }

    int String::LastIndexOf(Char ch, size_t offset) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        }

        return ((UnicodeString*)mString)->lastIndexOf(ch, offset);
    }

    int String::LastIndexOf(String str, size_t offset) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        }

        return ((UnicodeString*)mString)->lastIndexOf(*((UnicodeString*)str.mString), offset);
    }

    int String::LastIndexOf(Char ch, size_t offset, size_t size) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->lastIndexOf(ch, offset, size);
    }

    int String::LastIndexOf(String str, size_t offset, size_t size) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->lastIndexOf(*((UnicodeString*)str.mString), offset, size);
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
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->remove(startIndex);
        return String(result);
    }

    String String::Remove(size_t startIndex, size_t count) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        } else if (count > (size_t)((UnicodeString*)mString)->length() - startIndex) {
            throw out_of_range("count");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->remove(startIndex, count);
        return String(result);
    }

    String String::Replace(Char oldCh, Char newCh) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->findAndReplace(UnicodeString(oldCh), UnicodeString(newCh));
        return String(result);
    }

    String String::Replace(String oldStr, String newStr) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->findAndReplace(*((UnicodeString*)oldStr.mString), *((UnicodeString*)newStr.mString));
        return String(result);
    }

    String String::Reverse() const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->reverse();
        return String(result);
    }

    String String::Reverse(size_t startIndex, size_t count) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        } else if (count > (size_t)((UnicodeString*)mString)->length() - startIndex) {
            throw out_of_range("count");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->reverse(startIndex, count);
        return String(result);
    }

    vector<String> String::Split(const vector<Char>& delimiter, StringSplitOption option) const
    {
        vector<String> result;
        int32_t previousIndex = 0;

        for (int32_t i = 0; i < ((UnicodeString*)mString)->length(); i++) {
            for (auto ch : delimiter) {
                if (((UnicodeString*)mString)->operator[](i) == ch) {
                    String str;

                    if (option == StringSplitOption::RemoveEmptyEntries && i == previousIndex) {
                        continue;
                    } else if (i != previousIndex) {
                        str = this->Substring(previousIndex, i);
                    }

                    result.push_back(str);
                    previousIndex = i + 1;
                }
            }
        }

        return result;
    }

    vector<String> String::Split(const vector<Char>& delimiter, size_t count, StringSplitOption option) const
    {
        vector<String> result;
        int32_t previousIndex = 0;

        for (int32_t i = 0; i < ((UnicodeString*)mString)->length(); i++) {
            for (auto ch : delimiter) {
                if (((UnicodeString*)mString)->operator[](i) == ch) {
                    String str;

                    if (option == StringSplitOption::RemoveEmptyEntries && i == previousIndex) {
                        continue;
                    } else if (i != previousIndex) {
                        str = this->Substring(previousIndex, i);
                    }

                    result.push_back(str);
                    previousIndex = i + 1;

                    if (result.size() == count) {
                        break;
                    }
                }

                if (result.size() == count) {
                    break;
                }
            }
        }

        return result;
    }

    vector<String> String::Split(const String& str, StringSplitOption option) const
    {
        vector<String> result;
        int32_t previousIndex = 0;
        int32_t savedIndex = -1;

        for (int32_t index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), 0); index != -1; savedIndex = index, index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), index + 1)) {
            String tmp;

            if (option == StringSplitOption::RemoveEmptyEntries && index == previousIndex) {
                continue;
            } else if (index != previousIndex) {
                tmp = Substring(previousIndex, index - previousIndex);
            }

            result.push_back(tmp);
            previousIndex = index + str.Length();
        }

        if (savedIndex != previousIndex && (size_t)previousIndex < Length() - 1) {
            result.push_back(Substring(previousIndex));
        }

        return result;
    }

    vector<String> String::Split(const String& str, size_t count, StringSplitOption option) const
    {
        vector<String> result;
        int32_t previousIndex = 0;
        int32_t savedIndex = -1;

        for (int32_t index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), 0); index != -1; savedIndex = index, index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), index + 1)) {
            String tmp;

            if (option == StringSplitOption::RemoveEmptyEntries && index == previousIndex) {
                continue;
            } else if (index != previousIndex) {
                tmp = Substring(previousIndex, index - previousIndex);
            }

            result.push_back(tmp);
            previousIndex = index + str.Length();

            if (result.size() == count) {
                break;
            }
        }


        if (result.size() < count) {
            if (savedIndex != previousIndex && (size_t)previousIndex < Length() - 1) {
                result.push_back(Substring(previousIndex));
            }
        }

        return result;
    }

    bool String::StartsWith(String str) const
    {
        return ((UnicodeString*)mString)->startsWith(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::StartsWith(String str, size_t offset, size_t size) const
    {
        if (offset > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("offset");
        } else if (size > (size_t)((UnicodeString*)mString)->length() - offset) {
            throw out_of_range("size");
        }

        return ((UnicodeString*)mString)->startsWith(*((UnicodeString*)str.mString), offset, size) == TRUE;
    }

    String String::Substring(size_t startIndex) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        }

        return String(new UnicodeString(((UnicodeString*)mString)->getTerminatedBuffer() + startIndex));
    }

    String String::Substring(size_t startIndex, size_t count) const
    {
        if (startIndex > (size_t)((UnicodeString*)mString)->length()) {
            throw out_of_range("startIndex");
        } else if (count > (size_t)((UnicodeString*)mString)->length() - startIndex) {
            throw out_of_range("count");
        }

        return String(new UnicodeString(((UnicodeString*)mString)->getTerminatedBuffer() + startIndex, count));
    }

    String String::ToLower() const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->toLower();
        return String(result);
    }

    String String::ToUpper() const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->toUpper();
        return String(result);
    }

    string String::ToUTF8() const
    {
        string result;
        return ((UnicodeString*)mString)->toUTF8String<string>(result);
    }

    u16string String::ToUTF16() const
    {
        return u16string((const char16_t*)((UnicodeString*)mString)->getTerminatedBuffer());
    }

    u32string String::ToUTF32() const
    {
        UErrorCode errorCode;
        Char32* utf32 = new Char32[((UnicodeString*)mString)->countChar32()];
        ((UnicodeString*)mString)->toUTF32(force_cast<UChar32*>(utf32), ((UnicodeString*)mString)->countChar32(), errorCode);

        if (errorCode != U_ZERO_ERROR) {
            throw runtime_error("Error while converting to UTF32");
        }

        u32string result((char32_t*)utf32);
        delete utf32;
        return result;
    }

    String String::Trim() const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->trim();
        return String(result);
    }

    bool String::operator==(String str) const
    {
        return ((UnicodeString*)mString)->operator==(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::operator!=(String str) const
    {
        return ((UnicodeString*)mString)->operator!=(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::operator<(String str) const
    {
        return ((UnicodeString*)mString)->operator<(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::operator>(String str) const
    {
        return ((UnicodeString*)mString)->operator>(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::operator<=(String str) const
    {
        return ((UnicodeString*)mString)->operator<=(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::operator>=(String str) const
    {
        return ((UnicodeString*)mString)->operator>=(*((UnicodeString*)str.mString)) == TRUE;
    }

    String String::operator+(Char ch) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->append(ch);
        return String(result);
    }

    String String::operator+(const String& str) const
    {
        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->append(*((UnicodeString*)str.mString));
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
        *((UnicodeString*)mString) += ch;
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
        return *this;
    }

    String& String::operator+=(const String& str)
    {
        *((UnicodeString*)mString) += *((UnicodeString*)str.mString);
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
        return String((const UChar*)str.data());
    }

    String String::FromUTF32(const u32string& str)
    {
        return String(new UnicodeString(UnicodeString::fromUTF32((const UChar32*)str.data(), str.length())));
    }

    size_t String::AddRef()
    {
        if (mCount) {
            return (++(*mCount));
        } else {
            return 0;
        }
    }

    size_t String::ReleaseRef()
    {
        if (mCount) {
            return (--(*mCount));
        } else {
            return 0;
        }
    }

    size_t String::RefCount() const
    {
        if (mCount) {
            return *mCount;
        } else {
            return 0;
        }
    }

    size_t String::ComputeCapacity(size_t length)
    {
        return ((length / Capacity) + 1) * Capacity;
    }

    Char ToChar(char ch)
    {
        return String(std::string(1, ch))[0];
    }

    Char ToChar(wchar_t wc)
    {
#ifdef _UNICODE
        return wc;
#else
        return Text::Encoding::UTF8()->GetString(std::vector<uint8_t>((uint8_t*)&wc, ((uint8_t*)&wc) + sizeof(wchar_t)))[0];
#endif
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

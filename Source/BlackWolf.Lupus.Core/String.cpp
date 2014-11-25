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
#include "String.h"
#include "Encoding.h"
#include <unicode/uchar.h>
#include <unicode/ustring.h>
#include <unicode/unistr.h>
#include <unicode/regex.h>



#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4267)
#pragma warning(disable: 4715)
#endif

namespace Lupus {
    const U32 String::Capacity = 1024;

    String::String()
    {
        mString = new UnicodeString();
        mCount = new U32(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(Char ch, U32 count)
    {
        mString = new UnicodeString(ComputeCapacity(count), ch, count);
        mCount = new U32(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const char* str)
    {
        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str, strlen(str))));
        mCount = new U32(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const Char* str) : String(str, 0, u_strlen(str))
    {
    }
    
    String::String(const Char* str, U32 offset, U32 size)
    {
        U32 len = u_strlen(str);

        if (offset > len) {
            throw OutOfRange("offset");
        } else if (size > len - offset) {
            throw OutOfRange("size");
        }

        mString = new UnicodeString(str + offset, size);
        mCount = new U32(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const Vector<Char>& chars) :
        String(chars.data())
    {
    }

    String::String(const Vector<Char>& chars, U32 offset, U32 size) :
        String(chars.data(), offset, size)
    {
    }

    String::String(const std::string& str)
    {
        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str(), str.length())));
        mCount = new U32(1);
#ifdef _DEBUG
        mDebugString = ToUTF8();
#endif
    }

    String::String(const std::string& str, U32 offset, U32 size)
    {
        if (offset > str.length()) {
            throw OutOfRange("offset");
        } else if (size > str.length() - offset) {
            throw OutOfRange("size");
        }

        mString = new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str() + offset, size)));
        mCount = new U32(1);
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

    String::String(const String& str, U32 offset, U32 size)
    {
        if (offset > str.Length()) {
            throw OutOfRange("offset");
        } else if (size > str.Length() - offset) {
            throw OutOfRange("size");
        }

        mString = new UnicodeString(*((UnicodeString*)str.mString), offset, size);
        mCount = new U32(1);
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
        mCount = new U32(1);
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

    Char& String::operator[](U32 index)
    {
        if (index > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("index");
        }

        return *(const_cast<Char*>(((UnicodeString*)mString)->getTerminatedBuffer() + index));
    }

    const Char& String::operator[](U32 index) const
    {
        if (index > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("index");
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

    const Char* String::Data(U32 startIndex) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        }

        return ((UnicodeString*)mString)->getTerminatedBuffer() + startIndex;
    }

    bool String::IsEmpty() const
    {
        return ((UnicodeString*)mString)->isEmpty() == TRUE;
    }

    U32 String::Length() const
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

    String String::Append(String str, U32 offset, U32 size) const
    {
        if (offset > str.Length()) {
            throw OutOfRange("offset");
        } else if (size > str.Length() - offset) {
            throw OutOfRange("size");
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

    int String::Compare(String str, U32 offset, U32 size, StringCaseSensitivity sens) const
    {
        if (offset > str.Length()) {
            throw OutOfRange("offset");
        } else if (size > str.Length() - offset) {
            throw OutOfRange("size");
        }

        switch (sens) {
            case StringCaseSensitivity::CaseSensitive:
                return ((UnicodeString*)mString)->compare(0, ((UnicodeString*)mString)->length(), *((UnicodeString*)str.mString), offset, size);
            case StringCaseSensitivity::CaseInsensitive:
                return ((UnicodeString*)mString)->caseCompare(0, ((UnicodeString*)mString)->length(), *((UnicodeString*)str.mString), offset, size, 0);
        }
    }

    int String::Compare(U32 offset, U32 size, String cmpStr, U32 cmpOffset, U32 cmpSize, StringCaseSensitivity sens) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        } else if (cmpOffset > cmpStr.Length()) {
            throw OutOfRange("cmpOffset");
        } else if (cmpSize > cmpStr.Length() - cmpOffset) {
            throw OutOfRange("cmpSize");
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

    void String::CopyTo(U32 srcIndex, Vector<Char>& dst, U32 dstIndex, U32 dstSize) const
    {
        if (srcIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("srcIndex");
        } else if (dstIndex > dst.size()) {
            throw OutOfRange("dstIndex");
        } else if (dstSize > dst.size() - dstIndex) {
            throw OutOfRange("dstSize");
        }

        ((UnicodeString*)mString)->extract((S32)srcIndex, (S32)dstSize, &dst[0], (S32)dstIndex);
    }

    bool String::EndsWith(String str) const
    {
        return ((UnicodeString*)mString)->endsWith(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::EndsWith(String str, U32 offset, U32 size) const
    {
        if (offset > str.Length()) {
            throw OutOfRange("offset");
        } else if (size > str.Length() - offset) {
            throw OutOfRange("size");
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

    int String::IndexOf(Char ch, U32 offset) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        }

        return ((UnicodeString*)mString)->indexOf(ch, offset);
    }

    int String::IndexOf(String str, U32 offset) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        }

        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString), offset);
    }

    int String::IndexOf(Char ch, U32 offset, U32 size) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        }

        return ((UnicodeString*)mString)->indexOf(ch, offset, size);
    }

    int String::IndexOf(String str, U32 offset, U32 size) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        }

        return ((UnicodeString*)mString)->indexOf(*((UnicodeString*)str.mString), offset, size);
    }

    int String::IndexOfAny(const Vector<Char>& chars) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::IndexOfAny(const Vector<Char>& chars, U32 offset) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch, offset)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::IndexOfAny(const Vector<Char>& chars, U32 offset, U32 size) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = IndexOf(ch, offset, size)) != -1) {
                break;
            }
        }

        return result;
    }

    String String::Insert(U32 startIndex, Char ch) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->insert(startIndex, ch);
        return String(result);
    }

    String String::Insert(U32 startIndex, String str) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->insert(startIndex, *((UnicodeString*)str.mString));
        return String(result);
    }

    String String::Insert(U32 startIndex, String str, U32 offset, U32 size) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        } else if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
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

    int String::LastIndexOf(Char ch, U32 offset) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        }

        return ((UnicodeString*)mString)->lastIndexOf(ch, offset);
    }

    int String::LastIndexOf(String str, U32 offset) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        }

        return ((UnicodeString*)mString)->lastIndexOf(*((UnicodeString*)str.mString), offset);
    }

    int String::LastIndexOf(Char ch, U32 offset, U32 size) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        }

        return ((UnicodeString*)mString)->lastIndexOf(ch, offset, size);
    }

    int String::LastIndexOf(String str, U32 offset, U32 size) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        }

        return ((UnicodeString*)mString)->lastIndexOf(*((UnicodeString*)str.mString), offset, size);
    }

    int String::LastIndexOfAny(const Vector<Char>& chars) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::LastIndexOfAny(const Vector<Char>& chars, U32 offset) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch, offset)) != -1) {
                break;
            }
        }

        return result;
    }

    int String::LastIndexOfAny(const Vector<Char>& chars, U32 offset, U32 size) const
    {
        int result = -1;

        for (const Char& ch : chars) {
            if ((result = LastIndexOf(ch, offset, size)) != -1) {
                break;
            }
        }

        return result;
    }

    String String::Remove(U32 startIndex) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->remove(startIndex);
        return String(result);
    }

    String String::Remove(U32 startIndex, U32 count) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        } else if (count > (U32)((UnicodeString*)mString)->length() - startIndex) {
            throw OutOfRange("count");
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

    String String::Reverse(U32 startIndex, U32 count) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        } else if (count > (U32)((UnicodeString*)mString)->length() - startIndex) {
            throw OutOfRange("count");
        }

        auto result = new UnicodeString(*((UnicodeString*)mString));
        result->reverse(startIndex, count);
        return String(result);
    }

    Vector<String> String::Split(const Vector<Char>& delimiter, StringSplitOption option) const
    {
        Vector<String> result;
        S32 previousIndex = 0;

        for (S32 i = 0; i < ((UnicodeString*)mString)->length(); i++) {
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

    Vector<String> String::Split(const Vector<Char>& delimiter, U32 count, StringSplitOption option) const
    {
        Vector<String> result;
        S32 previousIndex = 0;

        for (S32 i = 0; i < ((UnicodeString*)mString)->length(); i++) {
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

    Vector<String> String::Split(const String& str, StringSplitOption option) const
    {
        Vector<String> result;
        S32 previousIndex = 0;
        S32 savedIndex = -1;

        for (S32 index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), 0); index != -1; savedIndex = index, index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), index + 1)) {
            String tmp;

            if (option == StringSplitOption::RemoveEmptyEntries && index == previousIndex) {
                continue;
            } else if (index != previousIndex) {
                tmp = Substring(previousIndex, index - previousIndex);
            }

            result.push_back(tmp);
            previousIndex = index + str.Length();
        }

        if (savedIndex != previousIndex && (U32)previousIndex < Length() - 1) {
            result.push_back(Substring(previousIndex));
        }

        return result;
    }

    Vector<String> String::Split(const String& str, U32 count, StringSplitOption option) const
    {
        Vector<String> result;
        S32 previousIndex = 0;
        S32 savedIndex = -1;

        for (S32 index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), 0); index != -1; savedIndex = index, index = ((UnicodeString*)mString)->indexOf(str.Data(), str.Length(), index + 1)) {
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
            if (savedIndex != previousIndex && (U32)previousIndex < Length() - 1) {
                result.push_back(Substring(previousIndex));
            }
        }

        return result;
    }

    bool String::StartsWith(String str) const
    {
        return ((UnicodeString*)mString)->startsWith(*((UnicodeString*)str.mString)) == TRUE;
    }

    bool String::StartsWith(String str, U32 offset, U32 size) const
    {
        if (offset > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("offset");
        } else if (size > (U32)((UnicodeString*)mString)->length() - offset) {
            throw OutOfRange("size");
        }

        return ((UnicodeString*)mString)->startsWith(*((UnicodeString*)str.mString), offset, size) == TRUE;
    }

    String String::Substring(U32 startIndex) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        }

        return String(new UnicodeString(((UnicodeString*)mString)->getTerminatedBuffer() + startIndex));
    }

    String String::Substring(U32 startIndex, U32 count) const
    {
        if (startIndex > (U32)((UnicodeString*)mString)->length()) {
            throw OutOfRange("startIndex");
        } else if (count > (U32)((UnicodeString*)mString)->length() - startIndex) {
            throw OutOfRange("count");
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

    std::string String::ToUTF8() const
    {
        std::string result;
        return ((UnicodeString*)mString)->toUTF8String<std::string>(result);
    }

    std::u16string String::ToUTF16() const
    {
        return std::u16string((const char16_t*)((UnicodeString*)mString)->getTerminatedBuffer());
    }

    std::u32string String::ToUTF32() const
    {
        UErrorCode errorCode;
        Char32* utf32 = new Char32[((UnicodeString*)mString)->countChar32()];
        ((UnicodeString*)mString)->toUTF32(force_cast<UChar32*>(utf32), ((UnicodeString*)mString)->countChar32(), errorCode);

        if (errorCode != U_ZERO_ERROR) {
            throw RuntimeError("Error while converting to UTF32");
        }

        std::u32string result((char32_t*)utf32);
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
        mCount = new U32(1);
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

    String String::FromUTF8(const std::string& str)
    {
        return String(new UnicodeString(UnicodeString::fromUTF8(StringPiece(str.c_str(), str.length()))));
    }

    String String::FromUTF16(const std::u16string& str)
    {
        return String((const UChar*)str.data());
    }

    String String::FromUTF32(const std::u32string& str)
    {
        return String(new UnicodeString(UnicodeString::fromUTF32((const UChar32*)str.data(), str.length())));
    }

    U32 String::AddRef()
    {
        if (mCount) {
            return (++(*mCount));
        } else {
            return 0;
        }
    }

    U32 String::ReleaseRef()
    {
        if (mCount) {
            return (--(*mCount));
        } else {
            return 0;
        }
    }

    U32 String::RefCount() const
    {
        if (mCount) {
            return *mCount;
        } else {
            return 0;
        }
    }

    U32 String::ComputeCapacity(U32 length)
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
        return Text::Encoding::UTF8()->GetString(Vector<U8>((U8*)&wc, ((U8*)&wc) + sizeof(wchar_t)))[0];
#endif
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

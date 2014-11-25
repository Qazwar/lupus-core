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

#include "Utility.h"
#include "IClonable.h"
#include <vector>
#include <functional>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    LUPUSCORE_API Char ToChar(char);
    LUPUSCORE_API Char ToChar(wchar_t);

    enum class StringSplitOption {
        None,
        RemoveEmptyEntries
    };

    enum class StringCaseSensitivity {
        CaseSensitive,
        CaseInsensitive
    };

    class LUPUSCORE_API String
    {
    public:

        typedef Char* iterator;
        typedef const Char* const_iterator;

        inline iterator begin() { return &this->operator[](0); }
        inline const_iterator begin() const { return &this->operator[](0); }
        inline const_iterator cbegin() const { return &this->operator[](0); }
        inline iterator end() { return &this->operator[](this->Length()); }
        inline const_iterator end() const { return &this->operator[](this->Length()); }
        inline const_iterator cend() const { return &this->operator[](this->Length()); }

        String();
        String(Char ch, U32 count = 1) NOEXCEPT;
        String(const char* str) throw(RuntimeError);
        String(const Char* str) NOEXCEPT;
        String(const Char* str, U32 offset, U32 size) throw(OutOfRange);
        String(const Vector<Char>& chars) NOEXCEPT;
        String(const Vector<Char>& chars, U32 offset, U32 size) throw(OutOfRange);
        String(const std::string& str) NOEXCEPT;
        String(const std::string& str, U32 offset, U32 size) throw(OutOfRange);
        String(const String& str) NOEXCEPT;
        String(const String& str, U32 offset, U32 size) throw(OutOfRange);
        String(String&&) NOEXCEPT;
        virtual ~String();

        Char& operator[](U32 index) throw(OutOfRange);
        const Char& operator[](U32 index) const throw(OutOfRange);
        virtual String Clone() const NOEXCEPT;
        virtual const Char* Data() const NOEXCEPT;
        virtual const Char* Data(U32 startIndex) const throw(OutOfRange);
        virtual bool IsEmpty() const NOEXCEPT;
        virtual U32 Length() const NOEXCEPT;

        virtual String Append(Char ch) const NOEXCEPT;
        virtual String Append(String str) const NOEXCEPT;
        virtual String Append(String str, U32 offset, U32 size) const throw(OutOfRange);
        virtual int Compare(String str, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const NOEXCEPT;
        virtual int Compare(String str, U32 offset, U32 size, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const throw(OutOfRange);
        virtual int Compare(U32 offset, U32 size, String cmpString, U32 cmpOffset, U32 cmpSize, StringCaseSensitivity = StringCaseSensitivity::CaseSensitive) const throw(OutOfRange);
        virtual bool Contains(String str) const NOEXCEPT;
        virtual void CopyTo(U32 srcIndex, Vector<Char>& dst, U32 dstIndex, U32 count) const throw(OutOfRange);
        virtual bool EndsWith(String str) const NOEXCEPT;
        virtual bool EndsWith(String str, U32 offset, U32 size) const throw(OutOfRange);
        virtual int IndexOf(Char ch) const NOEXCEPT;
        virtual int IndexOf(String str) const NOEXCEPT;
        virtual int IndexOf(Char ch, U32 offset) const throw(OutOfRange);
        virtual int IndexOf(String str, U32 offset) const throw(OutOfRange);
        virtual int IndexOf(Char ch, U32 offset, U32 count) const throw(OutOfRange);
        virtual int IndexOf(String str, U32 offset, U32 count) const throw(OutOfRange);
        virtual int IndexOfAny(const Vector<Char>& chars) const NOEXCEPT;
        virtual int IndexOfAny(const Vector<Char>& chars, U32 offset) const throw(OutOfRange);
        virtual int IndexOfAny(const Vector<Char>& chars, U32 offset, U32 count) const throw(OutOfRange);
        virtual String Insert(U32 startIndex, Char ch) const throw(OutOfRange);
        virtual String Insert(U32 startIndex, String str) const throw(OutOfRange);
        virtual String Insert(U32 startIndex, String str, U32 offset, U32 count) const throw(OutOfRange);
        virtual int LastIndexOf(Char ch) const NOEXCEPT;
        virtual int LastIndexOf(String str) const NOEXCEPT;
        virtual int LastIndexOf(Char ch, U32 offset) const throw(OutOfRange);
        virtual int LastIndexOf(String str, U32 offset) const throw(OutOfRange);
        virtual int LastIndexOf(Char ch, U32 offset, U32 count) const throw(OutOfRange);
        virtual int LastIndexOf(String str, U32 offset, U32 count) const throw(OutOfRange);
        virtual int LastIndexOfAny(const Vector<Char>& chars) const NOEXCEPT;
        virtual int LastIndexOfAny(const Vector<Char>& chars, U32 offset) const throw(OutOfRange);
        virtual int LastIndexOfAny(const Vector<Char>& chars, U32 offset, U32 count) const throw(OutOfRange);
        virtual String Remove(U32 startIndex) const throw(OutOfRange);
        virtual String Remove(U32 startIndex, U32 count) const throw(OutOfRange);
        virtual String Replace(Char oldCh, Char newCh) const NOEXCEPT;
        virtual String Replace(String oldStr, String newStr) const throw(OutOfRange);
        virtual String Reverse() const NOEXCEPT;
        virtual String Reverse(U32 startIndex, U32 count) const throw(OutOfRange);
        virtual Vector<String> Split(const Vector<Char>& delimiter, StringSplitOption = StringSplitOption::None) const throw(FormatError);
        virtual Vector<String> Split(const Vector<Char>& delimiter, U32 count, StringSplitOption = StringSplitOption::None) const throw(FormatError);
        virtual Vector<String> Split(const String& delimiter, StringSplitOption = StringSplitOption::None) const throw(FormatError);
        virtual Vector<String> Split(const String& delimiter, U32 count, StringSplitOption = StringSplitOption::None) const throw(FormatError);
        virtual bool StartsWith(String str) const NOEXCEPT;
        virtual bool StartsWith(String str, U32 offset, U32 size) const throw(OutOfRange);
        virtual String Substring(U32 startIndex) const throw(OutOfRange);
        virtual String Substring(U32 startIndex, U32 count) const throw(OutOfRange);
        virtual String ToLower() const NOEXCEPT;
        virtual String ToUpper() const NOEXCEPT;
        virtual std::string ToUTF8() const NOEXCEPT;
        virtual std::u16string ToUTF16() const NOEXCEPT;
        virtual std::u32string ToUTF32() const throw(RuntimeError);
        virtual String Trim() const NOEXCEPT;

        bool operator==(String str) const NOEXCEPT;
        bool operator!=(String str) const NOEXCEPT;
        bool operator<(String str) const NOEXCEPT;
        bool operator>(String str) const NOEXCEPT;
        bool operator<=(String str) const NOEXCEPT;
        bool operator>=(String str) const NOEXCEPT;
        String operator+(Char ch) const NOEXCEPT;
        String operator+(const String& str) const NOEXCEPT;
        String& operator=(Char ch) NOEXCEPT;
        String& operator=(const String& str) NOEXCEPT;
        String& operator=(String&&);
        String& operator+=(Char ch) NOEXCEPT;
        String& operator+=(const String& str) NOEXCEPT;

        static String FromUTF8(const std::string& str);
        static String FromUTF16(const std::u16string& str);
        static String FromUTF32(const std::u32string& str);

    protected:

        U32 AddRef();
        U32 ReleaseRef();
        U32 RefCount() const;

        static const U32 Capacity;
        static U32 ComputeCapacity(U32 length);

    private:

        explicit String(void*);

        void* mString = nullptr;
        U32* mCount = nullptr;
#ifdef _DEBUG
        std::string mDebugString;
#endif
    };

    template <typename CharT>
    inline String operator==(CharT lhs, const String& rhs)
    {
        return String(lhs) == rhs;
    }

    template <typename CharT>
    inline String operator==(const CharT* lhs, const String& rhs)
    {
        return String(lhs) == rhs;
    }

    template <typename CharT>
    inline String operator!=(CharT lhs, const String& rhs)
    {
        return String(lhs) != rhs;
    }

    template <typename CharT>
    inline String operator!=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) != rhs;
    }

    template <typename CharT>
    inline String operator<(const CharT* lhs, const String& rhs)
    {
        return String(lhs) < rhs;
    }

    template <typename CharT>
    inline String operator>(const CharT* lhs, const String& rhs)
    {
        return String(lhs) > rhs;
    }

    template <typename CharT>
    inline String operator<=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) <= rhs;
    }

    template <typename CharT>
    inline String operator>=(const CharT* lhs, const String& rhs)
    {
        return String(lhs) >= rhs;
    }

    template <typename CharT>
    inline String operator+(CharT lhs, const String& rhs)
    {
        return String(lhs) + rhs;
    }

    template <typename CharT>
    inline String operator+(const CharT* lhs, const String& rhs)
    {
        return String(lhs) + rhs;
    }
}

namespace std {
    template <>
    struct hash < Lupus::String >
    {
        typedef Lupus::String argument_type;
        typedef std::size_t result_type;

        hash() = default;
        hash(const hash&) = default;
        ~hash() = default;

        result_type operator()(const Lupus::String& str) const
        {
            return hash<string>()(str.ToUTF8());
        }
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

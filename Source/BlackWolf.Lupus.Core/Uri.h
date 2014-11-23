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
#include <vector>
#include <memory>
#include <utility>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUSCORE_API Uri : NonCopyable
    {
    public:

        Uri(const String& uriString) throw(RuntimeError, BadAlloc, FormatError);
        Uri(Pointer<Uri> baseUri, const String& uriString) throw(RuntimeError, BadAlloc, FormatError);
        Uri(Pointer<Uri> baseUri, Pointer<Uri> relativeUri) throw(RuntimeError, BadAlloc, FormatError);
        virtual ~Uri() = default;

        virtual const String& Scheme() const NOEXCEPT;
        virtual const String& UserInfo() const NOEXCEPT;
        virtual const String& HostText() const NOEXCEPT;
        virtual const String& HostData() const NOEXCEPT;
        virtual const String& PortText() const NOEXCEPT;
        virtual const Vector<String>& PathHead() const NOEXCEPT;
        virtual const Vector<String>& PathTail() const NOEXCEPT;
        virtual const String& Query() const NOEXCEPT;
        virtual const String& Fragment() const NOEXCEPT;
        virtual const String& OriginalString() const NOEXCEPT;
        virtual bool IsAbsolutePath() const NOEXCEPT;

        virtual String FullPath() const NOEXCEPT;
        virtual String ToString() const NOEXCEPT;

        static String Encode(const String&);
        static String Decode(const String&);
        static bool CheckSchemeName(const String&);

    private:

        String mScheme;
        String mUserInfo;
        String mHostText;
        String mHostData;
        String mPortText;
        Vector<String> mPathHead;
        Vector<String> mPathTail;
        String mQuery;
        String mFragment;
        String mOriginalString;
        bool mIsAbosultePath;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

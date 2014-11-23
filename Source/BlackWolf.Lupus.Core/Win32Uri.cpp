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
#include "Uri.h"

#ifdef _MSC_VER
#include "Integer.h"
#include <cwchar>
#include <algorithm>
#include <uriparser/Uri.h>
#include <unicode/uchar.h>



namespace Lupus {
    Uri::Uri(const String& uriString) :
        mOriginalString(uriString)
    {
        UriParserStateW state;
        UriUriW uri;
        int result;

        state.uri = &uri;

        if ((result = uriParseUriW(&state, uriString.Data())) != URI_SUCCESS) {
            uriFreeUriMembersW(&uri);

            switch (result) {
                case URI_ERROR_SYNTAX:
                    throw FormatError(std::string("Invalid char: '") + String(*state.errorPos).ToUTF8().c_str() + std::string("'"));
                case URI_ERROR_MALLOC:
                    throw BadAlloc();
                default:
                    throw RuntimeError("Could not parse given URI");
            }
        } else if ((result = uriNormalizeSyntaxW(&uri)) != URI_SUCCESS) {
            uriFreeUriMembersW(&uri);

            switch (result) {
                case URI_ERROR_SYNTAX:
                    throw FormatError(std::string("Invalid char: '") + String(*state.errorPos).ToUTF8().c_str() + std::string("'"));
                case URI_ERROR_MALLOC:
                    throw BadAlloc();
                default:
                    throw RuntimeError("Could not parse given URI");
            }
        }

        mScheme = uri.scheme.first ? String(uri.scheme.first, 0, uri.scheme.afterLast - uri.scheme.first) : "";
        mUserInfo = uri.userInfo.first ? String(uri.userInfo.first, 0, uri.userInfo.afterLast - uri.userInfo.first) : "";
        mHostText = uri.hostText.first ? String(uri.hostText.first, 0, uri.hostText.afterLast - uri.hostText.first) : "";
        mQuery = uri.query.first ? String(uri.query.first, 0, uri.query.afterLast - uri.query.first) : "";
        mFragment = uri.fragment.first ? String(uri.fragment.first, 0, uri.fragment.afterLast - uri.fragment.first) : "";
        mIsAbosultePath = uri.absolutePath != 0;

        for (auto it = uri.pathHead; it != NULL; it = it->next) {
            mPathHead.push_back(String(it->text.first, 0, it->text.afterLast - it->text.first));
        }

        for (auto it = uri.pathTail; it != NULL; it = it->next) {
            mPathTail.push_back(String(it->text.first, 0, it->text.afterLast - it->text.first));
        }

        uriFreeUriMembersW(&uri);
    }

    Uri::Uri(Pointer<Uri> baseUri, const String& uriString) :
        Uri(baseUri->ToString() + L'/' + uriString)
    {
    }

    Uri::Uri(Pointer<Uri> baseUri, Pointer<Uri> relativeUri) :
        Uri(baseUri->ToString() + L'/' + relativeUri->ToString())
    {
    }

    const String& Uri::UserInfo() const
    {
        return mUserInfo;
    }

    const String& Uri::HostText() const
    {
        return mHostText;
    }

    const String& Uri::HostData() const
    {
        return mHostData;
    }

    const String& Uri::PortText() const
    {
        return mPortText;
    }

    const Vector<String>& Uri::PathHead() const
    {
        return mPathHead;
    }

    const Vector<String>& Uri::PathTail() const
    {
        return mPathTail;
    }

    const String& Uri::Query() const
    {
        return mQuery;
    }

    const String& Uri::Fragment() const
    {
        return mFragment;
    }

    const String& Uri::Scheme() const
    {
        return mScheme;
    }

    const String& Uri::OriginalString() const
    {
        return mOriginalString;
    }

    bool Uri::IsAbsolutePath() const
    {
        return mIsAbosultePath;
    }

    String Uri::FullPath() const
    {
        String path;

        for_each(begin(mPathHead), end(mPathHead), [&path](const String& segment) {
            if (!segment.IsEmpty()) {
                path += L'/' + segment;
            }
        });

        if (mPathTail.empty() || mPathTail[0].IsEmpty()) {
            path += L'/';
        }

        return path;
    }

    String Uri::ToString() const
    {
        String uri;

        uri += mScheme.IsEmpty() ? L"" : mScheme + L"://";
        uri += mUserInfo.IsEmpty() ? L"" : mUserInfo + L'@';
        uri += mHostText.IsEmpty() ? L"" : mHostText;
        uri += mPathHead.empty() ? L"" : FullPath();
        uri += mQuery.IsEmpty() ? L"" : L'?' + mQuery;
        uri += mFragment.IsEmpty() ? L"" : L'#' + mFragment;

        return uri;
    }

    String Uri::Encode(const String& value)
    {
        if (value.IsEmpty()) {
            return "";
        }

        String result;
        wchar_t* buffer = new wchar_t[value.Length() * 6 + 1];

        memset(buffer, 0, value.Length() * 6 + 1);
        uriEscapeW(value.Data(), buffer, true, true);
        result = buffer;
        
        delete buffer;
        return result;
    }

    String Uri::Decode(const String& value)
    {
        if (value.IsEmpty()) {
            return "";
        }

        String result;
        wchar_t* buffer = new wchar_t[value.Length() + 1];
        
        memset(buffer, 0, value.Length() + 1);
        memcpy(buffer, value.Data(), value.Length());
        uriUnescapeInPlaceExW(buffer, true, URI_BR_DONT_TOUCH);
        result = buffer;

        delete buffer;
        return result;
    }

    bool Uri::CheckSchemeName(const String& value)
    {
        for (Char ch : value) {
            if (!u_isalnum((UChar)ch) || ch != L'.' || ch != L'+' || ch != L'-') {
                return false;
            }
        }

        return true;
    }
}
#endif

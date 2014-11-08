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
#include "Uri.h"

#ifdef _MSC_VER
#include "Integer.h"
#include <cwchar>
#include <algorithm>
#include <uriparser/Uri.h>

using namespace std;

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
                    throw format_error(string("Invalid char: '") + String(*state.errorPos).ToUTF8().c_str() + string("'"));
                case URI_ERROR_MALLOC:
                    throw bad_alloc();
                default:
                    throw runtime_error("Could not parse given URI");
            }
        } else if ((result = uriNormalizeSyntaxW(&uri)) != URI_SUCCESS) {
            uriFreeUriMembersW(&uri);

            switch (result) {
                case URI_ERROR_SYNTAX:
                    throw format_error(string("Invalid char: '") + String(*state.errorPos).ToUTF8().c_str() + string("'"));
                case URI_ERROR_MALLOC:
                    throw bad_alloc();
                default:
                    throw runtime_error("Could not parse given URI");
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

    Uri::Uri(shared_ptr<Uri> baseUri, const String& uriString) :
        Uri(baseUri->ToString() + L'/' + uriString)
    {
    }

    Uri::Uri(shared_ptr<Uri> baseUri, shared_ptr<Uri> relativeUri) :
        Uri(baseUri->ToString() + L'/' + relativeUri->ToString())
    {
    }

    const String& Uri::HostText() const
    {
        return mHostText;
    }

    const String& Uri::PortText() const
    {
        return mPortText;
    }

    const vector<String>& Uri::PathHead() const
    {
        return mPathHead;
    }

    const vector<String>& Uri::PathTail() const
    {
        return mPathTail;
    }

    const String& Uri::Query() const
    {
        return mQuery;
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
            if (!u_isalnum(ch) || ch != L'.' || ch != L'+' || ch != L'-') {
                return false;
            }
        }

        return true;
    }
}
#endif

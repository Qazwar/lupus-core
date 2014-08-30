#include "Uri.h"
#include <cwchar>
#include <algorithm>
#include <uriparser/Uri.h>

using namespace std;

namespace Lupus {
    Uri::Uri(const string& uriString) :
        mOriginalString(uriString)
    {
        UriParserStateA state;
        UriUriA uri;
        int result;

        state.uri = &uri;

        if ((result = uriParseUriA(&state, uriString.c_str())) != URI_SUCCESS) {
            uriFreeUriMembersA(&uri);

            switch (result) {
                case URI_ERROR_SYNTAX:
                    throw format_error(string("Invalid char: '") + *state.errorPos + string("'"));
                case URI_ERROR_MALLOC:
                    throw bad_alloc();
                default:
                    throw runtime_error("Could not parse given URI");
            }
        } else if ((result = uriNormalizeSyntaxA(&uri)) != URI_SUCCESS) {
            uriFreeUriMembersA(&uri);

            switch (result) {
                case URI_ERROR_SYNTAX:
                    throw format_error(string("Invalid char: '") + *state.errorPos + string("'"));
                case URI_ERROR_MALLOC:
                    throw bad_alloc();
                default:
                    throw runtime_error("Could not parse given URI");
            }
        }

        mScheme = string(uri.scheme.first, uri.scheme.afterLast - 1);
        mUserInfo = string(uri.userInfo.first, uri.userInfo.afterLast - 1);
        mHostText = string(uri.hostText.first, uri.hostText.afterLast - 1);
        mQuery = string(uri.query.first, uri.query.afterLast - 1);
        mFragment = string(uri.fragment.first, uri.fragment.afterLast - 1);
        mIsAbosultePath = uri.absolutePath != 0;

        for (auto it = uri.pathHead; it != NULL; it = it->next) {
            mPathHead.push_back(string(it->text.first, it->text.afterLast - 1));
        }

        for (auto it = uri.pathTail; it != NULL; it = it->next) {
            mPathTail.push_back(string(it->text.first, it->text.afterLast - 1));
        }

        uriFreeUriMembersA(&uri);
    }

    Uri::Uri(shared_ptr<Uri> baseUri, const string& uriString) :
        Uri(baseUri->ToString() + uriString)
    {
    }

    Uri::Uri(shared_ptr<Uri> baseUri, shared_ptr<Uri> relativeUri) :
        Uri(baseUri->ToString() + relativeUri->ToString())
    {
    }

    Uri::Uri(const wstring& uriString)
    {
        throw runtime_error("not implemented");
    }

    Uri::Uri(shared_ptr<Uri> baseUri, const wstring& uriString)
    {
        throw runtime_error("not implemented");
    }

    const string& Uri::HostText() const
    {
        return mHostText;
    }

    const string& Uri::PortText() const
    {
        return mPortText;
    }

    const vector<string>& Uri::PathHead() const
    {
        return mPathHead;
    }

    const vector<string>& Uri::PathTail() const
    {
        return mPathTail;
    }

    const string& Uri::Query() const
    {
        return mQuery;
    }

    const string& Uri::Scheme() const
    {
        return mScheme;
    }

    const string& Uri::OriginalString() const
    {
        return mOriginalString;
    }

    bool Uri::IsAbsolutePath() const
    {
        return mIsAbosultePath;
    }

    string Uri::FullPath() const
    {
        string path;

        for_each(begin(mPathHead), end(mPathHead), [&path](const string& segment) {
            if (!segment.empty()) {
                if (path.empty()) {
                    path += segment;
                } else {
                    path += "/" + segment;
                }
            }
        });

        return path;
    }

    string Uri::ToString() const
    {
        string uri;

        uri += mScheme.empty() ? "" : mScheme + "://";
        uri += mUserInfo.empty() ? "" : mUserInfo + "@";
        uri += mHostText.empty() ? "" : mHostText + "/";
        uri += mPathHead.empty() ? "" : FullPath();
        uri += mQuery.empty() ? "" : "?" + mQuery;
        uri += mFragment.empty() ? "" : "#" + mFragment;

        return uri;
    }

    string Uri::Encode(const string& value)
    {
        if (value.empty()) {
            return "";
        }

        string result;
        char* buffer = new char[value.size() * 3 + 1];

        memset(buffer, 0, value.size() * 3 + 1);
        uriEscapeA(value.c_str(), buffer, true, true);
        result = buffer;
        
        delete buffer;
        return result;
    }

    string Uri::Decode(const string& value)
    {
        if (value.empty()) {
            return "";
        }

        string result;
        char* buffer = new char[value.size() + 1];
        
        memset(buffer, 0, value.size() + 1);
        memcpy(buffer, value.data(), value.size());
        uriUnescapeInPlaceExA(buffer, true, URI_BR_DONT_TOUCH);
        result = buffer;

        delete buffer;
        return result;
    }

    bool Uri::CheckSchemeName(const string& value)
    {
        return value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890.+-") != value.npos;
    }

    wstring Uri::Encode(const wstring& value)
    {
        if (value.empty()) {
            return L"";
        }

        wstring result;
        wchar_t* buffer = new wchar_t[value.size() * 3 + 1];

        wmemset(buffer, 0, value.size() * 3 + 1);
        uriEscapeW(value.c_str(), buffer, true, true);
        result = buffer;

        delete buffer;
        return result;
    }

    wstring Uri::Decode(const wstring& value)
    {
        if (value.empty()) {
            return L"";
        }

        wstring result;
        wchar_t* buffer = new wchar_t[value.size() + 1];

        wmemset(buffer, 0, value.size() + 1);
        wmemcpy(buffer, value.data(), value.size());
        uriUnescapeInPlaceExW(buffer, true, URI_BR_DONT_TOUCH);
        result = buffer;

        delete buffer;
        return result;
    }

    bool Uri::CheckSchemeName(const wstring& value)
    {
        return value.find_first_not_of(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234567890.+-") != value.npos;
    }
}

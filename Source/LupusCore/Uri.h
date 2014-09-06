#pragma once

#include "String.h"
#include <vector>
#include <memory>
#include <utility>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUS_API Uri : boost::noncopyable
    {
    public:

        Uri(const String& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, const String& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, std::shared_ptr<Uri> relativeUri) throw(std::runtime_error, std::bad_alloc, format_error);

        const String& Scheme() const NOEXCEPT;
        const String& UserInfo() const NOEXCEPT;
        const String& HostText() const NOEXCEPT;
        const String& HostData() const NOEXCEPT;
        const String& PortText() const NOEXCEPT;
        const std::vector<String>& PathHead() const NOEXCEPT;
        const std::vector<String>& PathTail() const NOEXCEPT;
        const String& Query() const NOEXCEPT;
        const String& Fragment() const NOEXCEPT;
        const String& OriginalString() const NOEXCEPT;
        bool IsAbsolutePath() const NOEXCEPT;

        String FullPath() const NOEXCEPT;
        String ToString() const NOEXCEPT;

        static String Encode(const String&);
        static String Decode(const String&);
        static bool CheckSchemeName(const String&);

    private:

        String mScheme;
        String mUserInfo;
        String mHostText;
        String mHostData;
        String mPortText;
        std::vector<String> mPathHead;
        std::vector<String> mPathTail;
        String mQuery;
        String mFragment;
        String mOriginalString;
        bool mIsAbosultePath;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#pragma once

#include "Utility.h"
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

        Uri(const std::string& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(const std::wstring& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, const std::string& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, const std::wstring& uriString) throw(std::runtime_error, std::bad_alloc, format_error);
        Uri(std::shared_ptr<Uri> baseUri, std::shared_ptr<Uri> relativeUri) throw(std::runtime_error, std::bad_alloc, format_error);

        const std::string& Scheme() const NOEXCEPT;
        const std::string& UserInfo() const NOEXCEPT;
        const std::string& HostText() const NOEXCEPT;
        const std::string& HostData() const NOEXCEPT;
        const std::string& PortText() const NOEXCEPT;
        const std::vector<std::string>& PathHead() const NOEXCEPT;
        const std::vector<std::string>& PathTail() const NOEXCEPT;
        const std::string& Query() const NOEXCEPT;
        const std::string& Fragment() const NOEXCEPT;
        const std::string& OriginalString() const NOEXCEPT;
        bool IsAbsolutePath() const NOEXCEPT;

        std::string FullPath() const NOEXCEPT;
        std::string ToString() const NOEXCEPT;

        static std::string Encode(const std::string&);
        static std::string Decode(const std::string&);
        static bool CheckSchemeName(const std::string&);
        static std::wstring Encode(const std::wstring&);
        static std::wstring Decode(const std::wstring&);
        static bool CheckSchemeName(const std::wstring&);

    private:

        std::string mScheme;
        std::string mUserInfo;
        std::string mHostText;
        std::string mHostData;
        std::string mPortText;
        std::vector<std::string> mPathHead;
        std::vector<std::string> mPathTail;
        std::string mQuery;
        std::string mFragment;
        std::string mOriginalString;
        bool mIsAbosultePath;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

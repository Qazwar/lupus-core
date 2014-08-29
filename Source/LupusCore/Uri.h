#pragma once

#include "Utility.h"
#include <vector>
#include <memory>
#include <boost/noncopyable.hpp>

namespace Lupus {
    class LUPUS_API Uri : boost::noncopyable
    {
    public:

        Uri(const std::string& uriString) NOEXCEPT;
        Uri(std::shared_ptr<Uri> baseUri, const std::string& uriString) NOEXCEPT;
        Uri(std::shared_ptr<Uri> baseUri, std::shared_ptr<Uri> relativeUri) NOEXCEPT;

        const std::string& Host() const NOEXCEPT;
        const std::string& Port() const NOEXCEPT;
        const std::string& Path() const NOEXCEPT;
        const std::string& Query() const NOEXCEPT;
        const std::string& Schema() const NOEXCEPT;
        std::string PathAndQuery() const NOEXCEPT;
        const std::string& OriginalString() const NOEXCEPT;
        std::vector<std::string> Segments() const NOEXCEPT;

        std::string ToString() const NOEXCEPT;

    private:

        std::string mHost;
        std::string mPort;
        std::string mPath;
        std::string mQuery;
        std::string mSchema;
        std::string mOriginalString;
    };
}

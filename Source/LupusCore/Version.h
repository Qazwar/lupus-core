#pragma once

#include "Utility.h"
#include "IClonable.h"
#include <boost/noncopyable.hpp>

namespace Lupus {
    // TODO: Code schreiben.

    class Version : public boost::noncopyable, public IClonable
    {
    public:

        Version() = default;
        Version(const std::string&) throw(format_error);
        Version(int major, int minor) NOEXCEPT;
        Version(int major, int minor, int build) NOEXCEPT;
        Version(int major, int minor, int build, int revision) NOEXCEPT;

        int Major() const NOEXCEPT;
        int Minor() const NOEXCEPT;
        int Build() const NOEXCEPT;
        int Revision() const NOEXCEPT;
        short MajorRevision() const NOEXCEPT;
        short MinorRevision() const NOEXCEPT;

        std::shared_ptr<IClonable> Clone() const NOEXCEPT override;
        std::string ToString() const NOEXCEPT;

        bool operator==(std::shared_ptr<Version>) const;
        bool operator!=(std::shared_ptr<Version>) const;
        bool operator>=(std::shared_ptr<Version>) const;
        bool operator>(std::shared_ptr<Version>) const;
        bool operator<=(std::shared_ptr<Version>) const;
        bool operator<(std::shared_ptr<Version>) const;

        static std::shared_ptr<Version> Parse(const std::string& value) throw(format_error);
        static bool TryParse(const std::string& value, std::shared_ptr<Version>& result) NOEXCEPT;

    private:

        int mBuild = -1;
        int mMajor = -1;
        int mMinor = -1;
        int mRevision = -1;
    };
}

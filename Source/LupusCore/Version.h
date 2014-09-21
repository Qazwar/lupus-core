#pragma once

#include "String.h"
#include "IClonable.h"
#include <cstdint>
#include <boost/noncopyable.hpp>

namespace Lupus {
    class LUPUS_API Version : public boost::noncopyable, public IClonable<Version>
    {
    public:

        Version() = default;
        Version(const String&) throw(format_error);
        Version(int32_t major, int32_t minor) NOEXCEPT;
        Version(int32_t major, int32_t minor, int32_t build) NOEXCEPT;
        Version(int32_t major, int32_t minor, int32_t build, int32_t revision) NOEXCEPT;

        int32_t Major() const NOEXCEPT;
        int32_t Minor() const NOEXCEPT;
        int32_t Build() const NOEXCEPT;
        int32_t Revision() const NOEXCEPT;
        int16_t MajorRevision() const NOEXCEPT;
        int16_t MinorRevision() const NOEXCEPT;

        std::shared_ptr<Version> Clone() const NOEXCEPT override;
        String ToString() const NOEXCEPT;

        bool operator==(std::shared_ptr<Version>) const;
        bool operator!=(std::shared_ptr<Version>) const;
        bool operator>=(std::shared_ptr<Version>) const;
        bool operator>(std::shared_ptr<Version>) const;
        bool operator<=(std::shared_ptr<Version>) const;
        bool operator<(std::shared_ptr<Version>) const;

        static std::shared_ptr<Version> Parse(const String& value) throw(format_error);
        static bool TryParse(const String& value, std::shared_ptr<Version>& result) NOEXCEPT;

    private:

        int32_t mBuild = -1;
        int32_t mMajor = -1;
        int32_t mMinor = -1;
        int32_t mRevision = -1;
    };
}

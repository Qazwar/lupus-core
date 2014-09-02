#include "Version.h"
#include "Integer.h"
#include <vector>

using namespace std;

namespace Lupus {
    Version::Version(const string& version)
    {
        vector<int> numbers(4, -1);
        
        for (size_t n = version.find('.'), o = 0, i = 0; n != version.npos && i < 4; o = n, n = version.find('.', n), i++) {
            int num = -1;

            if (!Integer::TryParse(version.substr(o, n), num)) {
                throw format_error("Invalid version number");
            }

            numbers[i] = num;
        }

        Version::Version(numbers[0], numbers[1], numbers[2], numbers[3]);
    }

    Version::Version(int32_t major, int32_t minor) :
        Version(major, minor, -1, -1)
    {
    }

    Version::Version(int32_t major, int32_t minor, int32_t build) :
        Version(major, minor, build, -1)
    {
    }

    Version::Version(int32_t major, int32_t minor, int32_t build, int32_t revision) :
        mMajor(major), mMinor(minor), mBuild(build), mRevision(revision)
    {
    }

    int32_t Version::Major() const
    {
        return mMajor;
    }

    int32_t Version::Minor() const
    {
        return mMinor;
    }

    int32_t Version::Build() const
    {
        return mBuild;
    }

    int32_t Version::Revision() const
    {
        return mRevision;
    }

    int16_t Version::MajorRevision() const
    {
        if (mRevision == -1) {
            return -1;
        } else {
            return (short)((mRevision >> 16) & 0x0000ffff);
        }
    }

    int16_t Version::MinorRevision() const
    {
        if (mRevision == -1) {
            return -1;
        } else {
            return (short)(mRevision & 0x0000ffff);
        }
    }

    shared_ptr<IClonable> Version::Clone() const
    {
        return make_shared<Version>(mMajor, mMinor, mBuild, mRevision);
    }

    string Version::ToString() const
    {
        string result;

        result += mMajor > 0 ? (result.empty() ? "" : ".") + Integer::ToString(mMajor) : "";
        result += mMinor > 0 ? (result.empty() ? "" : ".") + Integer::ToString(mMinor) : "";
        result += mBuild > 0 ? (result.empty() ? "" : ".") + Integer::ToString(mBuild) : "";
        result += mRevision > 0 ? (result.empty() ? "" : ".") + Integer::ToString(mRevision) : "";

        return result;
    }

    bool Version::operator==(shared_ptr<Version> version) const
    {
        return (
            mMajor == version->Major() &&
            mMinor == version->Minor() &&
            mBuild == version->Build() &&
            mRevision == version->Revision()
        );
    }

    bool Version::operator!=(shared_ptr<Version> version) const
    {
        return (
            mMajor != version->Major() ||
            mMinor != version->Minor() ||
            mBuild != version->Build() ||
            mRevision != version->Revision()
        );
    }

    bool Version::operator>=(shared_ptr<Version> version) const
    {
        return (
            mMajor >= version->Major() ||
            mMinor >= version->Minor() ||
            mBuild >= version->Build() ||
            mRevision >= version->Revision()
        );
    }

    bool Version::operator>(shared_ptr<Version> version) const
    {
        return (
            mMajor > version->Major() ||
            mMinor > version->Minor() ||
            mBuild > version->Build() ||
            mRevision > version->Revision()
        );
    }

    bool Version::operator<=(shared_ptr<Version> version) const
    {
        return (
            mMajor <= version->Major() ||
            mMinor <= version->Minor() ||
            mBuild <= version->Build() ||
            mRevision <= version->Revision()
        );
    }

    bool Version::operator<(shared_ptr<Version> version) const
    {
        return (
            mMajor < version->Major() ||
            mMinor < version->Minor() ||
            mBuild < version->Build() ||
            mRevision < version->Revision()
        );
    }

    shared_ptr<Version> Version::Parse(const string& value)
    {
        vector<int> numbers(4, -1);

        for (size_t n = value.find('.'), o = 0, i = 0; n != value.npos && i < 4; o = n, n = value.find('.', n), i++) {
            int num = -1;

            if (!Integer::TryParse(value.substr(o, n), num)) {
                throw format_error("Invalid version number");
            }

            numbers[i] = num;
        }

        return make_shared<Version>(numbers[0], numbers[1], numbers[2], numbers[3]);
    }

    bool Version::TryParse(const string& value, shared_ptr<Version>& result)
    {
        try {
            result = Version::Parse(value);
        } catch (format_error&) {
            return false;
        }

        return true;
    }
}

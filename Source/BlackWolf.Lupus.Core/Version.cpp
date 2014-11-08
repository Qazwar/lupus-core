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
#include "Version.h"
#include "Integer.h"
#include <vector>

using namespace std;

namespace Lupus {
    Version::Version(const String& version)
    {
        vector<int> numbers(4, -1);
        
        for (int n = version.IndexOf("."), o = 0, i = 0; n != -1 && i < 4; o = n, n = version.IndexOf(".", n), i++) {
            int num = -1;

            if (!Integer::TryParse(version.Substring(o, n), num)) {
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

    shared_ptr<Version> Version::Clone() const
    {
        return make_shared<Version>(mMajor, mMinor, mBuild, mRevision);
    }

    String Version::ToString() const
    {
        String result;

        result += mMajor > 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mMajor) : "";
        result += mMinor > 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mMinor) : "";
        result += mBuild > 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mBuild) : "";
        result += mRevision > 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mRevision) : "";

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

    shared_ptr<Version> Version::Parse(const String& value)
    {
        vector<int> numbers(4, -1);

        for (int n = value.IndexOf("."), o = 0, i = 0; o != -1 && i < 4; o = n == -1 ? -1 : n + 1, n = value.IndexOf(".", n + 1), i++) {
            int num = -1;

            if (n != -1) {
                if (!Integer::TryParse(value.Substring(o, n), num)) {
                    throw format_error("Invalid version number");
                }
            } else {
                if (!Integer::TryParse(value.Substring(o), num)) {
                    throw format_error("Invalid version number");
                }
            }

            numbers[i] = num;
        }

        return make_shared<Version>(numbers[0], numbers[1], numbers[2], numbers[3]);
    }

    bool Version::TryParse(const String& value, shared_ptr<Version>& result)
    {
        try {
            result = Version::Parse(value);
        } catch (format_error&) {
            return false;
        }

        return true;
    }
}

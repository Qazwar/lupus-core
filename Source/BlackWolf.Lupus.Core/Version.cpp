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

        result += mMajor >= 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mMajor) : "";
        result += mMinor >= 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mMinor) : "";
        result += mBuild >= 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mBuild) : "";
        result += mRevision >= 0 ? (result.IsEmpty() ? "" : ".") + Integer::ToString(mRevision) : "";

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

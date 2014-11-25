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
#pragma once

#include "String.h"
#include "IClonable.h"
#include <cstdint>

namespace Lupus {
    class LUPUSCORE_API Version : public NonCopyable, public IClonable<Version>
    {
    public:

        Version() = default;
        Version(const String&) throw(FormatError);
        Version(S32 major, S32 minor) NOEXCEPT;
        Version(S32 major, S32 minor, S32 build) NOEXCEPT;
        Version(S32 major, S32 minor, S32 build, S32 revision) NOEXCEPT;
        virtual ~Version() = default;

        virtual S32 Major() const NOEXCEPT;
        virtual S32 Minor() const NOEXCEPT;
        virtual S32 Build() const NOEXCEPT;
        virtual S32 Revision() const NOEXCEPT;
        virtual S16 MajorRevision() const NOEXCEPT;
        virtual S16 MinorRevision() const NOEXCEPT;

        virtual Pointer<Version> Clone() const NOEXCEPT override;
        virtual String ToString() const NOEXCEPT;

        bool operator==(Pointer<Version>) const;
        bool operator!=(Pointer<Version>) const;
        bool operator>=(Pointer<Version>) const;
        bool operator>(Pointer<Version>) const;
        bool operator<=(Pointer<Version>) const;
        bool operator<(Pointer<Version>) const;

        static Pointer<Version> Parse(const String& value) throw(FormatError);
        static bool TryParse(const String& value, Pointer<Version>& result) NOEXCEPT;

    private:

        S32 mBuild = -1;
        S32 mMajor = -1;
        S32 mMinor = -1;
        S32 mRevision = -1;
    };
}

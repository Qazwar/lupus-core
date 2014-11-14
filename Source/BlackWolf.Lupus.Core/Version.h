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
        Version(const String&) throw(format_error);
        Version(int32_t major, int32_t minor) NOEXCEPT;
        Version(int32_t major, int32_t minor, int32_t build) NOEXCEPT;
        Version(int32_t major, int32_t minor, int32_t build, int32_t revision) NOEXCEPT;
        virtual ~Version() = default;

        virtual int32_t Major() const NOEXCEPT;
        virtual int32_t Minor() const NOEXCEPT;
        virtual int32_t Build() const NOEXCEPT;
        virtual int32_t Revision() const NOEXCEPT;
        virtual int16_t MajorRevision() const NOEXCEPT;
        virtual int16_t MinorRevision() const NOEXCEPT;

        virtual std::shared_ptr<Version> Clone() const NOEXCEPT override;
        virtual String ToString() const NOEXCEPT;

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

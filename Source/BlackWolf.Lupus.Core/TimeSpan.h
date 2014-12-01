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
#include "Utility.h"
#include "IStringifyable.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    class LUPUSCORE_API TimeSpan : public IStringifyable
    {
    public:
        TimeSpan(const TimeSpan&) = default;
        TimeSpan(TimeSpan&&);
        TimeSpan(S64 ticks);
        TimeSpan(S32 hours, S32 minutes, S32 seconds);
        TimeSpan(S32 days, S32 hours, S32 minutes, S32 seconds);
        TimeSpan(S32 days, S32 hours, S32 minutes, S32 seconds, S32 milliseconds);

        virtual S64 Ticks() const NOEXCEPT;
        virtual S32 Days() const NOEXCEPT;
        virtual S32 Hours() const NOEXCEPT;
        virtual S32 Minutes() const NOEXCEPT;
        virtual S64 Seconds() const NOEXCEPT;
        virtual S64 Milliseconds() const NOEXCEPT;
        virtual double TotalDays() const NOEXCEPT;
        virtual double TotalHours() const NOEXCEPT;
        virtual double TotalMinutes() const NOEXCEPT;
        virtual double TotalSeconds() const NOEXCEPT;
        virtual double TotalMilliseconds() const NOEXCEPT;

        virtual TimeSpan Add(TimeSpan timeSpan) const NOEXCEPT;
        virtual TimeSpan Duration() const NOEXCEPT;
        virtual TimeSpan Negate() const NOEXCEPT;
        virtual TimeSpan Subtract(TimeSpan timeSpan) const NOEXCEPT;

        TimeSpan& operator=(const TimeSpan&) = default;
        TimeSpan& operator=(TimeSpan&&)NOEXCEPT;
        bool operator==(const TimeSpan&) const NOEXCEPT;
        bool operator!=(const TimeSpan&) const NOEXCEPT;
        bool operator<(const TimeSpan&) const NOEXCEPT;
        bool operator<=(const TimeSpan&) const NOEXCEPT;
        bool operator>(const TimeSpan&) const NOEXCEPT;
        bool operator>=(const TimeSpan&) const NOEXCEPT;
        TimeSpan operator+(const TimeSpan& value) const NOEXCEPT;
        TimeSpan operator-(const TimeSpan& value) const NOEXCEPT;
        TimeSpan& operator+=(const TimeSpan& value) NOEXCEPT;
        TimeSpan& operator-=(const TimeSpan& value) NOEXCEPT;

        virtual String ToString() const NOEXCEPT override;
        virtual String ToString(String format) const NOEXCEPT;

    private:
        Tick mTicks = Tick(0);
    };

    LUPUSCORE_API TimeSpan operator+(S64 ticks, const TimeSpan& value);
    LUPUSCORE_API TimeSpan operator-(S64 ticks, const TimeSpan& value);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

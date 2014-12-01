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
#include "ISerializable.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    enum class WeekDay {
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    };

    enum class DateTimeKind {
        Unspecified,
        Local,
        Utc
    };

    class TimeSpan;

    class LUPUSCORE_API DateTime : public IStringifyable, public ISerializable
    {
    public:
        DateTime(const DateTime&) = default;
        DateTime(DateTime&&);
        DateTime(S64 ticks);
        DateTime(S32 year, S32 month, S32 day);
        DateTime(S32 year, S32 month, S32 day, DateTimeKind kind);
        DateTime(S32 year, S32 month, S32 day, S32 hour, S32 minute, S32 second);
        DateTime(S32 year, S32 month, S32 day, S32 hour, S32 minute, S32 second, DateTimeKind kind);
        ~DateTime() = default;

        virtual S64 Ticks() const NOEXCEPT;
        virtual S32 Year() const NOEXCEPT;
        virtual S32 Month() const NOEXCEPT;
        virtual S32 Day() const NOEXCEPT;
        virtual S32 Hour() const NOEXCEPT;
        virtual S32 Minute() const NOEXCEPT;
        virtual S32 Second() const NOEXCEPT;
        virtual WeekDay DayOfWeek() const NOEXCEPT;
        virtual S32 DayOfYear() const NOEXCEPT;
        virtual TimeSpan TimeOfDay() const NOEXCEPT;

        virtual DateTime Add(TimeSpan value) const NOEXCEPT;
        virtual DateTime AddTicks(S64 value) const NOEXCEPT;
        virtual DateTime AddYears(S32 value) const NOEXCEPT;
        virtual DateTime AddMonths(S32 value) const NOEXCEPT;
        virtual DateTime AddDays(double value) const NOEXCEPT;
        virtual DateTime AddHours(double value) const NOEXCEPT;
        virtual DateTime AddMinutes(double value) const NOEXCEPT;
        virtual DateTime AddSeconds(double value) const NOEXCEPT;
        virtual DateTime Subtract(TimeSpan value) const NOEXCEPT;
        virtual TimeSpan Subtract(DateTime value) const NOEXCEPT;

        DateTime& operator=(const DateTime&) = default;
        DateTime& operator=(DateTime&&) NOEXCEPT;
        bool operator==(const DateTime&) const NOEXCEPT;
        bool operator!=(const DateTime&) const NOEXCEPT;
        bool operator<(const DateTime&) const NOEXCEPT;
        bool operator<=(const DateTime&) const NOEXCEPT;
        bool operator>(const DateTime&) const NOEXCEPT;
        bool operator>=(const DateTime&) const NOEXCEPT;
        DateTime operator+(const TimeSpan& value) const NOEXCEPT;
        TimeSpan operator+(const DateTime& value) const NOEXCEPT;
        DateTime operator-(const TimeSpan& value) const NOEXCEPT;
        TimeSpan operator-(const DateTime& value) const NOEXCEPT;
        DateTime& operator+=(const TimeSpan& value) NOEXCEPT;
        DateTime& operator-=(const TimeSpan& value) NOEXCEPT;

        virtual String ToString() const NOEXCEPT override;
        virtual String ToString(String format) const NOEXCEPT;

        virtual Vector<U8> Serialize() const NOEXCEPT override;
        virtual void Deserialize(const Vector<U8>& data) throw(InvalidArgument) override;

        static DateTime Now() NOEXCEPT;
        static DateTime UtcNow() NOEXCEPT;

    protected:
        static std::tm FromTicks(Tick ticks);

    private:
        DateTime() = default;
        mutable std::tm mTime;
    };

    LUPUSCORE_API DateTime operator+(const TimeSpan&, const DateTime&);
    LUPUSCORE_API DateTime operator-(const TimeSpan&, const DateTime&);
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

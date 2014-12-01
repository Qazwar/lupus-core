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
#include "TimeSpan.h"
#include "String.h"
#include <sstream>
#include <iomanip>

using stringstream = std::stringstream;

namespace Lupus {
    TimeSpan::TimeSpan(TimeSpan&& timeSpan)
    {
        mTicks = std::move(timeSpan.mTicks);
    }

    TimeSpan::TimeSpan(S64 ticks)
    {
        mTicks = Tick(ticks);
    }

    TimeSpan::TimeSpan(S32 hours, S32 minutes, S32 seconds) :
        TimeSpan(0, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(S32 days, S32 hours, S32 minutes, S32 seconds) :
        TimeSpan(days, hours, minutes, seconds, 0)
    {
    }

    TimeSpan::TimeSpan(S32 days, S32 hours, S32 minutes, S32 seconds, S32 milliseconds)
    {
        mTicks = std::chrono::duration_cast<Tick>(
            Hour(24 * days) + 
            Hour(hours) + 
            Minute(minutes) + 
            Second(seconds) + 
            Millisecond(milliseconds)
        );
    }

    S64 TimeSpan::Ticks() const
    {
        return mTicks.count();
    }

    S32 TimeSpan::Days() const
    {
        return std::chrono::duration_cast<Day>(mTicks).count();
    }

    S32 TimeSpan::Hours() const
    {
        return std::chrono::duration_cast<Hour>(mTicks).count();
    }
    
    S32 TimeSpan::Minutes() const
    {
        return std::chrono::duration_cast<Minute>(mTicks).count();
    }
    
    S64 TimeSpan::Seconds() const
    {
        return std::chrono::duration_cast<Second>(mTicks).count();
    }
    
    S64 TimeSpan::Milliseconds() const
    {
        return std::chrono::duration_cast<Millisecond>(mTicks).count();
    }

    double TimeSpan::TotalDays() const
    {
        auto days = std::chrono::duration_cast<Day>(mTicks).count();

        return (
            static_cast<double>(days) +
            (std::chrono::duration_cast<Hour>(mTicks).count() / 24. - days) +
            (std::chrono::duration_cast<Minute>(mTicks).count() / 1440. - days) +
            (std::chrono::duration_cast<Second>(mTicks).count() / 86400. - days) +
            (std::chrono::duration_cast<Millisecond>(mTicks).count() / 86400000. - days)
        );
    }

    double TimeSpan::TotalHours() const
    {
        auto hours = std::chrono::duration_cast<Hour>(mTicks).count();

        return (
            static_cast<double>(hours) +
            (std::chrono::duration_cast<Minute>(mTicks).count() / 60. - hours) +
            (std::chrono::duration_cast<Second>(mTicks).count() / 3600. - hours) +
            (std::chrono::duration_cast<Millisecond>(mTicks).count() / 3600000. - hours)
        );
    }

    double TimeSpan::TotalMinutes() const
    {
        auto minutes = std::chrono::duration_cast<Minute>(mTicks).count();

        return (
            static_cast<double>(minutes) +
            (std::chrono::duration_cast<Second>(mTicks).count() / 60. - minutes) +
            (std::chrono::duration_cast<Millisecond>(mTicks).count() / 60000. - minutes)
        );
    }

    double TimeSpan::TotalSeconds() const
    {
        auto seconds = std::chrono::duration_cast<Second>(mTicks).count();

        return (
            static_cast<double>(seconds) +
            (std::chrono::duration_cast<Millisecond>(mTicks).count() / 1000. - seconds) +
            (std::chrono::duration_cast<Microsecond>(mTicks).count() / 1000000. - seconds)
        );
    }

    double TimeSpan::TotalMilliseconds() const
    {
        auto milliseconds = std::chrono::duration_cast<Millisecond>(mTicks).count();

        return (
            static_cast<double>(milliseconds) +
            (std::chrono::duration_cast<Microsecond>(mTicks).count() / 1000. - milliseconds) +
            (std::chrono::duration_cast<Nanosecond>(mTicks).count() / 1000000. - milliseconds)
        );
    }

    TimeSpan TimeSpan::Add(TimeSpan timeSpan) const
    {
        return TimeSpan((mTicks + timeSpan.mTicks).count());
    }

    TimeSpan TimeSpan::Duration() const
    {
        return TimeSpan(std::abs(mTicks.count()));
    }
    
    TimeSpan TimeSpan::Negate() const
    {
        return TimeSpan(std::negate<S64>()(mTicks.count()));
    }
    
    TimeSpan TimeSpan::Subtract(TimeSpan timeSpan) const
    {
        return TimeSpan((mTicks - timeSpan.mTicks).count());
    }

    TimeSpan& TimeSpan::operator=(TimeSpan&& timeSpan)
    {
        mTicks = std::move(timeSpan.mTicks);
        return *this;
    }

    bool TimeSpan::operator==(const TimeSpan& timeSpan) const
    {
        return mTicks == timeSpan.mTicks;
    }

    bool TimeSpan::operator!=(const TimeSpan& timeSpan) const
    {
        return mTicks != timeSpan.mTicks;
    }

    bool TimeSpan::operator<=(const TimeSpan& timeSpan) const
    {
        return mTicks <= timeSpan.mTicks;
    }

    bool TimeSpan::operator<(const TimeSpan& timeSpan) const
    {
        return mTicks < timeSpan.mTicks;
    }

    bool TimeSpan::operator>=(const TimeSpan& timeSpan) const
    {
        return mTicks >= timeSpan.mTicks;
    }

    bool TimeSpan::operator>(const TimeSpan& timeSpan) const
    {
        return mTicks > timeSpan.mTicks;
    }

    TimeSpan TimeSpan::operator+(const TimeSpan& timeSpan) const
    {
        return (mTicks + timeSpan.mTicks).count();
    }

    TimeSpan TimeSpan::operator-(const TimeSpan& timeSpan) const
    {
        return (mTicks - timeSpan.mTicks).count();
    }

    TimeSpan& TimeSpan::operator+=(const TimeSpan& timeSpan)
    {
        mTicks += timeSpan.mTicks;
        return *this;
    }

    TimeSpan& TimeSpan::operator-=(const TimeSpan& timeSpan)
    {
        mTicks -= timeSpan.mTicks;
        return *this;
    }

    String TimeSpan::ToString() const
    {
        stringstream ss;
        auto timePoint = TimePoint(mTicks);
        auto time = Clock::to_time_t(timePoint);
        tm timetm;

        memset(&timetm, 0, sizeof(timetm));
        localtime_s(&timetm, &time);
        ss << std::put_time(&timetm, "%c");
        return ss.str();
    }

    String TimeSpan::ToString(String format) const
    {
        stringstream ss;
        auto timePoint = TimePoint(mTicks);
        auto time = Clock::to_time_t(timePoint);
        tm timetm;

        memset(&timetm, 0, sizeof(timetm));
        localtime_s(&timetm, &time);
        ss << std::put_time(&timetm, format.ToUTF8().c_str());
        return ss.str();
    }

    TimeSpan operator+(S64 ticks, const TimeSpan& timeSpan)
    {
        return TimeSpan((Tick(ticks) + Tick(timeSpan.Ticks())).count());
    }

    TimeSpan operator-(S64 ticks, const TimeSpan& timeSpan)
    {
        return TimeSpan((Tick(ticks) - Tick(timeSpan.Ticks())).count());
    }
}

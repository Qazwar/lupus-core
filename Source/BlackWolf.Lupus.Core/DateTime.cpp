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
#include "DateTime.h"
#include "String.h"
#include "TimeSpan.h"
#include <sstream>
#include <iomanip>

using stringstream = std::stringstream;

namespace Lupus {
    DateTime::DateTime(DateTime&& date)
    {
        mTime = std::move(date.mTime);
    }

    DateTime::DateTime(S64 ticks)
    {
        mTime = FromTicks(Tick(ticks));
    }

    DateTime::DateTime(S32 year, S32 month, S32 day) :
        DateTime(year, month, day, 0, 0, 0, DateTimeKind::Unspecified)
    {
    }

    DateTime::DateTime(S32 year, S32 month, S32 day, DateTimeKind kind) :
        DateTime(year, month, day, 0, 0, 0, kind)
    {
    }

    DateTime::DateTime(S32 year, S32 month, S32 day, S32 hour, S32 minute, S32 second) :
        DateTime(year, month, day, hour, minute, second, DateTimeKind::Unspecified)
    {
    }

    DateTime::DateTime(S32 year, S32 month, S32 day, S32 hour, S32 minute, S32 second, DateTimeKind kind)
    {
        {
            std::time_t time;

            switch (kind) {
            case DateTimeKind::Unspecified:
                memset(&mTime, 0, sizeof(mTime));
                mTime.tm_isdst = -1;
                break;

            case DateTimeKind::Utc:
                std::time(&time);
                gmtime_s(&mTime, &time);
                break;

            case DateTimeKind::Local:
                std::time(&time);
                localtime_s(&mTime, &time);
                break;
            }
        }

        mTime.tm_year = year - 1900;
        mTime.tm_mon = month - 1;
        mTime.tm_mday = day;
        mTime.tm_hour = hour;
        mTime.tm_min = minute;
        mTime.tm_sec = second;
        mktime(&mTime);
    }

    S64 DateTime::Ticks() const
    {
        auto time = mktime(&mTime);
        auto timePoint = Clock::from_time_t(time);
        return (Clock::time_point::min() - timePoint).count();
    }

    S32 DateTime::Year() const
    {
        return mTime.tm_year + 1900;
    }
    
    S32 DateTime::Month() const
    {
        return mTime.tm_mon + 1;
    }
    
    S32 DateTime::Day() const
    {
        return mTime.tm_mday;
    }
    
    S32 DateTime::Hour() const
    {
        return mTime.tm_hour;
    }
    
    S32 DateTime::Minute() const
    {
        return mTime.tm_min;
    }
    
    S32 DateTime::Second() const
    {
        return mTime.tm_sec;
    }
    
    WeekDay DateTime::DayOfWeek() const
    {
        switch (mTime.tm_wday) {
        case 1:
            return WeekDay::Monday;
        case 2:
            return WeekDay::Tuesday;
        case 3:
            return WeekDay::Wednesday;
        case 4:
            return WeekDay::Thursday;
        case 5:
            return WeekDay::Friday;
        case 6:
            return WeekDay::Saturday;
        default:
            return WeekDay::Sunday;
        }
    }
    
    S32 DateTime::DayOfYear() const
    {
        return mTime.tm_yday;
    }

    TimeSpan DateTime::TimeOfDay() const
    {
        return TimeSpan(Hour(), Minute(), Second());
    }

    DateTime DateTime::Add(TimeSpan value) const
    {
        return DateTime(Ticks() + value.Ticks());
    }
    
    DateTime DateTime::AddTicks(S64 value) const
    {
        return DateTime(Ticks() + value);
    }
    
    DateTime DateTime::AddYears(S32 value) const
    {
        return DateTime(Year() + value, Month(), Day(), Hour(), Minute(), Second());
    }
    
    DateTime DateTime::AddMonths(S32 value) const
    {
        return DateTime(Year(), Month() + value, Day(), Hour(), Minute(), Second());
    }
    
    DateTime DateTime::AddDays(double value) const
    {
        auto day = (S32)value;
        auto hour = (value - std::floor(value)) * 24;
        auto minute = (hour - std::floor(hour)) * 60;
        auto second = (minute - std::floor(minute)) * 60;
        return DateTime(Year(), Month(), Day() + day, Hour() + (S32)hour, Minute() + (S32)minute, Second() + (S32)second);
    }
    
    DateTime DateTime::AddHours(double value) const
    {
        return AddDays(value / 24);
    }
    
    DateTime DateTime::AddMinutes(double value) const
    {
        return AddHours(value / 60);
    }
    
    DateTime DateTime::AddSeconds(double value) const
    {
        return AddMinutes(value / 60);
    }
    
    DateTime DateTime::Subtract(TimeSpan value) const
    {
        return DateTime(Ticks() - value.Ticks());
    }
    
    TimeSpan DateTime::Subtract(DateTime value) const
    {
        return TimeSpan(Ticks() - value.Ticks());
    }

    DateTime& DateTime::operator=(DateTime&& date)
    {
        mTime = std::move(date.mTime);
        return *this;
    }

    bool DateTime::operator==(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) == Clock::from_time_t(mktime(&date.mTime));
    }

    bool DateTime::operator!=(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) != Clock::from_time_t(mktime(&date.mTime));
    }

    bool DateTime::operator<=(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) <= Clock::from_time_t(mktime(&date.mTime));
    }

    bool DateTime::operator<(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) < Clock::from_time_t(mktime(&date.mTime));
    }

    bool DateTime::operator>=(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) >= Clock::from_time_t(mktime(&date.mTime));
    }

    bool DateTime::operator>(const DateTime& date) const
    {
        return Clock::from_time_t(mktime(&mTime)) > Clock::from_time_t(mktime(&date.mTime));
    }

    DateTime DateTime::operator+(const TimeSpan& timeSpan) const
    {
        return DateTime(Ticks() + timeSpan.Ticks());
    }

    TimeSpan DateTime::operator+(const DateTime& timeSpan) const
    {
        return TimeSpan(Ticks() + timeSpan.Ticks());
    }

    DateTime DateTime::operator-(const TimeSpan& timeSpan) const
    {
        return DateTime(Ticks() - timeSpan.Ticks());
    }

    TimeSpan DateTime::operator-(const DateTime& timeSpan) const
    {
        return TimeSpan(Ticks() - timeSpan.Ticks());
    }

    String DateTime::ToString() const
    {
        stringstream ss;
        ss << std::put_time(&mTime, "%c");
        return ss.str();
    }

    String DateTime::ToString(String format) const
    {
        stringstream ss;
        ss << std::put_time(&mTime, format.ToUTF8().c_str());
        return ss.str();
    }

    Vector<U8> DateTime::Serialize() const
    {
        Vector<U8> result(sizeof(mTime), 0);
        std::memcpy(result.data(), &mTime, sizeof(mTime));
        return result;
    }

    void DateTime::Deserialize(const Vector<U8>& data)
    {
        if (data.size() != sizeof(mTime)) {
            throw InvalidArgument("data");
        }

        std::memcpy(&mTime, data.data(), sizeof(mTime));
    }

    DateTime DateTime::Now()
    {
        auto time = Clock::to_time_t(Clock::now());
        DateTime result;
        localtime_s(&result.mTime, &time);
        return result;
    }

    DateTime DateTime::UtcNow()
    {
        auto time = Clock::to_time_t(Clock::now());
        DateTime result;
        gmtime_s(&result.mTime, &time);
        return result;
    }

    std::tm DateTime::FromTicks(Tick ticks)
    {
        auto timePoint = TimePoint(ticks);
        auto time = Clock::to_time_t(timePoint);
        tm timetm;

        localtime_s(&timetm, &time);
        return timetm;
    }

    DateTime operator+(const TimeSpan& lhs, const DateTime& rhs)
    {
        return DateTime(lhs.Ticks() + rhs.Ticks());
    }
    
    DateTime operator-(const TimeSpan& lhs, const DateTime& rhs)
    {
        return DateTime(lhs.Ticks() - rhs.Ticks());
    }
}

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
#include "Cookie.h"
#include "Version.h"
#include <iomanip>
#include <sstream>

using namespace std;
using namespace std::chrono;

namespace Lupus {
    namespace Net {
        Cookie::Cookie(String name, String value) :
            mName(name), mValue(value)
        {
        }

        Cookie::Cookie(String name, String value, String path) :
            mName(name), mValue(value), mPath(path)
        {
        }

        Cookie::Cookie(String name, String value, String path, String domain) :
            mName(name), mValue(value), mPath(path), mDomain(domain)
        {
        }

        String Cookie::Name() const 
        {
            return mName;
        }
        
        void Cookie::Name(String value) 
        {
            mName = value;
        }
        
        String Cookie::Value() const 
        {
            return mValue;
        }
        
        void Cookie::Value(String value) 
        {
            mValue = value;
        }
        
        String Cookie::Path() const 
        {
            return mPath;
        }
        
        void Cookie::Path(String value) 
        {
            mPath = value;
        }
        
        String Cookie::Domain() const 
        {
            return mDomain;
        }
        
        void Cookie::Domain(String value) 
        {
            mDomain = value;
        }
        
        bool Cookie::Expired() const 
        {
            return mExpired;
        }
        
        void Cookie::Expired(bool value) 
        {
            mExpired = value;
        }
        
        bool Cookie::HttpOnly() const 
        {
            return mHttpOnly;
        }
        
        void Cookie::HttpOnly(bool value) 
        {
            mHttpOnly = value;
        }
        
        bool Cookie::Secure() const 
        {
            return mSecure;
        }
        
        void Cookie::Secure(bool value) 
        {
            mSecure = value;
        }
        
        TimePoint Cookie::Expires() const 
        {
            return mExpires;
        }
        
        void Cookie::Expires(const TimePoint& value) 
        {
            mExpires = value;
        }

        String Cookie::ToString() const 
        {
            String expires;

            if (mExpired) {
                stringstream ss;
                time_t time = Clock::to_time_t(Clock::now());
                tm timetm;
                memset(&timetm, 0, sizeof(timetm));
                localtime_s(&timetm, &time);
                ss << put_time(&timetm, "%a, %Y-%b-%d %T GMT");
                expires += ss.str();
            } else if (mExpires != TimePoint::min()) {
                stringstream ss;
                time_t time = Clock::to_time_t(mExpires);
                tm timetm;
                memset(&timetm, 0, sizeof(timetm));
                localtime_s(&timetm, &time);
                ss << put_time(&timetm, "%a, %Y-%b-%d %T GMT");
                expires += ss.str();
            }

            String result = mName + "=" + mValue;
            result += (expires.IsEmpty() ? "" : ("; expires=" + expires));
            result += (mDomain.IsEmpty() ? "" : ("; domain=" + mDomain));
            result += (mPath.IsEmpty() ? "" : ("; path=" + mPath));
            result += (mSecure ? "; secure" : "");
            result += (mHttpOnly ? "; httponly" : "");

            return result;
        }
    }
}

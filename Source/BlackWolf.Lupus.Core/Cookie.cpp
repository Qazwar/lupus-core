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
#include "Cookie.h"
#include "Version.h"
#include <iomanip>
#include <sstream>

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
                std::stringstream ss;
                time_t time = Clock::to_time_t(Clock::now());
                tm timetm;
                memset(&timetm, 0, sizeof(timetm));
                localtime_s(&timetm, &time);
                ss << std::put_time(&timetm, "%a, %Y-%b-%d %T GMT");
                expires += ss.str();
            } else if (mExpires != TimePoint::min()) {
                std::stringstream ss;
                time_t time = Clock::to_time_t(mExpires);
                tm timetm;
                memset(&timetm, 0, sizeof(timetm));
                localtime_s(&timetm, &time);
                ss << std::put_time(&timetm, "%a, %Y-%b-%d %T GMT");
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

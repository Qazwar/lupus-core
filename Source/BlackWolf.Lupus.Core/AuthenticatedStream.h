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

#include "Stream.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Security {
            class LUPUSCORE_API AuthenticatedStream : public Stream
            {
            public:

                virtual ~AuthenticatedStream() = default;

                virtual std::shared_ptr<Stream> InnerStream() const NOEXCEPT;
                virtual bool IsAuthenticated() const = 0;
                virtual bool IsEncrypted() const = 0;
                virtual bool IsMutuallyAuthenticated() const = 0;
                virtual bool IsServer() const = 0;
                virtual bool IsSigned() const = 0;
                virtual bool LeaveInnerStreamOpen() const NOEXCEPT;

            protected:

                AuthenticatedStream(std::shared_ptr<Stream> innerStream, bool leaveInnerStreamOpen);

            private:

                std::shared_ptr<Stream> mStream = nullptr;
                bool mLeaveOpen = false;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

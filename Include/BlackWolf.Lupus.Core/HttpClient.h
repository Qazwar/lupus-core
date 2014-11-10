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
#pragma once

#include "Utility.h"
#include <chrono>
#include <boost/noncopyable.hpp>

namespace Lupus {
    class Uri;

    namespace Net {
        namespace Sockets {
            class TcpClient;
        }

        // TODO: HttpClient fertigstellen.
        class LUPUSCORE_API HttpClient : boost::noncopyable
        {
        public:

            HttpClient() = default;
            virtual ~HttpClient() = default;

            virtual std::shared_ptr<Uri> BaseAddress() const NOEXCEPT;
            virtual void BaseAddress(std::shared_ptr<Uri>) NOEXCEPT;
            virtual const NameValueCollection& DefaultRequestHeaders() const NOEXCEPT;
            virtual void DefaultRequestHeaders(const NameValueCollection&) NOEXCEPT;
            virtual size_t MaxResponseContentBufferSize() const NOEXCEPT;
            virtual void MaxResponseContentBufferSize(size_t) NOEXCEPT;

            template <typename Rep, typename Period>
            std::chrono::duration<Rep, Period> Timeout() const throw(socket_error, invalid_operation)
            {
                return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(std::chrono::milliseconds(mClient->SendTimeout()));
            }

            template <typename Rep, typename Period>
            void Timeout(const std::chrono::duration<Rep, Period>& value) throw(socket_error, invalid_operation)
            {
                mClient->SendTimeout(static_cast<int>(std::chrono::duration_cast<std::chrono::milliseconds>(value).count()));
            }

        private:

            std::shared_ptr<Sockets::TcpClient> mClient;
        };
    }
}

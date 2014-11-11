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

#include <vector>
#include <cstdint>
#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            namespace X509Certificates {
                // TODO: Zertifikat implementieren

                class LUPUSCORE_API X509Certificate : public NonCopyable
                {
                public:

                    X509Certificate();
                    X509Certificate(const std::vector<uint8_t>& buffer);
                    X509Certificate(const String& fileName);
                    X509Certificate(std::shared_ptr<X509Certificate> cert);
                    X509Certificate(const std::vector<uint8_t>& buffer, const String& password);
                    X509Certificate(const String& fileName, const String& password);
                };
            }
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

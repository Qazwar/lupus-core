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
#include <vector>
#include <cstdint>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Security {
        namespace Cryptography {
            class LUPUSCORE_API ICryptoTransform
            {
            public:

                virtual ~ICryptoTransform() = default;

                virtual std::vector<uint8_t> TransformFinalBlock(
                    const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount) = 0;
                virtual size_t TransformBlock(
                    const std::vector<uint8_t>& input,
                    size_t inputOffset,
                    size_t inputCount,
                    std::vector<uint8_t>& output,
                    size_t outputOffset) = 0;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

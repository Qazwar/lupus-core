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

namespace Lupus {
    namespace Security {
        namespace Authentication {
            enum class CipherAlgorithmType {
                None,
                Aes,
                TripleDes,
                Serpent,
                Rc5,
                Rc6,
                Twofish,
                Blowfish,
                Idea,
                Camellia,
                Seed
            };

            enum class HashAlgorithmType {
                None,
                Sha1,
                Sha224,
                Sha256,
                Sha384,
                Sha512,
                Sha3_224,
                Sha3_256,
                Sha3_384,
                Sha3_512,
                Tiger,
                Whirlpool,
                Ripemd128,
                Ripemd160,
                Ripemd256,
                Ripemd320,
                Md5
            };

            enum class ExchangeAlgorithmType {
                None,
                Dh,
                Dh2,
                Mqv,
                Ecdh,
                Ecmqv,
                XtrDh
            };

            enum class SslProtocols {
                Default,
                None,
                Ssl3,
                Tls10,
                Tsl11,
                Tls12
            };

            LupusFlagEnumeration(SslProtocols);
        }
    }
}

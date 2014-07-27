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

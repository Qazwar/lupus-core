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
#pragma once

#include "Utility.h"
#include "SocketEnum.h"

#include <vector>
#include <memory>
#include <cstdint>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class IPAddress;

            //! Repräsentiert einen Endpunkt mit dem Kommuniziert werden kann.
            class LUPUSCORE_API IPEndPoint : public NonCopyable
            {
            public:

                /*!
                 * Erstellt einen IP-Endpunkt mit der angegebenen IPv4 Adresse und
                 * bindet diesen an den angebenen Port. Es werden nur IPv4 Adressen
                 * unterstützt und diese muss sich in der Form 0xSSTTUUVV -\>
                 * sss.ttt.uuu.vvv befinden.
                 *
                 * \param[in]   address Eine valide IPv4 Adresse.
                 * \param[in]   port    Die Portnummer.
                 */
                IPEndPoint(uint32_t address, uint16_t port) NOEXCEPT;

                /*!
                 * Erstellt einen IP-Endpunkt mit der angebenen IP-Adresse und bindet
                 * diesen an den angebenen Port. Diese Instanz übernimmt den Besitz
                 * der IP-Adresse.
                 *
                 * \param[in]   address Eine gültige IP-Adresse für diesen Endpunkt.
                 * \param[in]   port    Die Portnummer.
                 */
                IPEndPoint(Pointer<IPAddress> address, uint16_t port) throw(NullPointer);

                /*!
                 * Erstellt einen IP-Endpunkt anhand von serialisierten Daten.
                 *
                 * \param[in]   buffer  Serialisierte Daten.
                 */
                IPEndPoint(const Vector<uint8_t>& buffer) throw(InvalidArgument);
                virtual ~IPEndPoint() = default;

                /*!
                 * \returns Die Adressfamilie des Endpunkts.
                 */
                virtual AddressFamily Family() const NOEXCEPT;

                /*!
                 * \returns Die IP-Adresse des Endpunkts.
                 */
                virtual Pointer<IPAddress> Address() const NOEXCEPT;
                /*!
                 * Setzt die IP-Adresse des Endpunkts.
                 *
                 * \param[in]   address Eine gültige IP-Adresse.
                 */
                virtual void Address(Pointer<IPAddress> address) throw(NullPointer);

                /*!
                 * \returns Die Portnummer des Endpunkts.
                 */
                virtual uint16_t Port() const NOEXCEPT;

                /*!
                 * Setzt den Port des Endpunkts.
                 *
                 * \param[in]   port    Der neue Port.
                 */
                virtual void Port(uint16_t port) NOEXCEPT;

                /*!
                 * Serialisiert die internen Daten und speichert sie in einen
                 * uint8_t-Buffer. Der Buffer ist Plattformabhängig, was auch der Grund
                 * ist wieso keine ISerializable implementiert wird.
                 *
                 * \returns Interne Daten in Form eines uint8_t-Buffers.
                 */
                virtual Vector<uint8_t> Serialize() const NOEXCEPT;

            private:

                //! Standardkonstruktor ist nicht erlaubt.
                IPEndPoint() = delete;

                AddrStorage mAddrStorage;
                Pointer<IPAddress> mAddress;
            };

            typedef Pointer<IPEndPoint> IPEndPointPtr;
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

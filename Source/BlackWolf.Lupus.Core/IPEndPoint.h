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
                IPEndPoint(std::shared_ptr<IPAddress> address, uint16_t port) throw(null_pointer);

                /*!
                 * Erstellt einen IP-Endpunkt anhand von serialisierten Daten.
                 *
                 * \param[in]   buffer  Serialisierte Daten.
                 */
                IPEndPoint(const std::vector<uint8_t>& buffer) throw(std::invalid_argument);
                virtual ~IPEndPoint() = default;

                /*!
                 * \returns Die Adressfamilie des Endpunkts.
                 */
                virtual AddressFamily Family() const NOEXCEPT;

                /*!
                 * \returns Die IP-Adresse des Endpunkts.
                 */
                virtual std::shared_ptr<IPAddress> Address() const NOEXCEPT;
                /*!
                 * Setzt die IP-Adresse des Endpunkts.
                 *
                 * \param[in]   address Eine gültige IP-Adresse.
                 */
                virtual void Address(std::shared_ptr<IPAddress> address) throw(null_pointer);

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
                virtual std::vector<uint8_t> Serialize() const NOEXCEPT;

            private:

                //! Standardkonstruktor ist nicht erlaubt.
                IPEndPoint() = delete;

                AddrStorage mAddrStorage;
                std::shared_ptr<IPAddress> mAddress;
            };

            typedef std::shared_ptr<IPEndPoint> IPEndPointPtr;
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

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
            class IPEndPoint;

            //! Repräsentiert einen IP-Adresse
            class LUPUSCORE_API IPAddress : public NonCopyable
            {
            public:

                /*!
                 * Erstellt eine neue IP-Adresse anhand der übergenenen IPv4 Adresse.
                 * Das Format der Ganzzahl ist 0xSSTTUUVV -\> sss.ttt.uuu.vvv und sie
                 * wird in das entsrechende Netzwerkformat konvertiert.
                 *
                 * \param[in]   ipv4    Ganzzahl die eine IPv4 Adresse beinhaltet.
                 */
                explicit IPAddress(uint32_t ipv4) NOEXCEPT;

                /*!
                 * Dieser Konstruktor ruft IPAddress(address, 0) auf.
                 *
                 * \sa IPAddress::IPAddress(const std::vector<uint8_t>&, U64)
                 *
                 * \param[in]   ipv6    Die IPv6 Adresse in Netzwerkformat.
                 */
                IPAddress(const std::vector<uint8_t>& ipv6) throw(std::length_error);

                /*!
                 * Erstellt eine IP-Adresse anhand eines uint8_t-Buffers. Der uint8_t-Buffer
                 * muss exakt 16-uint8_t bzw 128-Bit umfassen. Falls der uint8_t-Buffer
                 * größer ist, dann werden die restlichen uint8_ts nach dem 16ten
                 * ignoriert.
                 *
                 * Die Adresse muss sich Big-Endian sein.
                 *
                 * \param[in]   ipv6    Die IPv6 Adresse in Netzwerkformat.
                 * \param[in]   scopeid Der Scope Identifier der IPv6 Adresse.
                 */
                IPAddress(const std::vector<uint8_t>& ipv6, uint32_t scopeid) throw(std::length_error);

                /*!
                 * \sa IPAddress::IPAddress(const std::vector<uint8_t>&, size_t)
                 */
                IPAddress(std::initializer_list<uint8_t> ilist) throw(std::length_error);
                virtual ~IPAddress() = default;

                /*!
                 * Serialisiert die Adresse zu einem uint8_t-Buffer.
                 *
                 * \returns uint8_t-Buffer der serialisierten Adresse.
                 */
                virtual std::vector<uint8_t> Bytes() const NOEXCEPT;

                /*!
                 * \returns Die Adressfamilie der IP-Adresse.
                 */
                virtual AddressFamily Family() const NOEXCEPT;

                /*!
                 * \warning Methode ist noch nicht implementiert.
                 */
                virtual bool IsIPv6LinkLocal() const NOEXCEPT;

                /*!
                 * \warning Methode ist noch nicht implementiert.
                 */
                virtual bool IsIPv6Multicast() const NOEXCEPT;

                /*!
                 * \warning Methode ist noch nicht implementiert.
                 */
                virtual bool IsIPv6SiteLocal() const NOEXCEPT;

                /*!
                 * \returns Den Scope Identifier der IPv6 Adresse.
                 */
                virtual uint32_t ScopeId() const throw(socket_error);

                /*!
                 * Setzt den Scope Identifier der IPv6 Adresse.
                 *
                 * \param[in]   value   Der neue Wert des Scope Identifiers.
                 */
                virtual void ScopeId(uint32_t value) throw(socket_error);

                /*!
                 * \returns Das Präsentationsformat der IP-Adresse.
                 */
                virtual String ToString() const;

                /*!
                 * \returns TRUE wenn die IP-Adresse eine Loopback Adresse ist.
                 */
                static bool IsLoopback(std::shared_ptr<IPAddress> address) NOEXCEPT;

                /*!
                 * Erstellt eine IP-Adresse anhand des gegebenen Präsentationsformat.
                 * IPv4 muss in dezimal und IPv6 in hexadezimal dargestellt werden.
                 *
                 * Bsp IPv4: 127.0.0.1
                 * Bsp IPv6: 0:0:0:0:0:0:0:1
                 *
                 * \param[in]   ipString    Das Präsentationsformat der IP-Adresse.
                 */
                static std::shared_ptr<IPAddress> Parse(const String& ipString) throw(std::invalid_argument);

                /*!
                 * Ähnlich wie \sa IPAddress::Parse konvertiert diese Methode eine
                 * IP-Zeichenkette. Jedoch ist diese Methode Exception-Safe. Falls die
                 * Konvertierung dennoch fehlschlägt dann wird FALSE retouniert. Das
                 * Ergebniss wird in den Adresszeiger gespeichert.
                 *
                 * \param[in]   ipString    Das Präsentationsformat der IP-Adresse.
                 * \param[out]  address     Zeiger in dem das Ergebnis gespeichert
                 *                          wird.
                 *
                 * \returns TRUE wenn erfolgreich konvertiert wurde, bei einem Fehler
                 *          FALSE.
                 */
                static bool TryParse(const String& ipString, std::shared_ptr<IPAddress>& address) NOEXCEPT;

                static std::shared_ptr<IPAddress> Any();
                static std::shared_ptr<IPAddress> Broadcast();
                static std::shared_ptr<IPAddress> IPv6Any();
                static std::shared_ptr<IPAddress> IPv6Loopback();
                static std::shared_ptr<IPAddress> IPv6None();
                static std::shared_ptr<IPAddress> Loopback();
                static std::shared_ptr<IPAddress> None();

            protected:

            private:

                static const std::shared_ptr<IPAddress> sAny; //!< Entspricht 0.0.0.0
                static const std::shared_ptr<IPAddress> sBroadcast; //!< Entspricht 255.255.255.255
                static const std::shared_ptr<IPAddress> sIPv6Any; //!< Entspricht 0:0:0:0:0:0:0:0
                static const std::shared_ptr<IPAddress> sIPv6Loopback; //!< Entspricht ::1
                static const std::shared_ptr<IPAddress> sIPv6None; //!< Entspricht 0:0:0:0:0:0:0:0
                static const std::shared_ptr<IPAddress> sLoopback; //!< Entspricht 127.0.0.1
                static const std::shared_ptr<IPAddress> sNone; //!< Entspricht 0.0.0.0

                //! Standardkonstruktor ist nicht erlaubt.
                IPAddress() = delete;

                AddressFamily mFamily;
                std::vector<uint8_t> mAddress;
                uint32_t mScopeId = 0;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

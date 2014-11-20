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

#include "SocketEnum.h"
#include <cstdint>
#include <memory>
#include <vector>

namespace Lupus {
    namespace Net {
        namespace Sockets {
            class Socket;
            class IPAddress;
            class IPEndPoint;

            /*!
             * Konvertiert eine 16-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 16-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint16_t HostToNetworkOrder(uint16_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint32_t HostToNetworkOrder(uint32_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Netzwerk Byteorder.
             */
            LUPUSCORE_API uint64_t HostToNetworkOrder(uint64_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 16-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 16-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint16_t NetworkToHostOrder(uint16_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint32_t NetworkToHostOrder(uint32_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Host Byteorder.
             */
            LUPUSCORE_API uint64_t NetworkToHostOrder(uint64_t network) NOEXCEPT;

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified,
             * ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service) throw(RuntimeError);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * family, SocketType::Unspecified, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, AddressFamily family) throw(RuntimeError);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, type, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, SocketType type) throw(RuntimeError);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified, protocol) auf.
             *
             * \sa GetAddressInformation(const String&, const String&, AddressFamily, SocketType, ProtocolType)
             */
            LUPUSCORE_API Vector<Pointer<IPEndPoint>> GetAddressInformation(const String& node, const String& service, ProtocolType protocol) throw(RuntimeError);

            /*!
             * Liest die Adressinformation des angegebenen Knotens mit dem
             * entsprechenenden Service. Falls node und service eine leere Zeichenkette
             * darstellen, dann wird ein RuntimeError geworfen. Falls nach der
             * Lokalen-IP (Loopback) gesucht werden soll, dann muss der node eine
             * leere Zeichenkette sein. Falls ein beliebiger Service verwendet werden
             * soll, dann muss service eine leere Zeichenkette sein.
             *
             * Diese Methode führt eine DNS-Abfrage durch, dadurch sind auch Knoten der
             * Form "www.example.com" gültig.
             *
             * Als Service kann jeweils eine Portnummer oder der Service direkt
             * angegeben werden. Bsp: "http" oder "80".
             *
             * Alle gefunden Adressen werden dann schließlich in einen Vektor
             * gespeichert und retouniert.
             *
             * \param[in]   node        Der Knoten nach dem gesucht werden soll.
             * \param[in]   service     Der zu suchende Service.
             * \param[in]   family      Die zu verwendende Addressfamilie.
             * \param[in]   type        Der zu verwendende Sockettyp.
             * \param[in]   protocol    Das zu verwendende Protokoll.
             *
             * \returns Vektor mit allen gefunden Adressen.
             */
            LUPUSCORE_API Vector<Pointer<IPEndPoint>> GetAddressInformation(
                const String& node,
                const String& service,
                AddressFamily family,
                SocketType type,
                ProtocolType protocol
                )
                throw(RuntimeError, InvalidArgument);
        }
    }
}

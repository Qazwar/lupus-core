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
            SWC_API uint16_t HostToNetworkOrder(uint16_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Netzwerk Byteorder.
             */
            SWC_API uint32_t HostToNetworkOrder(uint32_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Host zu Netzwerk Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Netzwerk Byteorder.
             */
            SWC_API uint64_t HostToNetworkOrder(uint64_t host) NOEXCEPT;

            /*!
             * Konvertiert eine 16-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 16-Bit Ganzzahl in Host Byteorder.
             */
            SWC_API uint16_t NetworkToHostOrder(uint16_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 32-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 32-Bit Ganzzahl in Host Byteorder.
             */
            SWC_API uint32_t NetworkToHostOrder(uint32_t network) NOEXCEPT;

            /*!
             * Konvertiert eine 64-Bit Ganzzahl von Netzwerk zu Host Byteorder.
             *
             * \returns Die 64-Bit Ganzzahl in Host Byteorder.
             */
            SWC_API uint64_t NetworkToHostOrder(uint64_t network) NOEXCEPT;

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified,
             * ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const std::string&, const std::string&, AddressFamily, SocketType, ProtocolType)
             */
            SWC_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * family, SocketType::Unspecified, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const std::string&, const std::string&, AddressFamily, SocketType, ProtocolType)
             */
            SWC_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, AddressFamily family) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, type, ProtocolType::Unspecified) auf.
             *
             * \sa GetAddressInformation(const std::string&, const std::string&, AddressFamily, SocketType, ProtocolType)
             */
            SWC_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, SocketType type) throw(std::runtime_error);

            /*!
             * Diese Funktion ruft GetAddressInformation(node, service,
             * AddressFamily::Unspecified, SocketType::Unspecified, protocol) auf.
             *
             * \sa GetAddressInformation(const std::string&, const std::string&, AddressFamily, SocketType, ProtocolType)
             */
            SWC_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(const std::string& node, const std::string& service, ProtocolType protocol) throw(std::runtime_error);

            /*!
             * Liest die Adressinformation des angegebenen Knotens mit dem
             * entsprechenenden Service. Falls node und service eine leere Zeichenkette
             * darstellen, dann wird ein std::runtime_error geworfen. Falls nach der
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
            SWC_API std::vector<std::shared_ptr<IPEndPoint>> GetAddressInformation(
                const std::string& node,
                const std::string& service,
                AddressFamily family,
                SocketType type,
                ProtocolType protocol
                )
                throw(std::runtime_error, std::invalid_argument);
        }
    }
}

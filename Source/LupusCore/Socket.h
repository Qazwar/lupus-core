#pragma once

#include "SocketEnum.h"

#include <vector>
#include <memory>
#include <cstdint>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Net {
        namespace Sockets {
            struct SocketInformation;
            class IPEndPoint;
            class IPAddress;

            extern "C" struct LingerOption {
                bool Enabled;
                int LingerTime;
            };

            class LUPUS_API Socket : public boost::noncopyable
            {
            public:
                /*!
                 * Erstellt einen neuen Socket anhand von serialisierten Daten eines
                 * anderen Sockets. Falls der zuvor serialisierte Socket bereits
                 * verbunden oder gebunden war, dann wird auch dieser Socket
                 * automatisch verbunden bzw gebunden.
                 *
                 * \param[in]   socketInformatoin   Die serialisierten Socketdaten
                 */
                Socket(const SocketInformation& socketInformation) throw(std::invalid_argument, socket_error);

                /*!
                 * Erstellt einen Socket anhand der Domäne, des zu verwendenden
                 * Protokolls und des Sockttyps.
                 *
                 * \param[in]   family      Die zu verwendende Socketdomäne.
                 * \param[in]   type        Der zu verwendende Sockettyp.
                 * \param[in]   protocol    Das zu verwendende Protokoll.
                 */
                Socket(AddressFamily family, SocketType type, ProtocolType protocol) throw(socket_error);
                virtual ~Socket();

                /*!
                 * Akzeptiert eine neue Verbindung falls sich eine im Queue befindet.
                 * Diese Funktion ist blockierend und wartet so lange bis ein
                 * eingehender Peer sich verbinden will.
                 *
                 * \returns Zeiger auf den erstellten Socket der Remote-Verbindung.
                 */
                virtual std::shared_ptr<Socket> Accept() throw (socket_error);

                /*!
                 * Bindet diesen Socket an einen lokalen IP-Endpunkt. Diese Methode
                 * funktioniert nur für lokale IP-Adressen, da sie den Datenverkehr der
                 * Verbindung abfängt. Der Socket hat keinen exklusiven Zugang, was es
                 * ermöglicht auch weitere Sockets an diesen Endpunkt zu binden.
                 *
                 * \param[in]   localEndPoint   Lokaler Endpunkt an den sich der Socket
                 *                              binden soll.
                 */
                virtual void Bind(std::shared_ptr<IPEndPoint> localEndPoint) throw(socket_error);

                /*!
                 * Schließt die Socketverbindung.
                 */
                virtual void Close() throw(socket_error);

                /*!
                 * Schließt die Socketverbindung frühestens nach den angegebenen
                 * Sekunden in timeout. Bis dahin sind noch weiterhin alle gültigen
                 * Operationen erlaubt.
                 *
                 * \param[in]   timeout Der Zeitintervall bis zum schließen, angegeben
                 *                      in Sekunden.
                 */
                virtual void Close(size_t timeout) throw(socket_error);

                /*!
                 * Verbindet diesen Socket zu einen Remote-Endpunkt. Sobald die
                 * Verbindung aufgebaut ist, können Lese- und Schreiboperationen
                 * ausgeführt werden.
                 *
                 * \param[in]   remoteEndPoint  Der IP-Endpunkt mit dem sich verbunden
                 *                              wird.
                 */
                virtual void Connect(std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);

                /*!
                 * Ruft Connect(std::shared_ptr<IPEndPoint>) auf.
                 * \sa Connect(std::shared_ptr<IPEndPoint>)
                 */
                virtual void Connect(std::shared_ptr<IPAddress> address, uint16_t port) throw(socket_error, null_pointer);

                /*!
                 * Versucht eine Verbindung zu einem der angegebenen Endpunkte
                 * aufzubauen. Die Endpunkte werden normalerweise durch
                 * GetAddressInformation erzeugt. Jedoch darf die Liste jeden
                 * beliebigen gültigen Endpunkt enthalten.
                 *
                 * Der erste Endpunkt mit dem sich erfolgreich Verbunden wurde, beendet
                 * den aufruf.
                 *
                 * \sa GetAddressInformation(const String& node, const String& service, AddressFamily family, SocketType type, ProtocolType protocol)
                 *
                 * \param[in]   endPoints   Endpunkte mit denen sich Verbunden werden
                 *                          soll.
                 */
                virtual void Connect(const std::vector<std::shared_ptr<IPEndPoint>>& endPoints) throw(socket_error, null_pointer);

                /*!
                 * Ruft Connect(std::shared_ptr<IPEndPoint>) auf.
                 * \sa Connect(std::shared_ptr<IPEndPoint>)
                 */
                virtual void Connect(const String& host, uint16_t port) throw(socket_error, std::invalid_argument);

                /*!
                 * Serialisiert den Socket und schließt in anschließend. Die
                 * serialisierten Daten werden anschließend retouniert.
                 *
                 * \returns Serialisierte Socketdaten.
                 */
                virtual SocketInformation DuplicateAndClose() throw(null_pointer, socket_error);

                /*!
                 * Nach dem sich der Socket an eine lokale Adresse gebunden hat, wartet
                 * dieser nun auf eingehende Verbindungen.
                 *
                 * \param[in]   backlog Die maximale Anzahl an Verbindungen im Queue.
                 */
                virtual void Listen(size_t backlog) throw(socket_error);

                /*!
                 * Überprüft im angegebenen Zeitintervall den Socket. Gültige Modi sind
                 * alle Werte im SocketPollFlags enum. Diese Werte können auch via
                 * OR-Bit verknüpft werden.
                 *
                 * Das Ergebnis wird dann als OR-Bit retouniert und beinhaltet jenen
                 * Wert der als erstes aufgetretten ist.
                 *
                 * \param[in]   milliSeconds    Der Zeitintervall in dem gewartet
                 *                              werden soll.
                 * \param[in]   mode            Die Modi auf die gewartet wird.
                 *
                 * \returns Das Resultat der Operation.
                 */
                virtual SocketPollFlags Poll(size_t milliSeconds, SocketPollFlags mode) throw(socket_error);

                /*!
                 * Ruft Receive(buffer, 0, buffer.size(), SocketFlags::None, error)
                 * auf.
                 *
                 * \sa Receive(std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Receive(std::vector<uint8_t>& buffer) throw(socket_error);

                /*!
                 * Ruft Receive(buffer, offset, buffer.size(), SocketFlags::None,
                 * error) auf.
                 *
                 * \sa Receive(std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Receive(std::vector<uint8_t>& buffer, size_t offset) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft Receive(buffer, offset, size, SocketFlags::None, error) auf.
                 *
                 * \sa Receive(std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Receive(std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft Receive(buffer, offset, size, socketFlats, error) auf.
                 *
                 * \sa Receive(std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Receive(std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags) throw(socket_error, std::out_of_range);

                /*!
                 * Liest Daten aus dem Empfangs-Buffer. Diese Methode ist blockiert
                 * wenn der Socket so eingestellt ist und liefert einen Fehler wenn
                 * keine Daten vorhanden sind und der Socket auf Non-Blocking
                 * eingestellt ist. Im allgemeinen werden Fehlercodes im errorCode
                 * Argument gespeichert.
                 *
                 * Die Größe des Vektors wird nicht verändert, von daher muss der
                 * offset mit dem size Argument in die vorhandene Größe des Vektors
                 * passen. Falls die beiden Argumente nicht passen, dann wird eine
                 * std::out_of_range Exception geworfen.
                 *
                 * \param[in,out]   buffer      Der Vektor in dem die Daten gespeichert
                 *                              werden.
                 * \param[in]       offset      Der offset für den Vektor.
                 * \param[in]       size        Die zu lesende Größe.
                 * \param[in]       socketFlags Die zu verwendenden Flags.
                 * \param[out]      errorCode   Fehlercode im Fehlerfall.
                 *
                 * \returns Die Anzahl der erhaltenen Bytes. Falls die Verbindung
                 *          geschlossen wurde dann Null. Oder einen Fehlercode, wenn
                 *          ein Fehler aufgetreten ist.
                 */
                virtual int Receive(std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa ReceiveFrom(std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(std::vector<uint8_t>& buffer, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, size, SocketFlags::None, remoteEndPoint)
                 * auf.
                 *
                 * \sa ReceiveFrom(std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(std::vector<uint8_t>& buffer, size_t offset, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, size, SocketFlags::None, remoteEndPoint)
                 * auf.
                 *
                 * \sa ReceiveFrom(std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(std::vector<uint8_t>& buffer, size_t offset, size_t size, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Liest eingehende Daten aus. Diese Daten können von einen belieben
                 * Peer stammen, von daher wird der Endpunkt des Senders im
                 * remoteEndPoint Argument gespeichert.
                 *
                 * Diese Methode blockiert solange bis Daten eingetroffen sind. Es sei
                 * denn der Socket ist auf Non-Blocking gestellt, dann wird ein Fehler
                 * retouniert.
                 *
                 * Die Größe des Vektors wird nicht verändert, von daher muss der
                 * offset mit dem size Argument in die vorhandene Größe des Vektors
                 * passen. Falls die beiden Argumente nicht passen, dann wird eine
                 * std::out_of_range Exception geworfen.
                 *
                 * \param[in,out]   buffer          Der Vektor in dem die Daten
                 *                                  gespeichert werden.
                 * \param[in]       offset          Der offset für den Vektor.
                 * \param[in]       size            Die zu lesende Größe.
                 * \param[in]       socktFlags      Die zu vewendenden Flags.
                 * \param[out]      remoteEndPoint  Der sendende Endpunkt.
                 *
                 * \returns Die Anzahl der erhaltenen Bytes. Falls die Verbindung
                 *          geschlossen wurde dann Null. Oder einen Fehlercode, wenn
                 *          ein Fehler aufgetreten ist.
                 */
                virtual int ReceiveFrom(std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft Send(buffer, 0, buffer.size(), SocketFlags::None, error) auf.
                 *
                 * \sa Send(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Send(const std::vector<uint8_t>& buffer) throw(socket_error);

                /*!
                 * Ruft Send(buffer, offset, buffer.size(), SocketFlags::None, error)
                 * auf.
                 *
                 * \sa Send(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Send(const std::vector<uint8_t>& buffer, size_t offset) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft Send(buffer, offset, size, SocketFlags::None, error) auf.
                 *
                 * \sa Send(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Send(const std::vector<uint8_t>& buffer, size_t offset, size_t size) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft Send(buffer, offset, size, socketFlags, error) auf.
                 *
                 * \sa Send(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, SocketError&)
                 */
                virtual int Send(const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags) throw(socket_error, std::out_of_range);

                /*!
                 * Schreibt Daten zu den verbundenen Endpunkt. Wenn der Socket
                 * blockiert, dann wartet diese Methode solange bis die Daten gesendet
                 * wurden. Andernfalls wird ein Fehlercode im errorCode Argument
                 * gespeichert.
                 *
                 * \param[in]   buffer      Vektor mit den Daten zum senden.
                 * \param[in]   offset      Der offset ab dem gesendet wird.
                 * \param[in]   size        Die zu sendende Größe.
                 * \param[in]   socketFlags Die zu verwendenden Flags.
                 * \param[out]  errorCode   Fehlercode im Fehlerfall.
                 *
                 * \returns Die Anzahl der erhaltenen Bytes. Falls die Verbindung
                 *          geschlossen wurde dann Null. Oder einen Fehlercode, wenn
                 *          ein Fehler aufgetreten ist.
                 */
                virtual int Send(const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft SendTo(buffer, 0, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa SendTo(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>)
                 */
                virtual int SendTo(const std::vector<uint8_t>& buffer, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error);

                /*!
                 * Ruft SendTo(buffer, offset, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa SendTo(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>)
                 */
                virtual int SendTo(const std::vector<uint8_t>& buffer, size_t offset, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Ruft SendTo(buffer, offset, size, SocketFlags::None remoteEndPoint)
                 * auf.
                 *
                 * \sa SendTo(const std::vector<uint8_t>&, size_t, size_t, SocketFlags, std::shared_ptr<IPEndPoint>)
                 */
                virtual int SendTo(const std::vector<uint8_t>& buffer, size_t offset, size_t size, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Sendet Daten an einen gewissen Endpunkt. Falls die Daten nicht
                 * gesendet werden können und der Socket auf Blocking eingestellt ist,
                 * dann wartet diese Methode solange bis die Daten gesendet werden
                 * können. Andernfalls wird ein Fehler retouniert.
                 *
                 * \param[in]   buffer          Vektor mit den Daten zum senden.
                 * \param[in]   offset          Der offset ab dem gesendet wird.
                 * \param[in]   size            Die zu sendende Größe.
                 * \param[in]   socketFlags     Die zu verwendenden Flags.
                 * \param[out]  remoteEndPoint  Der lesende Endpunkt.
                 *
                 * \returns Die Anzahl der erhaltenen Bytes. Falls die Verbindung
                 *          geschlossen wurde dann Null. Oder einen Fehlercode, wenn
                 *          ein Fehler aufgetreten ist.
                 */
                virtual int SendTo(const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, std::out_of_range);

                /*!
                 * Schließt die Verbindung nicht komplett, sondern lediglich den
                 * lesenden oder schreibenden Teil. Es können auch beide gleichzeitig
                 * geschlossen werden.
                 *
                 * \param[in]   how Teil der beendet wird.
                 */
                virtual void Shutdown(SocketShutdown how) throw(socket_error);

                /*!
                 * \returns Den nativen Socket-Handle
                 */
                virtual SocketHandle Handle() const NOEXCEPT;

                /*!
                 * Überprüft ob für diesen Socket eine Verbindung besteht.
                 *
                 * \returns TRUE wenn der Socket verbunden ist, ansonsten FALSE.
                 */
                virtual bool IsConnected() const NOEXCEPT;

                /*!
                 * Überprüft ob dieser Socket an eine Adresse gebunden ist.
                 *
                 * \returns TRUE wenn der Socket gebunden ist, ansonsten FALSE.
                 */
                virtual bool IsBound() const NOEXCEPT;

                /*!
                 * Überprüft ob der Socket auf eingehende Verbindungen wartet.
                 *
                 * \returns TRUE wenn der Socket auf Verbindungen wartet, ansonsten
                 *          FALSE.
                 */
                virtual bool IsListening() const throw(socket_error);

                /*!
                 * \returns Die Domäne des Sockets.
                 */
                virtual AddressFamily Family() const throw(socket_error);

                /*!
                 * \returns Das Protokoll des Sockets.
                 */
                virtual ProtocolType Protocol() const throw(socket_error);

                /*!
                 * \returns Den Typ des Sockets.
                 */
                virtual SocketType Type() const throw(socket_error);

                /*!
                 * Überprüft ob es Daten zum lesen gibt und retouniert die Anzahl an
                 * Bytes.
                 *
                 * \returns Die Byteanzahl zum lesen.
                 */
                virtual size_t Available() const throw(socket_error);

                /*!
                 * Überprüft ob der Socket auf Anfragen wartet. Standardwert ist TRUE.
                 *
                 * \returns TRUE wenn der Socket blockt, ansonsten FALSE.
                 */
                virtual bool Blocking() const NOEXCEPT;

                /*!
                 * Entscheidet ob der Socket blockt oder nicht. TRUE wenn der Socket
                 * blocken soll, ansonsten FALSE. Standardwert ist TRUE.
                 */
                virtual void Blocking(bool) throw(socket_error);

                /*!
                 * Liest den LingerState
                 */
                virtual LingerOption LingerState() const throw(socket_error);

                /*!
                 * Schreibt den LingerState
                 */
                virtual void LingerState(const LingerOption&) throw(socket_error);

                /*!
                 * Überprüft ob der Nagle-Algorithmus aktiviert ist.
                 */
                virtual bool NoDelay() const throw(socket_error);

                /*!
                 * Setzt den Nagle-Algorithmus
                 */
                virtual void NoDelay(bool) throw(socket_error);

                /*!
                 * Retouniert den lokalen Endpunkt an den der Socket gebunden ist, oder
                 * einen Nullzeiger wenn der Socket keine spezifische lokale Verbindung
                 * besitzt.
                 */
                virtual std::shared_ptr<IPEndPoint> LocalEndPoint() const NOEXCEPT;

                /*!
                 * Retouniert den Remote-Endpunkt mit dem der Socket verbunden ist,
                 * oder einen Nullzeiger wenn der Socket keine Remote-Verbindung
                 * besitzt.
                 */
                virtual std::shared_ptr<IPEndPoint> RemoteEndPoint() const NOEXCEPT;

                /*!
                 * \returns Die Größe des Schreib-Buffers.
                 */
                virtual int SendBuffer() const throw(socket_error);

                /*!
                 * Setzt die Größe des Schreib-Buffers.
                 */
                virtual void SendBuffer(int) throw(socket_error);

                /*!
                 * \returns Die Größe des Lese-Buffers.
                 */
                virtual int ReceiveBuffer() const throw(socket_error);

                /*!
                 * Setzt die Größe des Lese-Buffers.
                 */
                virtual void ReceiveBuffer(int) throw(socket_error);

                /*!
                 * Retouniert den Timeout für das blocken von Schreibbefehlen.
                 */
                virtual int SendTimeout() const NOEXCEPT;

                /*!
                 * Setzt den Timeout für das blocken von Schreibbefehlen.
                 */
                virtual void SendTimeout(int) throw(socket_error);

                /*!
                 * Retouniert den Timeout für das blocken von Lesebefehlen.
                 */
                virtual int ReceiveTimeout() const NOEXCEPT;

                /*!
                 * Setzt den Timeout für das blocken von Lesebefehlen.
                 */
                virtual void ReceiveTimeout(int) throw(socket_error);

                /*!
                 * \warning Noch nicht implementiert.
                 */
                static void Select(const std::vector<std::shared_ptr<Socket>>& checkRead, const std::vector<std::shared_ptr<Socket>>& checkWrite, const std::vector<std::shared_ptr<Socket>>& checkError, size_t microSeconds) throw(socket_error);

            protected:

                int GetSocketDomain(SocketHandle h) const throw(socket_error);
                int GetSocketProtocol(SocketHandle h) const throw(socket_error);

            private:

                class SocketState : public boost::noncopyable
                {
                public:
                    virtual ~SocketState() = default;

                    virtual std::shared_ptr<Socket> Accept(Socket* socket) throw(socket_error);
                    virtual void Bind(Socket* socket, std::shared_ptr<IPEndPoint> localEndPoint) throw(socket_error);
                    virtual void Close(Socket* socket) throw(socket_error);
                    virtual void Close(Socket* socket, size_t timeout) throw(socket_error);
                    virtual void Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);
                    virtual SocketInformation DuplicateAndClose(Socket* socket) throw(null_pointer, socket_error);
                    virtual void Listen(Socket* socket, size_t backlog) throw(socket_error);
                    virtual int Receive(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range);
                    virtual int ReceiveFrom(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error, std::out_of_range);
                    virtual int Send(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range);
                    virtual int SendTo(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, std::out_of_range);
                    virtual void Shutdown(Socket* socket, SocketShutdown how) throw(socket_error);

                protected:

                    std::shared_ptr<Socket> CreateSocket(Socket*, SocketHandle, AddrStorage) NOEXCEPT;

                    void ChangeState(Socket* socket, std::shared_ptr<SocketState> state) NOEXCEPT;
                    void SetLocalEndPoint(Socket* socket, std::shared_ptr<IPEndPoint>) NOEXCEPT;
                    void SetRemoteEndPoint(Socket* socket, std::shared_ptr<IPEndPoint>) NOEXCEPT;
                    std::shared_ptr<IPEndPoint> GetLocalEndPoint(Socket* socket) const NOEXCEPT;
                    std::shared_ptr<IPEndPoint> GetRemoteEndPoint(Socket* socket) const NOEXCEPT;

                    void SetConnected(Socket*, bool) NOEXCEPT;
                    void SetBound(Socket*, bool) NOEXCEPT;
                };

                class SocketBound : public SocketState
                {
                public:
                    SocketBound(Socket*);
                    SocketBound(Socket*, std::shared_ptr<IPEndPoint>);
                    virtual ~SocketBound() = default;

                    virtual void Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer) override;
                    virtual void Listen(Socket* socket, size_t backlog) throw(socket_error) override;
                };

                class SocketListen : public SocketState
                {
                public:
                    SocketListen(Socket*);
                    virtual ~SocketListen() = default;

                    virtual std::shared_ptr<Socket> Accept(Socket* socket) throw(socket_error);
                };

                class SocketConnected : public SocketState
                {
                public:
                    SocketConnected(Socket*);
                    SocketConnected(Socket*, std::shared_ptr<IPEndPoint>);
                    virtual ~SocketConnected() = default;

                    virtual void Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer);
                    virtual int Receive(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range) override;
                    virtual int Send(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, SocketError& errorCode) throw(socket_error, std::out_of_range) override;
                    virtual void Shutdown(Socket* socket, SocketShutdown how) throw(socket_error) override;
                };

                class SocketReady : public SocketState
                {
                public:
                    SocketReady(Socket*);
                    virtual ~SocketReady() = default;

                    virtual void Bind(Socket* socket, std::shared_ptr<IPEndPoint> localEndPoint) throw(socket_error) override;
                    virtual void Connect(Socket* socket, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, null_pointer) override;
                };

                class SocketClosed : public SocketState
                {
                public:
                    SocketClosed() = default;
                    virtual ~SocketClosed() = default;

                    virtual void Close(Socket* socket) NOEXCEPT override;
                    virtual void Close(Socket* socket, size_t timeout) NOEXCEPT override;
                    virtual SocketInformation DuplicateAndClose(Socket* socket) throw(socket_error) override;
                    virtual int ReceiveFrom(Socket* socket, std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint>& remoteEndPoint) throw(socket_error, std::out_of_range) override;
                    virtual int SendTo(Socket* socket, const std::vector<uint8_t>& buffer, size_t offset, size_t size, SocketFlags socketFlags, std::shared_ptr<IPEndPoint> remoteEndPoint) throw(socket_error, std::out_of_range) override;
                };

                Socket() = default;

                SocketHandle mHandle = INVALID_SOCKET;
                int mSendTime = 0; // Windows support
                int mRecvTime = 0; // Windows support
                bool mBlocking = true;
                std::shared_ptr<IPEndPoint> mLocal;
                std::shared_ptr<IPEndPoint> mRemote;
                bool mBound = false;
                bool mConnected = false;

                std::shared_ptr<class SocketState> mState;
                friend class SocketState;
            };

            typedef std::shared_ptr<Socket> SocketPtr;
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

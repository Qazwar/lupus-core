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
            struct SocketInformation;
            class IPEndPoint;
            class IPAddress;

            extern "C" struct LUPUSCORE_API LingerOption {
                bool Enabled;
                int LingerTime;
            };

            class LUPUSCORE_API Socket : public NonCopyable
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
                Socket(const SocketInformation& socketInformation) throw(InvalidArgument, SocketError);

                /*!
                 * Erstellt einen Socket anhand der Domäne, des zu verwendenden
                 * Protokolls und des Sockttyps.
                 *
                 * \param[in]   family      Die zu verwendende Socketdomäne.
                 * \param[in]   type        Der zu verwendende Sockettyp.
                 * \param[in]   protocol    Das zu verwendende Protokoll.
                 */
                Socket(AddressFamily family, SocketType type, ProtocolType protocol) throw(SocketError);
                virtual ~Socket();

                /*!
                 * Akzeptiert eine neue Verbindung falls sich eine im Queue befindet.
                 * Diese Funktion ist blockierend und wartet so lange bis ein
                 * eingehender Peer sich verbinden will.
                 *
                 * \returns Zeiger auf den erstellten Socket der Remote-Verbindung.
                 */
                virtual Pointer<Socket> Accept() throw (SocketError);

                /*!
                 * Bindet diesen Socket an einen lokalen IP-Endpunkt. Diese Methode
                 * funktioniert nur für lokale IP-Adressen, da sie den Datenverkehr der
                 * Verbindung abfängt. Der Socket hat keinen exklusiven Zugang, was es
                 * ermöglicht auch weitere Sockets an diesen Endpunkt zu binden.
                 *
                 * \param[in]   localEndPoint   Lokaler Endpunkt an den sich der Socket
                 *                              binden soll.
                 */
                virtual void Bind(Pointer<IPEndPoint> localEndPoint) throw(SocketError);

                /*!
                 * Schließt die Socketverbindung.
                 */
                virtual void Close() throw(SocketError);

                /*!
                 * Schließt die Socketverbindung frühestens nach den angegebenen
                 * Sekunden in timeout. Bis dahin sind noch weiterhin alle gültigen
                 * Operationen erlaubt.
                 *
                 * \param[in]   timeout Der Zeitintervall bis zum schließen, angegeben
                 *                      in Sekunden.
                 */
                virtual void Close(U32 timeout) throw(SocketError);

                /*!
                 * Verbindet diesen Socket zu einen Remote-Endpunkt. Sobald die
                 * Verbindung aufgebaut ist, können Lese- und Schreiboperationen
                 * ausgeführt werden.
                 *
                 * \param[in]   remoteEndPoint  Der IP-Endpunkt mit dem sich verbunden
                 *                              wird.
                 */
                virtual void Connect(Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, NullPointer);

                /*!
                 * Ruft Connect(Pointer<IPEndPoint>) auf.
                 * \sa Connect(Pointer<IPEndPoint>)
                 */
                virtual void Connect(Pointer<IPAddress> address, U16 port) throw(SocketError, NullPointer);

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
                virtual void Connect(const Vector<Pointer<IPEndPoint>>& endPoints) throw(SocketError, NullPointer);

                /*!
                 * Ruft Connect(Pointer<IPEndPoint>) auf.
                 * \sa Connect(Pointer<IPEndPoint>)
                 */
                virtual void Connect(const String& host, U16 port) throw(SocketError, InvalidArgument);

                /*!
                 * Serialisiert den Socket und schließt in anschließend. Die
                 * serialisierten Daten werden anschließend retouniert.
                 *
                 * \returns Serialisierte Socketdaten.
                 */
                virtual SocketInformation DuplicateAndClose() throw(NullPointer, SocketError);

                /*!
                 * Nach dem sich der Socket an eine lokale Adresse gebunden hat, wartet
                 * dieser nun auf eingehende Verbindungen.
                 *
                 * \param[in]   backlog Die maximale Anzahl an Verbindungen im Queue.
                 */
                virtual void Listen(U32 backlog) throw(SocketError);

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
                virtual SocketPollFlags Poll(U32 milliSeconds, SocketPollFlags mode) throw(SocketError);

                /*!
                 * Ruft Receive(buffer, 0, buffer.size(), SocketFlags::None, error)
                 * auf.
                 *
                 * \sa Receive(Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Receive(Vector<U8>& buffer) throw(SocketError);

                /*!
                 * Ruft Receive(buffer, offset, buffer.size(), SocketFlags::None,
                 * error) auf.
                 *
                 * \sa Receive(Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Receive(Vector<U8>& buffer, U32 offset) throw(SocketError, OutOfRange);

                /*!
                 * Ruft Receive(buffer, offset, size, SocketFlags::None, error) auf.
                 *
                 * \sa Receive(Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Receive(Vector<U8>& buffer, U32 offset, U32 size) throw(SocketError, OutOfRange);

                /*!
                 * Ruft Receive(buffer, offset, size, socketFlats, error) auf.
                 *
                 * \sa Receive(Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Receive(Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags) throw(SocketError, OutOfRange);

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
                 * OutOfRange Exception geworfen.
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
                virtual int Receive(Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa ReceiveFrom(Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(Vector<U8>& buffer, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, size, SocketFlags::None, remoteEndPoint)
                 * auf.
                 *
                 * \sa ReceiveFrom(Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(Vector<U8>& buffer, U32 offset, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError, OutOfRange);

                /*!
                 * Ruft ReceiveFrom(buffer, 0, size, SocketFlags::None, remoteEndPoint)
                 * auf.
                 *
                 * \sa ReceiveFrom(Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>&)
                 */
                virtual int ReceiveFrom(Vector<U8>& buffer, U32 offset, U32 size, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError, OutOfRange);

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
                 * OutOfRange Exception geworfen.
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
                virtual int ReceiveFrom(Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError, OutOfRange);

                /*!
                 * Ruft Send(buffer, 0, buffer.size(), SocketFlags::None, error) auf.
                 *
                 * \sa Send(const Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Send(const Vector<U8>& buffer) throw(SocketError);

                /*!
                 * Ruft Send(buffer, offset, buffer.size(), SocketFlags::None, error)
                 * auf.
                 *
                 * \sa Send(const Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Send(const Vector<U8>& buffer, U32 offset) throw(SocketError, OutOfRange);

                /*!
                 * Ruft Send(buffer, offset, size, SocketFlags::None, error) auf.
                 *
                 * \sa Send(const Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Send(const Vector<U8>& buffer, U32 offset, U32 size) throw(SocketError, OutOfRange);

                /*!
                 * Ruft Send(buffer, offset, size, socketFlags, error) auf.
                 *
                 * \sa Send(const Vector<U8>&, U32, U32, SocketFlags, SocketErrorCode&)
                 */
                virtual int Send(const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags) throw(SocketError, OutOfRange);

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
                virtual int Send(const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange);

                /*!
                 * Ruft SendTo(buffer, 0, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa SendTo(const Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>)
                 */
                virtual int SendTo(const Vector<U8>& buffer, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError);

                /*!
                 * Ruft SendTo(buffer, offset, buffer.size(), SocketFlags::None,
                 * remoteEndPoint) auf.
                 *
                 * \sa SendTo(const Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>)
                 */
                virtual int SendTo(const Vector<U8>& buffer, U32 offset, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, OutOfRange);

                /*!
                 * Ruft SendTo(buffer, offset, size, SocketFlags::None remoteEndPoint)
                 * auf.
                 *
                 * \sa SendTo(const Vector<U8>&, U32, U32, SocketFlags, Pointer<IPEndPoint>)
                 */
                virtual int SendTo(const Vector<U8>& buffer, U32 offset, U32 size, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, OutOfRange);

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
                virtual int SendTo(const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, OutOfRange);

                /*!
                 * Schließt die Verbindung nicht komplett, sondern lediglich den
                 * lesenden oder schreibenden Teil. Es können auch beide gleichzeitig
                 * geschlossen werden.
                 *
                 * \param[in]   how Teil der beendet wird.
                 */
                virtual void Shutdown(SocketShutdown how) throw(SocketError);

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
                virtual bool IsListening() const throw(SocketError);

                /*!
                 * \returns Die Domäne des Sockets.
                 */
                virtual AddressFamily Family() const throw(SocketError);

                /*!
                 * \returns Das Protokoll des Sockets.
                 */
                virtual ProtocolType Protocol() const throw(SocketError);

                /*!
                 * \returns Den Typ des Sockets.
                 */
                virtual SocketType Type() const throw(SocketError);

                /*!
                 * Überprüft ob es Daten zum lesen gibt und retouniert die Anzahl an
                 * Bytes.
                 *
                 * \returns Die Byteanzahl zum lesen.
                 */
                virtual U32 Available() const throw(SocketError);

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
                virtual void Blocking(bool) throw(SocketError);

                /*!
                 * Liest den LingerState
                 */
                virtual LingerOption LingerState() const throw(SocketError);

                /*!
                 * Schreibt den LingerState
                 */
                virtual void LingerState(const LingerOption&) throw(SocketError);

                /*!
                 * Überprüft ob der Nagle-Algorithmus aktiviert ist.
                 */
                virtual bool NoDelay() const throw(SocketError);

                /*!
                 * Setzt den Nagle-Algorithmus
                 */
                virtual void NoDelay(bool) throw(SocketError);

                /*!
                 * Retouniert den lokalen Endpunkt an den der Socket gebunden ist, oder
                 * einen Nullzeiger wenn der Socket keine spezifische lokale Verbindung
                 * besitzt.
                 */
                virtual Pointer<IPEndPoint> LocalEndPoint() const NOEXCEPT;

                /*!
                 * Retouniert den Remote-Endpunkt mit dem der Socket verbunden ist,
                 * oder einen Nullzeiger wenn der Socket keine Remote-Verbindung
                 * besitzt.
                 */
                virtual Pointer<IPEndPoint> RemoteEndPoint() const NOEXCEPT;

                /*!
                 * \returns Die Größe des Schreib-Buffers.
                 */
                virtual int SendBuffer() const throw(SocketError);

                /*!
                 * Setzt die Größe des Schreib-Buffers.
                 */
                virtual void SendBuffer(int) throw(SocketError);

                /*!
                 * \returns Die Größe des Lese-Buffers.
                 */
                virtual int ReceiveBuffer() const throw(SocketError);

                /*!
                 * Setzt die Größe des Lese-Buffers.
                 */
                virtual void ReceiveBuffer(int) throw(SocketError);

                /*!
                 * Retouniert den Timeout für das blocken von Schreibbefehlen.
                 * Wert in Millisekunden.
                 */
                virtual int SendTimeout() const NOEXCEPT;

                /*!
                 * Setzt den Timeout für das blocken von Schreibbefehlen.
                 * Wert in Millisekunden.
                 */
                virtual void SendTimeout(int) throw(SocketError);

                /*!
                 * Retouniert den Timeout für das blocken von Lesebefehlen.
                 * Wert in Millisekunden.
                 */
                virtual int ReceiveTimeout() const NOEXCEPT;

                /*!
                 * Setzt den Timeout für das blocken von Lesebefehlen.
                 * Wert in Millisekunden.
                 */
                virtual void ReceiveTimeout(int) throw(SocketError);

                /*!
                 * \warning Noch nicht implementiert.
                 */
                static void Select(const Vector<Pointer<Socket>>& checkRead, const Vector<Pointer<Socket>>& checkWrite, const Vector<Pointer<Socket>>& checkError, U32 microSeconds) throw(SocketError);

            protected:

                int GetSocketDomain(SocketHandle h) const throw(SocketError);
                int GetSocketProtocol(SocketHandle h) const throw(SocketError);

            private:

                class SocketState : public NonCopyable
                {
                public:
                    virtual ~SocketState() = default;

                    virtual Pointer<Socket> Accept(Socket* socket) throw(SocketError);
                    virtual void Bind(Socket* socket, Pointer<IPEndPoint> localEndPoint) throw(SocketError);
                    virtual void Close(Socket* socket) throw(SocketError);
                    virtual void Close(Socket* socket, U32 timeout) throw(SocketError);
                    virtual void Connect(Socket* socket, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, NullPointer);
                    virtual SocketInformation DuplicateAndClose(Socket* socket) throw(NullPointer, SocketError);
                    virtual void Listen(Socket* socket, U32 backlog) throw(SocketError);
                    virtual int Receive(Socket* socket, Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange);
                    virtual int ReceiveFrom(Socket* socket, Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError, OutOfRange);
                    virtual int Send(Socket* socket, const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange);
                    virtual int SendTo(Socket* socket, const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, OutOfRange);
                    virtual void Shutdown(Socket* socket, SocketShutdown how) throw(SocketError);

                protected:

                    Pointer<Socket> CreateSocket(Socket*, SocketHandle, AddrStorage) NOEXCEPT;

                    void ChangeState(Socket* socket, Pointer<SocketState> state) NOEXCEPT;
                    void SetLocalEndPoint(Socket* socket, Pointer<IPEndPoint>) NOEXCEPT;
                    void SetRemoteEndPoint(Socket* socket, Pointer<IPEndPoint>) NOEXCEPT;
                    Pointer<IPEndPoint> GetLocalEndPoint(Socket* socket) const NOEXCEPT;
                    Pointer<IPEndPoint> GetRemoteEndPoint(Socket* socket) const NOEXCEPT;

                    void SetConnected(Socket*, bool) NOEXCEPT;
                    void SetBound(Socket*, bool) NOEXCEPT;
                };

                class SocketBound : public SocketState
                {
                public:
                    SocketBound(Socket*);
                    SocketBound(Socket*, Pointer<IPEndPoint>);
                    virtual ~SocketBound() = default;

                    virtual void Connect(Socket* socket, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, NullPointer) override;
                    virtual void Listen(Socket* socket, U32 backlog) throw(SocketError) override;
                };

                class SocketListen : public SocketState
                {
                public:
                    SocketListen(Socket*);
                    virtual ~SocketListen() = default;

                    virtual Pointer<Socket> Accept(Socket* socket) throw(SocketError);
                };

                class SocketConnected : public SocketState
                {
                public:
                    SocketConnected(Socket*);
                    SocketConnected(Socket*, Pointer<IPEndPoint>);
                    virtual ~SocketConnected() = default;

                    virtual void Connect(Socket* socket, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, NullPointer);
                    virtual int Receive(Socket* socket, Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange) override;
                    virtual int Send(Socket* socket, const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, SocketErrorCode& errorCode) throw(SocketError, OutOfRange) override;
                    virtual void Shutdown(Socket* socket, SocketShutdown how) throw(SocketError) override;
                };

                class SocketReady : public SocketState
                {
                public:
                    SocketReady(Socket*);
                    virtual ~SocketReady() = default;

                    virtual void Bind(Socket* socket, Pointer<IPEndPoint> localEndPoint) throw(SocketError) override;
                    virtual void Connect(Socket* socket, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, NullPointer) override;
                };

                class SocketClosed : public SocketState
                {
                public:
                    SocketClosed() = default;
                    virtual ~SocketClosed() = default;

                    virtual void Close(Socket* socket) NOEXCEPT override;
                    virtual void Close(Socket* socket, U32 timeout) NOEXCEPT override;
                    virtual SocketInformation DuplicateAndClose(Socket* socket) throw(SocketError) override;
                    virtual int ReceiveFrom(Socket* socket, Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint>& remoteEndPoint) throw(SocketError, OutOfRange) override;
                    virtual int SendTo(Socket* socket, const Vector<U8>& buffer, U32 offset, U32 size, SocketFlags socketFlags, Pointer<IPEndPoint> remoteEndPoint) throw(SocketError, OutOfRange) override;
                };

                Socket() = default;

                SocketHandle mHandle = INVALID_SOCKET;
                int mSendTime = 0; // Windows support
                int mRecvTime = 0; // Windows support
                bool mBlocking = true;
                Pointer<IPEndPoint> mLocal;
                Pointer<IPEndPoint> mRemote;
                bool mBound = false;
                bool mConnected = false;

                Pointer<class SocketState> mState;
                friend class SocketState;
            };

            typedef Pointer<Socket> SocketPtr;
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

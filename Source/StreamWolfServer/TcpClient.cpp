#include "TcpClient.h"
#include "Socket.h"
#include "IPEndPoint.h"
#include "IPAddress.h"
#include "NetworkStream.h"
#include "NetUtility.h"
#include "Integer.hpp"

#include <thread>

using namespace std;

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            TcpClient::TcpClient(AddressFamily family)
            {
                mClient = make_shared<Socket>(family, SocketType::Stream, ProtocolType::TCP);
            }

            TcpClient::TcpClient(shared_ptr<IPEndPoint> localEP)
            {
                if (!localEP) {
                    throw null_pointer();
                }

                mClient = make_shared<Socket>(localEP->Family(), SocketType::Stream, ProtocolType::TCP);
                mClient->Connect(localEP);
            }

            TcpClient::TcpClient(const string& hostname, uint16_t port)
            {
                GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP);
                mClient = make_shared<Socket>(AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP);
                mClient->Connect(GetAddressInformation(hostname, Integer::ToString(port), AddressFamily::Unspecified, SocketType::Stream, ProtocolType::TCP));
            }

            uint32_t TcpClient::Available() const
            {
                if (mClient) {
                    return mClient->Available();
                }

                return 0;
            }

            shared_ptr<Socket> TcpClient::Client() const
            {
                return mClient;
            }

            void TcpClient::Client(shared_ptr<Socket> client)
            {
                if (!client) {
                    throw null_pointer();
                }

                mClient = client;
            }

            bool TcpClient::IsConnected() const
            {
                if (mClient) {
                    return mClient->IsConnected();
                }

                return false;
            }

            bool TcpClient::ExclusiveAddressUse() const
            {
                int32_t result, length = 4;

                if (getsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void TcpClient::ExclusiveAddressUse(bool value)
            {
                int32_t val = value ? 1 : 0;

                if (setsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            bool TcpClient::NoDelay() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->NoDelay();
            }

            void TcpClient::NoDelay(bool b)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->NoDelay(b);
            }

            int32_t TcpClient::SendBuffer() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->SendBuffer();
            }

            void TcpClient::SendBuffer(int32_t i)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->SendBuffer(i);
            }

            int32_t TcpClient::ReceiveBuffer() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->ReceiveBuffer();
            }

            void TcpClient::ReceiveBuffer(int32_t i)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->ReceiveBuffer(i);
            }

            int32_t TcpClient::SendTimeout() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->SendTimeout();
            }

            void TcpClient::SendTimeout(int32_t i)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->SendTimeout(i);
            }

            int32_t TcpClient::ReceiveTimeout() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->ReceiveTimeout();
            }

            void TcpClient::ReceiveTimeout(int32_t i)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->ReceiveTimeout(i);
            }

            void TcpClient::ConnectAsync(shared_ptr<IPEndPoint> remoteEndPoint, function<void(exception_ptr, TcpClient*)> callback)
            {
                thread([this, remoteEndPoint, callback]() {
                    try {
                        this->Connect(remoteEndPoint);
                        callback(nullptr, this);
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }

            void TcpClient::ConnectAsync(shared_ptr<IPAddress> address, uint16_t port, function<void(exception_ptr, TcpClient*)> callback)
            {
                thread([this, address, port, callback]() {
                    try {
                        this->Connect(address, port);
                        callback(nullptr, this);
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }

            void TcpClient::ConnectAsync(const vector<shared_ptr<IPEndPoint>>& endPoints, function<void(exception_ptr, TcpClient*)> callback)
            {
                thread([this, endPoints, callback]() {
                    try {
                        this->Connect(endPoints);
                        callback(nullptr, this);
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }

            void TcpClient::ConnectAsync(const string& host, uint16_t port, function<void(exception_ptr, TcpClient*)> callback)
            {
                thread([this, host, port, callback]() {
                    try {
                        this->Connect(host, port);
                        callback(nullptr, this);
                    } catch (...) {
                        callback(current_exception(), nullptr);
                    }
                }).detach();
            }

            void TcpClient::Connect(shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(remoteEndPoint);
            }

            void TcpClient::Connect(shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(address, port);
            }

            void TcpClient::Connect(const vector<shared_ptr<IPEndPoint>>& endPoints)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(endPoints);
            }

            void TcpClient::Connect(const string& host, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(host, port);
            }

            void TcpClient::Close()
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Close();
            }

            shared_ptr<NetworkStream> TcpClient::GetStream() const
            {
                return make_shared<NetworkStream>(mClient);
            }
        }
    }
}

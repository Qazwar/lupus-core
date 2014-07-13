#include "UdpClient.h"
#include "Socket.h"
#include "IPAddress.h"
#include "IPEndPoint.h"
#include "Integer.hpp"
#include "NetUtility.h"

#include <thread>

using namespace std;

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            UdpClient::UdpClient(AddressFamily)
            {
            }

            UdpClient::UdpClient(uint16_t port)
            {
            }

            UdpClient::UdpClient(shared_ptr<IPEndPoint>)
            {
            }

            UdpClient::UdpClient(uint16_t port, AddressFamily)
            {
            }

            UdpClient::UdpClient(const string& hostname, uint16_t port)
            {
            }

            uint32_t UdpClient::Available() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->Available();
            }

            shared_ptr<Socket> UdpClient::Client() const
            {
                return mClient;
            }

            void UdpClient::Client(shared_ptr<Socket> client)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient = client;
            }

            bool UdpClient::ExclusiveAddressUse() const
            {
                if (!mClient) {
                    throw null_pointer();
                }

                int32_t result, length = 4;

                if (getsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&result, (int*)&length) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }

                return (result != 0);
            }

            void UdpClient::ExclusiveAddressUse(bool value)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                int32_t val = value ? 1 : 0;

                if (setsockopt(mClient->Handle(), SOL_SOCKET, SO_REUSEADDR, (char*)&val, 4) != 0) {
                    throw socket_error(GetLastSocketErrorString());
                }
            }

            void UdpClient::ReceiveAsync(function<void(exception_ptr, shared_ptr<IPEndPoint>, const vector<uint8_t>&)> callback)
            {
                thread([this, callback]() {
                    try {
                        shared_ptr<IPEndPoint> ep;
                        callback(nullptr, ep, this->Receive(ep));
                    } catch (...) {
                        callback(current_exception(), nullptr, vector<uint8_t>());
                    }
                }).detach();
            }

            void UdpClient::SendAsync(const vector<uint8_t>& buffer, uint32_t size, function<void(exception_ptr, int32_t)> callback)
            {
                thread([this, &buffer, size, callback]() {
                    try {
                        callback(nullptr, this->Send(buffer, size));
                    } catch (...) {
                        callback(current_exception(), -1);
                    }
                }).detach();
            }

            void UdpClient::SendAsync(const vector<uint8_t>& buffer, uint32_t size, shared_ptr<IPEndPoint> ep, function<void(exception_ptr, int32_t)> callback)
            {
                thread([this, &buffer, size, ep, callback]() {
                    try {
                        callback(nullptr, this->Send(buffer, size, ep));
                    } catch (...) {
                        callback(current_exception(), -1);
                    }
                }).detach();
            }

            void UdpClient::SendAsync(const vector<uint8_t>& buffer, uint32_t size, const string& hostname, uint16_t port, function<void(exception_ptr, int32_t)> callback)
            {
                thread([this, &buffer, size, hostname, port, callback]() {
                    try {
                        callback(nullptr, this->Send(buffer, size, hostname, port));
                    } catch (...) {
                        callback(current_exception(), -1);
                    }
                }).detach();
            }

            void UdpClient::Connect(shared_ptr<IPEndPoint> remoteEndPoint)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(remoteEndPoint);
            }

            void UdpClient::Connect(shared_ptr<IPAddress> address, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(address, port);
            }

            void UdpClient::Connect(const string& host, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Connect(host, port);
            }

            void UdpClient::Close()
            {
                if (!mClient) {
                    throw null_pointer();
                }

                mClient->Close();
            }

            vector<uint8_t> UdpClient::Receive(shared_ptr<IPEndPoint>& ep)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                vector<uint8_t> vec(Available());
                mClient->ReceiveFrom(vec, ep);
                return vec;
            }

            int32_t UdpClient::Send(const vector<uint8_t>& buffer, uint32_t bytes)
            {
                if (!mClient) {
                    throw null_pointer();
                }

                return mClient->Send(buffer, 0, bytes);
            }

            int32_t UdpClient::Send(const vector<uint8_t>& buffer, uint32_t bytes, shared_ptr<IPEndPoint> ep)
            {
                if (!mClient) {
                    throw null_pointer();
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, ep);
            }

            int32_t UdpClient::Send(const vector<uint8_t>& buffer, uint32_t bytes, const string& hostname, uint16_t port)
            {
                if (!mClient) {
                    throw null_pointer();
                } else if (mClient->IsConnected()) {
                    throw socket_error("client is already connected");
                }

                return mClient->SendTo(buffer, 0, bytes, make_shared<IPEndPoint>(IPAddress::Parse(hostname), port));
            }
        }
    }
}
#include "NetworkStream.h"
#include "Socket.h"

#include <thread>

using namespace std;

namespace StreamWolf {
    namespace Net {
        namespace Sockets {
            NetworkStream::NetworkStream(shared_ptr<Sockets::Socket> socket)
            {
                if (!socket) {
                    throw null_pointer();
                }

                mSocket = socket;
            }

            uint32_t NetworkStream::DataAvailable() const
            {
                return mSocket->Available();
            }
            
            shared_ptr<Socket> NetworkStream::Socket() const
            {
                return mSocket;
            }

            void NetworkStream::ReadAsync(vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, int32_t)> callback)
            {
                thread([this, &buffer, offset, size, &callback](shared_ptr<Sockets::Socket> socket) {
                    try {
                        callback(nullptr, socket->Receive(buffer, offset, size));
                    } catch (...) {
                        callback(current_exception(), -1);
                    }
                }, mSocket).detach();
            }
            
            void NetworkStream::WriteAsync(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, int32_t)> callback)
            {
                thread([this, &buffer, offset, size, &callback](shared_ptr<Sockets::Socket> socket) {
                    try {
                        callback(nullptr, socket->Send(buffer, offset, size));
                    } catch (...) {
                        callback(current_exception(), -1);
                    }
                }, mSocket).detach();
            }

            bool NetworkStream::CanRead() const
            {
                return mRead;
            }

            bool NetworkStream::CanWrite() const
            {
                return mWrite;
            }

            bool NetworkStream::CanSeek() const
            {
                return false;
            }

            void NetworkStream::Close()
            {
                mSocket->Close();
            }
            
            void NetworkStream::Close(uint32_t timeout)
            {
                mSocket->Close(timeout);
            }

            int64_t NetworkStream::Length() const
            {
                return (int64_t)mSocket->Available();
            }
            
            int32_t NetworkStream::Read(vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
            {
                if (!mRead) {
                    throw io_error("network stream is not readable");
                }

                return mSocket->Receive(buffer, offset, size);
            }
            
            int32_t NetworkStream::ReadByte()
            {
                if (!mRead) {
                    throw io_error("network stream is not readable");
                }

                vector<uint8_t> vec(1);
                
                if (mSocket->Receive(vec, 0, 1) != 1) {
                    return -1;
                }

                return vec[0];
            }
            
            int32_t NetworkStream::Write(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
            {
                if (!mWrite) {
                    throw io_error("network stream is not writable");
                }

                return mSocket->Send(buffer, offset, size);
            }
            
            void NetworkStream::WriteByte(uint8_t byte)
            {
                if (!mWrite) {
                    throw io_error("network stream is not writable");
                }

                vector<uint8_t> vec(1, byte);
                mSocket->Send(vec, 0, 1);
            }

            bool NetworkStream::Readable() const
            {
                return mRead;
            }

            void NetworkStream::Readable(bool b)
            {
                mRead = b;
            }

            bool NetworkStream::Writable() const
            {
                return mWrite;
            }

            void NetworkStream::Writable(bool b)
            {
                mWrite = b;
            }
        }
    }
}

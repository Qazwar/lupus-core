#include "NetworkStream.h"
#include "Socket.h"

#include <thread>

using namespace std;

namespace StreamWolf {
    namespace Net {
        namespace Socket {
            NetworkStream::NetworkStream(shared_ptr<Socket> socket)
            {
                if (!socket) {
                    throw null_pointer();
                }

                mHandle = socket;
            }

            uint32_t NetworkStream::DataAvailable() const
            {
                return mHandle->Available();
            }
            
            shared_ptr<Socket> NetworkStream::Handle() const
            {
                return mHandle;
            }

            void NetworkStream::ReadAsync(vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, const vector<uint8_t>&, int32_t)> callback)
            {
                thread([this, &buffer, offset, size, &callback](shared_ptr<Socket> socket) {
                    try {
                        callback(nullptr, buffer, socket->Receive(buffer, offset, size));
                    } catch (...) {
                        callback(current_exception(), vector<uint8_t>(), -1);
                    }
                }, mHandle).detach();
            }
            
            void NetworkStream::WriteAsync(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size, function<void(exception_ptr, const vector<uint8_t>&, int32_t)> callback)
            {
                thread([this, &buffer, offset, size, &callback](shared_ptr<Socket> socket) {
                    try {
                        callback(nullptr, buffer, socket->Send(buffer, offset, size));
                    } catch (...) {
                        callback(current_exception(), vector<uint8_t>(), -1);
                    }
                }, mHandle).detach();
            }

            void NetworkStream::Close()
            {
                mHandle->Close();
            }
            
            void NetworkStream::Close(uint32_t timeout)
            {
                mHandle->Close(timeout);
            }
            
            int32_t NetworkStream::Read(vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
            {
                return mHandle->Receive(buffer, offset, size);
            }
            
            int32_t NetworkStream::ReadByte()
            {
                vector<uint8_t> vec(1);
                
                if (mHandle->Receive(vec, 0, 1) != 1) {
                    return -1;
                }

                return vec[0];
            }
            
            int32_t NetworkStream::Write(const vector<uint8_t>& buffer, uint32_t offset, uint32_t size)
            {
                return mHandle->Send(buffer, offset, size);
            }
            
            int32_t NetworkStream::WriteByte(uint8_t byte)
            {
                vector<uint8_t> vec(1, byte);
                return mHandle->Send(vec, 0, 1);
            }
        }
    }
}

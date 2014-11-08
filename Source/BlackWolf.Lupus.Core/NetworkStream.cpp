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
#include "NetworkStream.h"
#include "Socket.h"

#include <thread>

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Sockets {
            NetworkStream::NetworkStream(shared_ptr<Sockets::Socket> socket)
            {
                if (!socket) {
                    throw null_pointer();
                }

                mSocket = socket;
            }

            size_t NetworkStream::DataAvailable() const
            {
                return mSocket->Available();
            }
            
            shared_ptr<Socket> NetworkStream::Socket() const
            {
                return mSocket;
            }

            Task<int> NetworkStream::ReadAsync(vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                return Task<int>([&buffer, offset, size](shared_ptr<Sockets::Socket> socket) {
                    return socket->Receive(buffer, offset, size);
                }, mSocket);
            }
            
            Task<int> NetworkStream::WriteAsync(const vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                return Task<int>([&buffer, offset, size](shared_ptr<Sockets::Socket> socket) {
                    return socket->Send(buffer, offset, size);
                }, mSocket);
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
            
            void NetworkStream::Close(size_t timeout)
            {
                mSocket->Close(timeout);
            }

            int64_t NetworkStream::Position() const
            {
                return 0;
            }

            int64_t NetworkStream::Length() const
            {
                return (int64_t)mSocket->Available();
            }
            
            int NetworkStream::Read(vector<uint8_t>& buffer, size_t offset, size_t size)
            {
                if (!mRead) {
                    throw io_error("network stream is not readable");
                }

                return mSocket->Receive(buffer, offset, size);
            }
            
            int NetworkStream::ReadByte()
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
            
            int NetworkStream::Write(const vector<uint8_t>& buffer, size_t offset, size_t size)
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

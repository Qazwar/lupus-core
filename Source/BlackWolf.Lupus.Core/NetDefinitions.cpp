#include "NetDefinitions.h"

namespace Lupus {
    namespace Net {
        namespace Sockets {
#ifdef _MSC_VER
            std::string GetLastSocketErrorString() {
                CHAR buffer[1024];
                int i = WSAGetLastError();
                memset(buffer, 0, 1024);

                FormatMessageA(
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    i,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    buffer,
                    1023, NULL);

                return buffer;
            }

            std::string GetLastAddressInfoErrorString() {
                CHAR buffer[1024];
                int i = WSAGetLastError();
                memset(buffer, 0, 1024);

                FormatMessageA(
                    FORMAT_MESSAGE_FROM_SYSTEM |
                    FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    i,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    buffer,
                    1023, NULL);

                return buffer;
            }
#else
            std::string GetLastSocketErrorString() {
                return strerror(errno);
            }

            std::string GetLastAddressInfoErrorString() {
                return gai_strerror(errno);
            }
#endif
        }
    }
}

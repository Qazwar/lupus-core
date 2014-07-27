#include "AuthenticatedStream.h"

using namespace std;

namespace Lupus {
    namespace Net {
        namespace Security {
            AuthenticatedStream::AuthenticatedStream(shared_ptr<Stream> innerStream, bool leaveOpen)
            {
                mStream = innerStream;
                mLeaveOpen = leaveOpen;
            }

            shared_ptr<Stream> AuthenticatedStream::InnerStream() const
            {
                return mStream;
            }

            bool AuthenticatedStream::LeaveInnerStreamOpen() const
            {
                return mLeaveOpen;
            }
        }
    }
}

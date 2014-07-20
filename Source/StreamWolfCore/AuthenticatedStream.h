#pragma once

#include "Stream.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace StreamWolf {
    namespace Net {
        namespace Security {
            class SWC_API AuthenticatedStream : public Stream
            {
            public:

                virtual ~AuthenticatedStream() = default;

                virtual std::shared_ptr<Stream> InnerStream() const NOEXCEPT;
                virtual bool IsAuthenticated() const = 0;
                virtual bool IsEncrypted() const = 0;
                virtual bool IsMutuallyAuthenticated() const = 0;
                virtual bool IsServer() const = 0;
                virtual bool IsSigned() const = 0;
                virtual bool LeaveInnerStreamOpen() const NOEXCEPT;

            protected:

                AuthenticatedStream(std::shared_ptr<Stream> innerStream, bool leaveInnerStreamOpen);

            private:

                std::shared_ptr<Stream> mStream = nullptr;
                bool mLeaveOpen = false;
            };
        }
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#pragma once

#include <string>
#include <boost/noncopyable.hpp>

namespace StreamWolf {
    namespace Data {
        class ITransaction : public boost::noncopyable
        {
        public:

            virtual ~ITransaction() = default;

            virtual void Commit() = 0;
            virtual void Rollback() = 0;
        };
    }
}

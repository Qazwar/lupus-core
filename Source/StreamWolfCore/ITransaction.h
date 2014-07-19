#pragma once

#include <string>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace StreamWolf {
    namespace Data {
        class ITransaction : public boost::noncopyable
        {
        public:

            virtual ~ITransaction() = default;

            virtual void Commit() throw(sql_error) = 0;
            virtual void Rollback() throw(sql_error) = 0;
        };
    }
}

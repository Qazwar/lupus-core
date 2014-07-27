#pragma once

#include <functional>
#include <boost/noncopyable.hpp>

#include "Utility.h"

namespace Lupus {
    namespace System {
        class LUPUS_API Library : public boost::noncopyable
        {
        public:

            virtual ~Library();

            virtual void* GetFunctionHandle(const std::string&) NOEXCEPT;
            virtual void Load(const std::string&) throw(io_error);
            virtual void Unload() NOEXCEPT;

        private:

            uintptr_t mHandle = 0;
        };

        template <typename ReturnType, typename... Args>
        std::function<ReturnType(Args...)> CastFunctionHandle(void* handle)
        {
            return std::function<ReturnType(Args...)>((ReturnType(*)(Args...))(handle));
        }
    }
}

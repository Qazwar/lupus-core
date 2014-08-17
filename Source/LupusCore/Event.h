#pragma once

#include <vector>
#include <algorithm>
#include <functional>

#include "Utility.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename Sender, typename... Args>
    class LUPUS_API Event
    {
    public:

        typedef std::function<void(Sender*, Args...)> Handle;

        Event() = default;
        ~Event() = default;

        void Add(Handle&& f) const
        {
            mCallback.push_back(f);
        }

        void Clear() const
        {
            mCallback.clear();
        }

        void Fire(Sender* sender, Args&&... args)
        {
            std::for_each(std::begin(mCallback), std::end(mCallback), [&](Handle& callback) {
                callback(sender, std::forward<Args>(args)...);
            });
        }

        Event& operator+=(Handle&& f)
        {
            mCallback.push_back(f);
            return *this;
        }

    private:

        mutable std::vector<Handle> mCallback;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

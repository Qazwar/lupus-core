/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>

#include "String.h"
#include "Event.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename T>
    class IObserver
    {
    public:
            
        virtual ~IObserver() = default;

        virtual void OnUpdate(const T& value) = 0;
        virtual void OnError(Exception& error) = 0;
        virtual void OnComplete() = 0;
    };

    template <typename T>
    class Observable
    {
    public:

        virtual ~Observable() = default;

        virtual void Attach(Pointer<IObserver<T>> observer) NOEXCEPT final
        {
            mObservers.push_back(observer);
        }

        virtual void Detach(Pointer<IObserver<T>> observer) NOEXCEPT final
        {
            std::remove(Begin(mObservers), End(mObservers), observer);
        }

        virtual void OnUpdate(const T& value) NOEXCEPT final
        {
            std::for_each(Begin(mObservers), End(mObservers), [&](Pointer<IObserver<T>> observer) {
                observer->OnUpdate(value);
            });
        }

        virtual void OnError(Exception& ex) NOEXCEPT final
        {
            std::for_each(Begin(mObservers), End(mObservers), [&](Pointer<IObserver<T>> observer) {
                observer->OnError(ex);
            });
        }

        virtual void OnComplete() NOEXCEPT final
        {
            std::for_each(Begin(mObservers), End(mObservers), [](Pointer<IObserver<T>> observer) {
                observer->OnComplete();
            });
        }

    private:

        Vector<Pointer<IObserver<T>>> mObservers = Vector<Pointer<IObserver<T>>>(32);
    };

    template <typename Owner, typename T>
    class ObservableProperty : public NonCopyable
    {
        friend Owner;

    public:

        Event<ObservableProperty<Owner, T>, const T&> ValueChanged;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;
        ~ObservableProperty() = default;

        virtual T Get() const final
        {
            if (mGetter) {
                return mGetter();
            } else {
                throw RuntimeError("getter is not set");
            }
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw RuntimeError("setter is not set");
            }

            ValueChanged(this, value);
            return *this;
        }

        virtual operator T() const final
        {
            if (mGetter) {
                return mGetter();
            } else {
                throw RuntimeError("getter is not set");
            }
        }

        virtual ObservableProperty& operator=(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw RuntimeError("setter is not set");
            }

            ValueChanged(this, value);
            return *this;
        }

    private:

        std::function<T()> mGetter;
        std::function<void(const T&)> mSetter;
    };

    template <typename T>
    class ObservableProperty < void, T >
    {
    public:

        Event<ObservableProperty<void, T>, const T&> ValueChanged;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;
        ~ObservableProperty() = default;

        virtual const T& Get() const final
        {
            return mValue;
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            mValue = value;
            ValueChanged(this, value);

            return *this;
        }

        virtual operator T() const final
        {
            return mValue;
        }

        virtual ObservableProperty& operator=(const T& value) final
        {
            mValue = value;
            ValueChanged(this, value);

            return *this;
        }

    private:

        T mValue = T();
    };

    class LUPUSCORE_API ObservableObject : public NonCopyable
    {
    public:

        Event<ObservableObject, const String&> PropertyChanged;

        ObservableObject() = default;
        virtual ~ObservableObject() = default;

        virtual void Remove(const String& propertyName) NOEXCEPT final;
        virtual bool HasProperty(const String& propertyName) const NOEXCEPT final;
        virtual Any& operator[](const String& propertyName) NOEXCEPT final;
        virtual const Any& operator[](const String& propertyName) const NOEXCEPT final;

        template <typename T>
        void Add(const String& propertyName, const T& value = T())
        {
            mProperties[propertyName] = Any(value);
            PropertyChanged(this, propertyName);
        }

        template <typename T>
        const T& Get(const String& propertyName) const
        {
            return Any_cast<const T&>(mProperties[propertyName]);
        }

        template <typename T>
        void Set(const String& propertyName, const T& value)
        {
            mProperties[propertyName] = Any(value);
            PropertyChanged(this, propertyName);
        }

    private:

        Collection<String, Any> mProperties;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include "String.h"
#include "Event.h"
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    template <typename T>
    class LUPUS_API IObserver
    {
    public:
            
        virtual ~IObserver() = default;

        virtual void OnUpdate(const T& value) NOEXCEPT = 0;
        virtual void OnError(std::exception& error) NOEXCEPT = 0;
        virtual void OnComplete() NOEXCEPT = 0;
    };

    template <typename T>
    class LUPUS_API Observable
    {
    public:

        virtual ~Observable() = default;

        virtual void Attach(std::shared_ptr<IObserver<T>> observer) final
        {
            mObservers.push_back(observer);
        }

        virtual void Detach(std::shared_ptr<IObserver<T>> observer) NOEXCEPT final
        {
            std::remove(std::begin(mObservers), std::end(mObservers), observer);
        }

        virtual void OnUpdate(const T& value) NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnUpdate(value);
            });
        }

        virtual void OnError(std::exception& ex) NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnError(ex);
            });
        }

        virtual void OnComplete() NOEXCEPT final
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [](std::shared_ptr<IObserver<T>> observer) {
                observer->OnComplete();
            });
        }

    private:

        std::vector<std::shared_ptr<IObserver<T>>> mObservers = std::vector<std::shared_ptr<IObserver<T>>>(32);
    };

    template <typename Owner, typename T>
    class LUPUS_API ObservableProperty : public boost::noncopyable
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
                throw std::runtime_error("getter is not set");
            }
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw std::runtime_error("setter is not set");
            }

            ValueChanged(this, value);
            return *this;
        }

        virtual operator T() const final
        {
            if (mGetter) {
                return mGetter();
            } else {
                throw std::runtime_error("getter is not set");
            }
        }

        virtual ObservableProperty& operator=(const T& value) final
        {
            if (mSetter) {
                mSetter(value);
            } else {
                throw std::runtime_error("setter is not set");
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

    class LUPUS_API ObservableObject : public boost::noncopyable
    {
    public:

        Event<ObservableObject, const String&> PropertyChanged;

        ObservableObject() = default;
        virtual ~ObservableObject() = default;

        virtual void Remove(const String& propertyName) NOEXCEPT final;
        virtual bool HasProperty(const String& propertyName) const NOEXCEPT final;
        virtual boost::any& operator[](const String& propertyName) NOEXCEPT final;
        virtual const boost::any& operator[](const String& propertyName) const NOEXCEPT final;

        template <typename T>
        void Add(const String& propertyName, const T& value = T())
        {
            mProperties[propertyName] = boost::any(value);
            PropertyChanged(this, propertyName);
        }

        template <typename T>
        const T& Get(const String& propertyName) const
        {
            return boost::any_cast<const T&>(mProperties[propertyName]);
        }

        template <typename T>
        void Set(const String& propertyName, const T& value)
        {
            mProperties[propertyName] = boost::any(value);
            PropertyChanged(this, propertyName);
        }

    private:

        std::unordered_map<String, boost::any> mProperties;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

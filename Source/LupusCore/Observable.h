#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <unordered_map>

#include "Utility.h"
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
    class LUPUS_API IObservable
    {
    public:

        virtual ~IObservable() = default;

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

    template <typename T>
    class LUPUS_API ObservableProperty : public IObservable<T>, public boost::noncopyable
    {
    public:

        Event<ObservableProperty<T>, const T&> ValueChanged;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;

        virtual ~ObservableProperty()
        {
            OnComplete();
        }

        virtual const T& Get() const final
        {
            return mValue;
        }

        virtual ObservableProperty& Set(const T& value) final
        {
            mValue = value;
            OnUpdate(value);
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
            OnUpdate(value);
            ValueChanged(this, value);

            return *this;
        }

    private:

        T mValue = T();
    };

    class LUPUS_API ObservableObject : public IObservable<std::string>, public boost::noncopyable
    {
    public:

        Event<ObservableObject, const std::string&> PropertyChanged;

        virtual ~ObservableObject();

        template <typename T>
        void Add(const std::string& propertyName, const T& value = T())
        {
            mProperties[propertyName] = boost::any(value);
            OnUpdate(propertyName);
            PropertyChanged(this, propertyName);
        }

        template <typename T>
        T& Get(const std::string& propertyName)
        {
            return boost::any_cast<const T&>(mProperties[propertyName]);
        }

        template <typename T>
        const T& Get(const std::string& propertyName) const
        {
            return boost::any_cast<const T&>(mProperties[propertyName]);
        }

        template <typename T>
        void Set(const std::string& propertyName, const T& value)
        {
            mProperties[propertyName] = boost::any(value);
            OnUpdate(propertyName);
            PropertyChanged(this, propertyName);
        }

        virtual void Remove(const std::string& propertyName) NOEXCEPT final;
        virtual bool HasProperty(const std::string& propertyName) const NOEXCEPT final;

    private:

        std::unordered_map<std::string, boost::any> mProperties;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

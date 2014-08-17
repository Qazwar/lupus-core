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

        void Attach(std::shared_ptr<IObserver<T>> observer)
        {
            mObservers.push_back(observer);
        }

        void Detach(std::shared_ptr<IObserver<T>> observer) NOEXCEPT
        {
            std::remove(std::begin(mObservers), std::end(mObservers), observer);
        }

        void OnUpdate(const T& value) NOEXCEPT
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnUpdate(value);
            });
        }

        void OnError(std::exception& ex) NOEXCEPT
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [&](std::shared_ptr<IObserver<T>> observer) {
                observer->OnError(ex);
            });
        }

        void OnComplete() NOEXCEPT
        {
            std::for_each(std::begin(mObservers), std::end(mObservers), [](std::shared_ptr<IObserver<T>> observer) {
                observer->OnComplete();
            });
        }

    private:

        std::vector<std::shared_ptr<IObserver<T>>> mObservers;
    };

    template <typename T>
    class LUPUS_API ObservableProperty : public IObservable<T>, public boost::noncopyable
    {
    public:

        typedef Event<ObservableProperty<T>, const T&> ValueChangedEventHandle;

        ObservableProperty() = default;
        ObservableProperty(ObservableProperty&&) = delete;
        ObservableProperty& operator=(ObservableProperty&&) = delete;

        virtual ~ObservableProperty()
        {
            OnComplete();
        }

        const T& Get() const
        {
            return mValue;
        }

        ObservableProperty& Set(const T& value)
        {
            mValue = value;
            OnUpdate(value);
            mValueChanged.Fire(this, value);

            return *this;
        }

        ValueChangedEventHandle& ValueChanged() NOEXCEPT
        {
            return mValueChanged;
        }

        operator T() const
        {
            return mValue;
        }

        ObservableProperty& operator=(const T& value)
        {
            mValue = value;
            OnUpdate(value);
            mValueChanged.Fire(this, value);

            return *this;
        }

    private:

        T mValue;
        ValueChangedEventHandle mValueChanged;
    };

    class LUPUS_API ObservableObject : public IObservable<std::string>, public boost::noncopyable
    {
    public:

        typedef Event<ObservableObject, const std::string&> PropertyChangedEventHandle;

        virtual ~ObservableObject();

        virtual PropertyChangedEventHandle& PropertyChanged() NOEXCEPT;

        template <typename T>
        void Add(const std::string& propertyName, const T& value = T())
        {
            mProperties[propertyName] = boost::any(value);
        }

        template <typename T>
        void Get(const std::string& propertyName) const
        {
            return boost::any_cast<T>(mProperties[propertyName]);
        }

        template <typename T>
        void Set(const std::string& propertyName, const T& value)
        {
            mProperties[propertyName] = boost::any(value);
        }

        void Remove(const std::string& propertyName) NOEXCEPT;
        bool HasProperty(const std::string& propertyName) const NOEXCEPT;

    private:

        PropertyChangedEventHandle mPropertyChanged;
        std::unordered_map<std::string, boost::any> mProperties;
    };
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

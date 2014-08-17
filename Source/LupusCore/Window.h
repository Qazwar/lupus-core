#pragma once

#include "Utility.h"
#include "Event.h"
#include "Observable.h"

#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Windows {
        // TODO: Schnittstelle ausbauen und Klasse implementieren.
        class LUPUS_API Window : public boost::noncopyable
        {
        public:
            template <typename... Args>
            using WindowEvent = Event < Window, Args... > ;

            Window();
            ~Window();

            // Properties

            ObservableProperty<std::string> Uid;

            // Methods

            void Show();
            void ShowDialog();

            // Events

            WindowEvent<> Activated;
        };
    }
}

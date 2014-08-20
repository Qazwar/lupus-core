#pragma once

#include "Utility.h"
#include "Event.h"
#include "Observable.h"
#include "Size.h"
#include "Point.h"

#include <boost/noncopyable.hpp>

namespace Lupus {
    namespace Windows {
        // TODO: Schnittstelle ausbauen und Klasse implementieren.
        class LUPUS_API Window : public boost::noncopyable
        {
        public:
            template <typename... Args>
            using WindowEvent = Event < Window, Args... > ;

            template <typename T>
            using WindowProperty = ObservableProperty < Window, T > ;

            Window();
            virtual ~Window();

            // Properties

            ObservableProperty<void, std::string> Uid;
            WindowProperty<std::string> Title;
            WindowProperty<float> Brightness;
            WindowProperty<bool> Grabbed;
            WindowProperty<int> MaxWidth;
            WindowProperty<int> MinWidth;
            WindowProperty<int> MaxHeight;
            WindowProperty<int> MinHeight;
            WindowProperty<int> Width;
            WindowProperty<int> Height;
            WindowProperty<int> Left;
            WindowProperty<int> Top;
            WindowProperty<Math::Size<int>> MaxSize;
            WindowProperty<Math::Size<int>> MinSize;
            WindowProperty<Math::Size<int>> Size;
            WindowProperty<Math::Point<int>> Position;

            // Methods

            virtual void Bordered(bool) const final;
            virtual int DisplayIndex() const final;
            virtual void Hide() final;
            virtual void Maximize() final;
            virtual void Minimize() final;
            virtual void Raise() final;
            virtual void Restore() final;
            virtual void Show(bool modal = false) final;
            virtual void Refresh() final;

            // Events

            //! Fenster ist sichtbar.
            WindowEvent<> Shown;
            //! Fenster ist nicht mehr sichtbar.
            WindowEvent<> Hidden;
            //! Fenster sollte neu gezeichnet werden.
            WindowEvent<> Exposed;
            //! Fenster wurde bewegt.
            WindowEvent<> Moved;
            //! Fenstergröße wurde verändert.
            WindowEvent<> Resized;
            //! Fentergröße hat sich verändert, wird nach Resized aufgerufen.
            WindowEvent<> SizeChanged;
            //! Fenster wurde minimiert.
            WindowEvent<> Minimized;
            //! Fenster wurde maximiert.
            WindowEvent<> Maximized;
            //! Fenster hat wieder Normalgröße.
            WindowEvent<> Restored;
            //! Fenster hat jetzt Mausfokus.
            WindowEvent<> Enter;
            //! Fenster hat keinen Mausfokus mehr.
            WindowEvent<> Leave;
            //! Fenster hat jetzt Tastaturfokus.
            WindowEvent<> FocuesGained;
            //! Fenster hat Tastarufokus verloren.
            WindowEvent<> FocusLost;
            //! Fenster soll geschlossen werden.
            WindowEvent<> Close;

        protected:

            void* mHandle = nullptr;
        };
    }
}

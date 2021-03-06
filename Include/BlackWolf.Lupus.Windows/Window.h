/**
 * Copyright (C) 2014 David Wolf <d.wolf@live.at>
 *
 * This file is part of Lupus.
 * Lupus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Lupus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Lupus. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "Grid.h"
#include <BlackWolf.Lupus.Core/Utility.h>
#include <BlackWolf.Lupus.Core/Event.h>
#include <BlackWolf.Lupus.Core/Observable.h>
#include <BlackWolf.Lupus.Core/Size.h>
#include <BlackWolf.Lupus.Core/Point.h>
#include <BlackWolf.Lupus.Core/Rectangle.h>
#include <BlackWolf.Lupus.Core/String.h>

#include <unordered_map>
#include <boost/noncopyable.hpp>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif

namespace Lupus {
    namespace Windows {
        enum class WindowFlags {
            LupusCreateNoFlag(None),
            LupusCreateFlag(Fullscreen, 0),
            LupusCreateFlag(FullscreenDesktop, 1),
            LupusCreateFlag(Shown, 2),
            LupusCreateFlag(Hidden, 3),
            LupusCreateFlag(Borderless, 4),
            LupusCreateFlag(Resizable, 5),
            LupusCreateFlag(Minimized, 6),
            LupusCreateFlag(Maximized, 7),
            LupusCreateFlag(InputGrabbed, 8),
            LupusCreateFlag(InputFocus, 9),
            LupusCreateFlag(MouseFocus, 10),
            LupusCreateFlag(AllowHighDPI, 11)
        };
        LupusFlagEnumeration(WindowFlags);

        // TODO: Schnittstelle ausbauen und Klasse implementieren.
        class LUPUSWINDOWS_API Window : public boost::noncopyable
        {
            friend class Application;

        public:
            template <typename... Args>
            using WindowEvent = Event < Window, Args... > ;

            template <typename T>
            using WindowProperty = ObservableProperty < Window, T > ;

            Window(WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const String& title, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(int x, int y, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(int x, int y, int w, int h, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Point<int>& position, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Point<int>& position, const Math::Size<int>& size, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const Math::Rectangle<int>& rect, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            Window(const String& title, const Math::Rectangle<int>& rect, WindowFlags flags = WindowFlags::None) throw(std::runtime_error);
            virtual ~Window();

            // Properties

            ObservableProperty<void, String> Uid;
            WindowProperty<String> Title;
            WindowProperty<float> Brightness;
            WindowProperty<bool> Grabbed;
            WindowProperty<Math::Size<int>> MaxSize;
            WindowProperty<Math::Size<int>> MinSize;
            WindowProperty<Math::Size<int>> Size;
            WindowProperty<Math::Point<int>> Position;
            WindowProperty<Math::Rectangle<int>> Rectangle;

            // Methods
            
            virtual void Bordered(bool) const final;
            virtual int DisplayIndex() const final;
            virtual std::shared_ptr<Grid> Grid() const final;
            virtual void Hide() final;
            virtual void Maximize() final;
            virtual void Minimize() final;
            virtual void Raise() final;
            virtual void Refresh() throw(std::runtime_error) final;
            virtual void Restore() final;
            virtual void Show() final;
            virtual void ShowDialog() final;
            virtual std::shared_ptr<ObservableObject> ViewModel() const;
            virtual void ViewModel(std::shared_ptr<ObservableObject> viewModel);

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

            static Window* GetWindowFromId(uint32_t);

            static const int PositionCentered;
            static const int PositionUndefined;

        private:

            uint32_t ConvertFlags(WindowFlags flags);
            void Initialize();

            void* mHandle = nullptr;
            std::shared_ptr<Windows::Grid> mGrid;
            std::shared_ptr<ObservableObject> mViewModel;
            static std::unordered_map<uint32_t, Window*> smMappedWindows;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

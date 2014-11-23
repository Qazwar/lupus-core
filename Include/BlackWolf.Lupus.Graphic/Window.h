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
    namespace Graphic {
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
        class LUPUSGRAPHIC_API Window : public boost::noncopyable
        {
            friend class Application;

        public:
            template <typename... Args>
            using WindowEvent = Event < Window, Args... > ;

            template <typename T>
            using WindowProperty = ObservableProperty < Window, T > ;

            Window(WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(const String& title, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(int x, int y, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(int x, int y, int w, int h, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(const Math::Point<int>& position, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(const Math::Point<int>& position, const Math::Size<int>& size, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(const Math::Rectangle<int>& rect, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
            Window(const String& title, const Math::Rectangle<int>& rect, WindowFlags flags = WindowFlags::None) throw(RuntimeError);
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
            virtual Pointer<Graphic::Grid> Grid() const final;
            virtual void Hide() final;
            virtual void Maximize() final;
            virtual void Minimize() final;
            virtual void Raise() final;
            virtual void Refresh() throw(RuntimeError) final;
            virtual void Restore() final;
            virtual void Show() final;
            virtual void ShowDialog() final;
            virtual Pointer<ObservableObject> ViewModel() const;
            virtual void ViewModel(Pointer<ObservableObject> viewModel);

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
            Pointer<Graphic::Grid> mGrid;
            Pointer<ObservableObject> mViewModel;
            static Collection<uint32_t, Window*> smMappedWindows;
        };
    }
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif

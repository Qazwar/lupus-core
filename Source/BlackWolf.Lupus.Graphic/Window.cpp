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
#include "Window.h"
#include "UIElement.h"
#include <SDL/SDL_video.h>
#include <SDL/SDL_render.h>



namespace Lupus {
    namespace Graphic {
        Window::Window(WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                128,
                128,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }
        Window::Window(const String& title, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                title.ToUTF8().c_str(),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                128,
                128,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }

        Window::Window(int x, int y, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                x,
                y,
                128,
                128,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }
        
        Window::Window(int x, int y, int w, int h, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                x,
                y,
                w,
                h,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }
        
        Window::Window(const Math::Point<int>& position, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                position.X,
                position.Y,
                128,
                128,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }
        
        Window::Window(const Math::Point<int>& position, const Math::Size<int>& size, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                position.X,
                position.Y,
                size.Width,
                size.Height,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }

        Window::Window(const Math::Rectangle<int>& rect, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                rect.X,
                rect.Y,
                rect.Width,
                rect.Height,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }

        Window::Window(const String& title, const Math::Rectangle<int>& rect, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                title.ToUTF8().c_str(),
                rect.X,
                rect.Y,
                rect.Width,
                rect.Height,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw RuntimeError(SDL_GetError());
            }

            mHandle = window;
            Initialize();
        }

        Window::~Window()
        {
            if (mHandle) {
                smMappedWindows.erase(SDL_GetWindowID(force_cast<SDL_Window*>(mHandle)));
                SDL_DestroyRenderer(SDL_GetRenderer(force_cast<SDL_Window*>(mHandle)));
                SDL_DestroyWindow(force_cast<SDL_Window*>(mHandle));
                mHandle = nullptr;
            }
        }

        void Window::Bordered(bool value) const
        {
            return SDL_SetWindowBordered(force_cast<SDL_Window*>(mHandle), value ? SDL_TRUE : SDL_FALSE);
        }

        int Window::DisplayIndex() const
        {
            return SDL_GetWindowDisplayIndex(force_cast<SDL_Window*>(mHandle));
        }

        Pointer<Grid> Window::Grid() const
        {
            return mGrid;
        }

        void Window::Hide()
        {
            SDL_HideWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::Maximize()
        {
            SDL_MaximizeWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::Minimize()
        {
            SDL_MinimizeWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::Raise()
        {
            SDL_RaiseWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::Refresh()
        {
            auto renderer = SDL_GetRenderer(force_cast<SDL_Window*>(mHandle));
            SDL_RenderPresent(renderer);

            if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0) {
                throw RuntimeError(SDL_GetError());
            } else if (SDL_RenderClear(renderer) != 0) {
                throw RuntimeError(SDL_GetError());
            }
        }

        void Window::Restore()
        {
            SDL_RestoreWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::Show()
        {
            SDL_ShowWindow(force_cast<SDL_Window*>(mHandle));
        }

        void Window::ShowDialog()
        {
            // TODO: Fenster anzeigen.
        }

        Pointer<ObservableObject> Window::ViewModel() const
        {
            return mViewModel;
        }

        void Window::ViewModel(Pointer<ObservableObject> viewModel)
        {
            mViewModel = viewModel;
        }

        Window* Window::GetWindowFromId(U32 id)
        {
            return smMappedWindows.at(id);
        }

        U32 Window::ConvertFlags(WindowFlags flags)
        {
            U32 sdlFlags = 0;

            if (HasFlag(WindowFlags::AllowHighDPI, flags)) {
                sdlFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
            }

            if (HasFlag(WindowFlags::Borderless, flags)) {
                sdlFlags |= SDL_WINDOW_BORDERLESS;
            }

            if (HasFlag(WindowFlags::Fullscreen, flags)) {
                sdlFlags |= SDL_WINDOW_FULLSCREEN;
            }

            if (HasFlag(WindowFlags::FullscreenDesktop, flags)) {
                sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            }

            if (HasFlag(WindowFlags::Hidden, flags)) {
                sdlFlags |= SDL_WINDOW_HIDDEN;
            }

            if (HasFlag(WindowFlags::InputFocus, flags)) {
                sdlFlags |= SDL_WINDOW_INPUT_FOCUS;
            }

            if (HasFlag(WindowFlags::InputGrabbed, flags)) {
                sdlFlags |= SDL_WINDOW_INPUT_GRABBED;
            }

            if (HasFlag(WindowFlags::Maximized, flags)) {
                sdlFlags |= SDL_WINDOW_MAXIMIZED;
            }

            if (HasFlag(WindowFlags::Minimized, flags)) {
                sdlFlags |= SDL_WINDOW_MINIMIZED;
            }

            if (HasFlag(WindowFlags::MouseFocus, flags)) {
                sdlFlags |= SDL_WINDOW_MOUSE_FOCUS;
            }

            if (HasFlag(WindowFlags::Resizable, flags)) {
                sdlFlags |= SDL_WINDOW_RESIZABLE;
            }

            if (HasFlag(WindowFlags::Shown, flags)) {
                sdlFlags |= SDL_WINDOW_SHOWN;
            }

            return sdlFlags;
        }

        void Window::Initialize()
        {
            auto window = force_cast<SDL_Window*>(mHandle);

            Uid = RandomString(sizeof(void*));

            Title.mGetter = [window]() { return SDL_GetWindowTitle(window); };
            Title.mSetter = [window](const String& value) { SDL_SetWindowTitle(window, value.ToUTF8().c_str()); };
            Brightness.mGetter = [window]() { return SDL_GetWindowBrightness(window); };
            Brightness.mSetter = [window](const float& value) { SDL_SetWindowBrightness(window, value); };
            Grabbed.mGetter = [window]() { return SDL_GetWindowGrab(window) == SDL_TRUE; };
            Grabbed.mSetter = [window](const bool& value) { SDL_SetWindowGrab(window, value ? SDL_TRUE : SDL_FALSE); };

            MaxSize.mGetter = [window]() {
                int w, h;
                SDL_GetWindowMaximumSize(window, &w, &h);
                return Math::Size<int>(w, h);
            };
            MaxSize.mSetter = [window](const Math::Size<int>& size) {
                SDL_SetWindowMaximumSize(window, size.Width, size.Height);
            };

            MinSize.mGetter = [window]() {
                int w, h;
                SDL_GetWindowMinimumSize(window, &w, &h);
                return Math::Size<int>(w, h);
            };
            MinSize.mSetter = [window](const Math::Size<int>& size) {
                SDL_SetWindowMinimumSize(window, size.Width, size.Height);
            };

            Size.mGetter = [window]() {
                int w, h;
                SDL_GetWindowSize(window, &w, &h);
                return Math::Size<int>(w, h);
            };
            Size.mSetter = [window](const Math::Size<int>& size) {
                SDL_SetWindowSize(window, size.Width, size.Height);
            };

            Position.mGetter = [window]() {
                int x, y;
                SDL_GetWindowPosition(window, &x, &y);
                return Math::Point<int>(x, y);
            };
            Position.mSetter = [window](const Math::Point<int>& point) {
                SDL_SetWindowPosition(window, point.X, point.Y);
            };

            Rectangle.mGetter = [this]() {
                return Math::Rectangle<int>(this->Position, this->Size);
            };
            Rectangle.mSetter = [this](const Math::Rectangle<int>& rect) {
                this->Size = rect.Size();
                this->Position = rect.Position();
            };

            smMappedWindows[SDL_GetWindowID(window)] = this;
            mGrid = MakePointer<Graphic::Grid>();
        }

        const int Window::PositionUndefined = SDL_WINDOWPOS_UNDEFINED;
        const int Window::PositionCentered = SDL_WINDOWPOS_CENTERED;
        Collection<U32, Window*> Window::smMappedWindows;
    }
}

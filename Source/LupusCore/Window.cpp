#include "Window.h"
#include <SDL/SDL_video.h>
#include <SDL/SDL_render.h>

using namespace std;

namespace Lupus {
    namespace Windows {
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
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
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
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
        }
        
        Window::Window(int x, int y, int w, int h, WindowFlags flags)
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                w,
                h,
                ConvertFlags(flags));

            if (!window || !SDL_CreateRenderer(window, -1, 0)) {
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
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
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
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
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
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
                throw runtime_error(SDL_GetError());
            }

            mHandle = window;
            SetPropertyHandles();
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

        void Window::Refresh()
        {
            auto renderer = SDL_GetRenderer(force_cast<SDL_Window*>(mHandle));
            SDL_RenderPresent(renderer);
            
            if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0) {
                throw runtime_error(SDL_GetError());
            } else if (SDL_RenderClear(renderer) != 0) {
                throw runtime_error(SDL_GetError());
            }
        }

        Window* Window::GetWindowFromId(uint32_t id)
        {
            return smMappedWindows.at(id);
        }

        uint32_t Window::ConvertFlags(WindowFlags flags)
        {
            uint32_t sdlFlags = 0;

            if (LupusHasFlag(WindowFlags::AllowHighDPI, flags)) {
                sdlFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
            }

            if (LupusHasFlag(WindowFlags::Borderless, flags)) {
                sdlFlags |= SDL_WINDOW_BORDERLESS;
            }

            if (LupusHasFlag(WindowFlags::Fullscreen, flags)) {
                sdlFlags |= SDL_WINDOW_FULLSCREEN;
            }

            if (LupusHasFlag(WindowFlags::FullscreenDesktop, flags)) {
                sdlFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
            }

            if (LupusHasFlag(WindowFlags::Hidden, flags)) {
                sdlFlags |= SDL_WINDOW_HIDDEN;
            }

            if (LupusHasFlag(WindowFlags::InptuFocus, flags)) {
                sdlFlags |= SDL_WINDOW_INPUT_FOCUS;
            }

            if (LupusHasFlag(WindowFlags::InputGrabbed, flags)) {
                sdlFlags |= SDL_WINDOW_INPUT_GRABBED;
            }

            if (LupusHasFlag(WindowFlags::Maximized, flags)) {
                sdlFlags |= SDL_WINDOW_MAXIMIZED;
            }

            if (LupusHasFlag(WindowFlags::Minimized, flags)) {
                sdlFlags |= SDL_WINDOW_MINIMIZED;
            }

            if (LupusHasFlag(WindowFlags::MouseFocus, flags)) {
                sdlFlags |= SDL_WINDOW_MOUSE_FOCUS;
            }

            if (LupusHasFlag(WindowFlags::Resizable, flags)) {
                sdlFlags |= SDL_WINDOW_RESIZABLE;
            }

            if (LupusHasFlag(WindowFlags::Shown, flags)) {
                sdlFlags |= SDL_WINDOW_SHOWN;
            }

            return sdlFlags;
        }

        void Window::SetPropertyHandles()
        {
            auto window = force_cast<SDL_Window*>(mHandle);

            Uid = RandomString(sizeof(void*));

            Title.mGetter = [window]() { return SDL_GetWindowTitle(window); };
            Title.mSetter = [window](const string& value) { SDL_SetWindowTitle(window, value.c_str()); };
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
        }

        const int Window::PositionUndefined = SDL_WINDOWPOS_UNDEFINED;
        const int Window::PositionCentered = SDL_WINDOWPOS_CENTERED;
        unordered_map<uint32_t, Window*> Window::smMappedWindows;
    }
}

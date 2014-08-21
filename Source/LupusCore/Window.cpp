#include "Window.h"
#include <SDL/SDL_video.h>
#include <SDL/SDL_render.h>

using namespace std;

namespace Lupus {
    namespace Windows {
        // TODO: Window implementieren

        Window::Window()
        {
            SDL_Window* window = SDL_CreateWindow(
                "",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                128,
                128,
                SDL_WINDOW_RESIZABLE | SDL_WINDOW_INPUT_GRABBED | SDL_WINDOW_HIDDEN);

            if (!window || SDL_CreateRenderer(window, -1, 0)) {
                throw runtime_error(SDL_GetError());
            }

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

            smMappedWindows[SDL_GetWindowID(window)] = this;
            mHandle = window;
        }

        Window::~Window()
        {
            if (mHandle) {
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

        const int Window::PositionUndefined = SDL_WINDOWPOS_UNDEFINED;
        const int Window::PositionCentered = SDL_WINDOWPOS_CENTERED;
        unordered_map<uint32_t, Window*> Window::smMappedWindows;
    }
}

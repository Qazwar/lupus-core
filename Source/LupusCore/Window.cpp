#include "Window.h"
#include <SDL/SDL_video.h>

namespace Lupus {
    namespace Windows {
        // TODO: Window implementieren

        Window::Window()
        {
            Uid = RandomString(sizeof(void*));
        }

        Window::~Window()
        {
            if (mHandle) {
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

        void Window::Show(bool modal)
        {
            // TODO: Fenster anzeigen, unterscheiden zwischen Modal.
        }

        void Window::Refresh()
        {
            // TODO: Fenster aktualisieren.
        }
    }
}

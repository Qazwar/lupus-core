#include "Window.h"
#include <SDL/SDL_video.h>

namespace Lupus {
    namespace Windows {
        Window::Window()
        {
            // TODO: Funktionen ausbauen und entsprechend an SDL anpassen.

            Uid.ValueChanged += [this](void* sender, const std::string& value) {
                // ...
            };

            Title.ValueChanged += [this](void* sender, const std::string& value) {
                SDL_SetWindowTitle(force_cast<SDL_Window*>(this->mHandle), value.c_str());
            };

            Brightness.ValueChanged += [this](void* sender, const float& value) {
                SDL_SetWindowBrightness(force_cast<SDL_Window*>(this->mHandle), value);
            };

            Grabbed.ValueChanged += [this](void* sender, const bool& value) {
                SDL_SetWindowGrab(force_cast<SDL_Window*>(this->mHandle), value ? SDL_TRUE : SDL_FALSE);
            };

            MaxWidth.ValueChanged += [this](void* sender, const int& value) {

            };

            MinWidth.ValueChanged += [this](void* sender, const int& value) {

            };

            Width.ValueChanged += [this](void* sender, const int& value) {

            };

            MaxHeight.ValueChanged += [this](void* sender, const int& value) {

            };

            MinHeight.ValueChanged += [this](void* sender, const int& value) {

            };

            Height.ValueChanged += [this](void* sender, const int& value) {

            };

            Left.ValueChanged += [this](void* sender, const int& value) {

            };

            Top.ValueChanged += [this](void* sender, const int& value) {

            };
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

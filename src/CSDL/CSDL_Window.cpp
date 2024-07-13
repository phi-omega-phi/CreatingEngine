/**
  * @file   CSDL_Window.cpp
  * @author 0And1Story
  * @date   2024-02-29
  * @brief  
  */

#include "CSDL_Window.h"
#include "CSDL_Renderer.h"

#include "CSDL_error.h"

namespace CSDL::SDL {
    Window::Window(SDL_Window* SDL_window): _window(SDL_window) {}

    Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags) {
        _window = SDL_CreateWindow(title, x, y, w, h, flags);
    }

    Window::~Window() {
        SDL_DestroyWindow(_window);
    }

    Window::Window(Window&& other) noexcept : _window(other._window) {
        other._window = nullptr;
    }

    Window& Window::operator=(Window&& other) noexcept {
        if (std::addressof(other) == this) return *this;
        SDL_DestroyWindow(_window);
        _window = other._window;
        other._window = nullptr;
        return *this;
    }

    SDL_Window* Window::GetHandler() const noexcept {
        return _window;
    }

    SDL_Window* Window::operator*() const noexcept {
        return _window;
    }

    SDL_Window* Window::operator->() const noexcept {
        return _window;
    }

    void Window::SetAlwaysOnTop(bool on_top) {
        SDL_SetWindowAlwaysOnTop(_window, static_cast<SDL_bool>(on_top));
    }

    void Window::SetBordered(bool bordered) {
        SDL_SetWindowBordered(_window, static_cast<SDL_bool>(bordered));
    }

    void Window::SetBrightness(float brightness) {
        if (SDL_SetWindowBrightness(_window, brightness)) throw error::SDLWindowError();
    }

    void* Window::SetData(const char* name, void* userdata) {
        return SDL_SetWindowData(_window, name, userdata);
    }

    void Window::SetDisplayMode(const SDL_DisplayMode* mode) {
        if (SDL_SetWindowDisplayMode(_window, mode)) throw error::SDLWindowError();
    }

    void Window::SetFullscreen(Uint32 flags) {
        if (SDL_SetWindowFullscreen(_window, flags)) throw error::SDLWindowError();
    }

    void Window::SetGammaRamp(const Uint16* red, const Uint16* green, const Uint16* blue) {
        if (SDL_SetWindowGammaRamp(_window, red, green, blue)) throw error::SDLWindowError();
    }

    void Window::SetGrab(bool grabbed) {
        SDL_SetWindowGrab(_window, static_cast<SDL_bool>(grabbed));
    }

    void Window::SetHitTest(SDL_HitTest callback, void* callback_data) {
        if (SDL_SetWindowHitTest(_window, callback, callback_data)) throw error::SDLWindowError();
    }

    void Window::SetIcon(SDL_Surface* icon) {
        SDL_SetWindowIcon(_window, icon);
    }

    void Window::SetInputFocus() {
        if (SDL_SetWindowInputFocus(_window)) throw error::SDLWindowError();
    }

    void Window::SetKeyboardGrab(bool grabbed) {
        SDL_SetWindowKeyboardGrab(_window, static_cast<SDL_bool>(grabbed));
    }

    void Window::SetMaximumSize(int max_w, int max_h) {
        SDL_SetWindowMaximumSize(_window, max_w, max_h);
    }

    void Window::SetMinimumSize(int min_w, int min_h) {
        SDL_SetWindowMinimumSize(_window, min_w, min_h);
    }

    void Window::SetModalFor(const Window& parent_window) {
        SDL_SetWindowModalFor(_window, parent_window._window);
    }

    void Window::SetMouseGrab(bool grabbed) {
        SDL_SetWindowMouseGrab(_window, static_cast<SDL_bool>(grabbed));
    }

    void Window::SetMouseRect(const SDL_Rect& rect) {
        if (SDL_SetWindowMouseRect(_window, &rect)) throw error::SDLWindowError();
    }

    void Window::SetOpacity(float opacity) {
        if (SDL_SetWindowOpacity(_window, opacity)) throw error::SDLWindowError();
    }

    void Window::SetPosition(int x, int y) {
        SDL_SetWindowPosition(_window, x, y);
    }

    void Window::SetResizable(bool resizable) {
        SDL_SetWindowResizable(_window, static_cast<SDL_bool>(resizable));
    }

    void Window::SetShape(const Surface& shape, SDL_WindowShapeMode* shape_mode) {
        if (SDL_SetWindowShape(_window, shape.GetHandler(), shape_mode)) throw error::SDLWindowError();
    }

    void Window::SetSize(int w, int h) {
        SDL_SetWindowSize(_window, w, h);
    }

    void Window::SetTitle(const char* title) {
        SDL_SetWindowTitle(_window, title);
    }

    void Window::GetBordersSize(int& top, int& left, int& bottom, int& right) {
        if (SDL_GetWindowBordersSize(_window, &top, &left, &bottom, &right)) throw error::SDLWindowError();
    }

    float Window::GetBrightness() {
        return SDL_GetWindowBrightness(_window);
    }

    int Window::GetDisplayIndex() {
        return SDL_GetWindowDisplayIndex(_window);
    }

    void Window::GetDisplayMode(SDL_DisplayMode* mode) {
        if (SDL_GetWindowDisplayMode(_window, mode)) throw error::SDLWindowError();
    }

    Uint32 Window::GetFlags() {
        return SDL_GetWindowFlags(_window);
    }

    Window Window::GetWindowFromID(Uint32 id) {
        return SDL_GetWindowFromID(id);
    }

    void Window::GetGammaRamp(Uint16* red, Uint16* green, Uint16* blue) {
        if (SDL_GetWindowGammaRamp(_window, red, green, blue)) throw error::SDLWindowError();
    }

    bool Window::GetGrab() {
        return SDL_GetWindowGrab(_window);
    }

    void* Window::GetICCProfile(size_t& size) {
        return SDL_GetWindowICCProfile(_window, &size);
    }

    Uint32 Window::GetID() {
        return SDL_GetWindowID(_window);
    }

    bool Window::GetKeyboardGrab() {
        return SDL_GetWindowKeyboardGrab(_window);
    }

    void Window::GetMaximumSize(int& w, int& h) {
        SDL_GetWindowMaximumSize(_window, &w, &h);
    }

    void Window::GetMinimumSize(int& w, int& h) {
        SDL_GetWindowMinimumSize(_window, &w, &h);
    }

    bool Window::GetMouseGrab() {
        return SDL_GetWindowMouseGrab(_window);
    }

    Rect Window::GetMouseRect() {
        return *SDL_GetWindowMouseRect(_window);
    }

    float Window::GetOpacity() {
        float out_opacity;
        if (SDL_GetWindowOpacity(_window, &out_opacity)) throw error::SDLWindowError();
        return out_opacity;
    }

    Uint32 Window::GetPixelFormat() {
        return SDL_GetWindowPixelFormat(_window);
    }

    void Window::GetPosition(int& x, int& y) {
        SDL_GetWindowPosition(_window, &x, &y);
    }

    void Window::GetSize(int& w, int& h) {
        SDL_GetWindowSize(_window, &w, &h);
    }

    void Window::GetSizeInPixels(int& w, int& h) {
        SDL_GetWindowSizeInPixels(_window, &w, &h);
    }

    Surface Window::GetSurface() {
        return SDL_GetWindowSurface(_window);
    }

    const char* Window::GetTitle() {
        return SDL_GetWindowTitle(_window);
    }

    void Window::UpdateSurface() {
        SDL_UpdateWindowSurface(_window);
    }

    Renderer Window::GetRenderer() {
        return SDL_GetRenderer(_window);
    }
}

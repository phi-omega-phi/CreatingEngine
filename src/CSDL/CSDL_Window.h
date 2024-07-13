/**
  * @file   CSDL_Window.h
  * @author 0And1Story
  * @date   2024-02-29
  * @brief  
  */

#ifndef _CSDL_WINDOW_H_
#define _CSDL_WINDOW_H_

#include "SDL.h"

#include "CSDL_Surface.h"

namespace CSDL::SDL {
    class Renderer;

    class Window {
    private:
        SDL_Window* _window;

    public:
        Window(SDL_Window* SDL_window);
        Window(const char* title, int x, int y, int w, int h, Uint32 flags);
        ~Window();

        Window(Window&& other) noexcept;
        Window(const Window&) = delete;
        Window& operator=(Window&& other) noexcept;
        Window& operator=(const Window&) = delete;

        [[nodiscard]] SDL_Window* GetHandler() const noexcept;

        SDL_Window* operator*() const noexcept;
        SDL_Window* operator->() const noexcept;

        void SetAlwaysOnTop(bool on_top);
        void SetBordered(bool bordered);
        void GetBordersSize(int& top, int& left, int& bottom, int& right);
        float GetBrightness();
        void SetBrightness(float brightness);
        void* SetData(const char* name, void* userdata);
        int GetDisplayIndex();
        void GetDisplayMode(SDL_DisplayMode* mode);
        void SetDisplayMode(const SDL_DisplayMode* mode);
        Uint32 GetFlags();
        static Window GetWindowFromID(Uint32 id);
        void SetFullscreen(Uint32 flags);
        void GetGammaRamp(Uint16* red, Uint16* green, Uint16* blue);
        void SetGammaRamp(const Uint16* red, const Uint16* green, const Uint16* blue);
        bool GetGrab();
        void SetGrab(bool grabbed);
        void SetHitTest(SDL_HitTest callback, void* callback_data);
        void* GetICCProfile(size_t& size);
        Uint32 GetID();
        void SetIcon(SDL_Surface* icon);
        void SetInputFocus();
        bool GetKeyboardGrab();
        void SetKeyboardGrab(bool grabbed);
        void GetMaximumSize(int& w, int& h);
        void SetMaximumSize(int max_w, int max_h);
        void GetMinimumSize(int& w, int& h);
        void SetMinimumSize(int min_w, int min_h);
        void SetModalFor(const Window& parent_window);
        bool GetMouseGrab();
        void SetMouseGrab(bool grabbed);
        Rect GetMouseRect();
        void SetMouseRect(const SDL_Rect& rect);
        float GetOpacity();
        void SetOpacity(float opacity);
        Uint32 GetPixelFormat();
        void GetPosition(int& x, int& y);
        void SetPosition(int x, int y);
        void SetResizable(bool resizable);
        void SetShape(const Surface& shape, SDL_WindowShapeMode* shape_mode);
        void GetSize(int& w, int& h);
        void SetSize(int w, int h);
        void GetSizeInPixels(int& w, int& h);
        Surface GetSurface();
        const char* GetTitle();
        void SetTitle(const char* title);

        void UpdateSurface();

        Renderer GetRenderer();
    };
}

#endif //_CSDL_WINDOW_H_

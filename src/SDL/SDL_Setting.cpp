/**
  * @file   SDL_Setting.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "SDL_Setting.h"

__SDL_Setting& __SDL_Setting::Instance() {
    static __SDL_Setting instance;
    return instance;
}

int __SDL_Setting::Check() {
    if (!_window.width || !_window.height || !_window.handler || !_renderer) {
        SDL_FileError("Something necessary is not configured.");
        return -1;
    }
    return 0;
}

void __SDL_Setting::SetWindowSize(const int& w_, const int& h_) {
    if (w_ <= 0 || h_ <= 0) {
        SDL_FileError("The width and height must be positive integers.");
        return;
    }
    if (_window.width && _window.height) {
        SDL_FileError("Window Size could only be configured once.");
        return;
    }

    _window.width = w_;
    _window.height = h_;
}

void __SDL_Setting::SetWindowScale(const double scale_) {
    _window.scale = scale_;
}

void __SDL_Setting::SetWindowHandler(SDL_Window* handler_) {
    _window.handler = handler_;
}

void __SDL_Setting::SetRenderer(SDL_Renderer* renderer_) {
    _renderer = renderer_;
}

/// The global instance of __SDL_Setting.
__SDL_Setting& settings = __SDL_Setting::Instance();

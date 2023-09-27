/**
 * @file    SDL_Setting.h
 * @author  0And1Story
 * @date    2023-7-26
 * @brief   The Configuration Module.
 */

#ifndef _SDL_SETTING_H_
#define _SDL_SETTING_H_

#include "SDL.h"
#include "SDL_FileLog.h"

/**
 * @brief       The constant settings of the program.
 * @attention   This is a singleton.\n
 *              It can not be instantiated.\n
 *              Please use @code __SDL_Setting::instance() @endcode to get the instance of the singleton if necessary,
 *              but there is a global instance called "settings" so we don't recommend.
 * @class       __SDL_Setting
 */
class __SDL_Setting {
private:
    struct WindowSetting { int width = 0, height = 0; double scale = 1; SDL_Window* handler = nullptr; };
    WindowSetting _window;
    SDL_Renderer* _renderer = nullptr;

private:
    __SDL_Setting() = default;
    ~__SDL_Setting() = default;

public:
    WindowSetting const& window = _window;
    SDL_Renderer* const& renderer = _renderer;

public:
    __SDL_Setting(const __SDL_Setting&) = delete;
    const __SDL_Setting& operator=(const __SDL_Setting&) = delete;

    static __SDL_Setting& Instance();

    int Check();

    void SetWindowSize(const int& w_, const int& h_);

    void SetWindowScale(double scale_);

    void SetWindowHandler(SDL_Window* handler_);

    void SetRenderer(SDL_Renderer* renderer_);
};

#endif //_SDL_SETTING_H_

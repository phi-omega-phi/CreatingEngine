/**
 * @file    SDL_Const.h
 * @author  0And1Story
 * @date    2023-7-8
 * @brief   The Definition of Const Values.
 */

#ifndef _SDL_CONST_H_
#define _SDL_CONST_H_

#include "SDL.h"

/**
 * @name    WindowConfig
 * @brief   Configurations of the window.
 * @{
 */
#define WINDOW_WIDTH    1280    ///< The standard width of development.
#define WINDOW_HEIGHT   720     ///< The standard height of development.
#define WINDOW_SCALE    1       ///< The scale of client.
/** @} */

/**
 * @name    LogConfig
 * @brief   Configurations of the log system.
 * @see     LogLevel
 */
#ifndef NDEBUG
#define LOG_LEVEL   LOG_LEVEL_DEBUG     ///< The Log Level Setting(Debug Mode).
#else
#define LOG_LEVEL   LOG_LEVEL_WARNING   ///< The Log Level Setting(Release Mode).
#endif

#define LOG_OUTPUT  stderr  ///< The output stream of console log.

#define LIGHT_THEME 1
#define DARK_THEME  0

#define COLOR_THEME LIGHT_THEME ///< The theme of the console log.

#define __NAME__(variable) (#variable)

#define SDL_USER_RENDER     (SDL_USEREVENT + 1)

typedef void (*CALLBACK_FUNC)(void* param);    ///< The type of callback function.

/// The structure to save size information.
struct SDL_Size {
    int w;  ///< The width.
    int h;  ///< The height.
};

/**
 * @name    ScaleOperator
 * @brief   The method to scale window and rect.
 * @{
 */
const SDL_Rect& operator*=(SDL_Rect& rect_, const int& scale_);
const SDL_Rect& operator*=(SDL_Rect& rect_, const double& scale_);
SDL_Rect operator*(const SDL_Rect& rect_, const int& scale_);
SDL_Rect operator*(const SDL_Rect& rect_, const double& scale_);
SDL_Rect operator/(const SDL_Rect& rect_, const int& scale_);
SDL_Rect operator/(const SDL_Rect& rect_, const double& scale_);
/** @} */

const SDL_Point& operator*=(SDL_Point& position_, const int& scale_);
const SDL_Point& operator*=(SDL_Point& position_, const double& scale_);
SDL_Point operator*(const SDL_Point& position_, const int& scale_);
SDL_Point operator*(const SDL_Point& position_, const double& scale_);
SDL_Point operator/(const SDL_Point& position_, const int& scale_);
SDL_Point operator/(const SDL_Point& position_, const double& scale_);
const SDL_Point& operator+=(SDL_Point& position_A, const SDL_Point& position_B);
const SDL_Point& operator-=(SDL_Point& position_A, const SDL_Point& position_B);
SDL_Point operator+(const SDL_Point& position_A, const SDL_Point& position_B);
SDL_Point operator-(const SDL_Point& position_A, const SDL_Point& position_B);

class __SDL_FileLog;
extern __SDL_FileLog& SDL_FileLog;
class __SDL_Setting;
extern __SDL_Setting& settings;
class __SDL_ResourceReader;
extern __SDL_ResourceReader& SDL_ResourceReader;

#endif //_SDL_CONST_H_

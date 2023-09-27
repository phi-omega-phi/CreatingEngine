/**
 * @file    SDL_Widget.h
 * @author  0And1Story
 * @date    2023-7-9
 * @brief   The Widget Module for SDL.
 */

#ifndef _SDL_WIDGET_H_
#define _SDL_WIDGET_H_

#include "SDL.h"
#include "XML_Parser.h"

/**
 * @brief       The interface of widgets.
 * @interface   SDL_Widget
 * @details     This is the base class of all widgets.
 * @note        We defined a standard window size, e.g. 1280x720, as the standard size of the window,
 *              and we use a scale value to change the factual size of the window.\n
 *              The standard window size is made constant when initializing the program,
 *              and we change the window size by the scale value on the premise of locking of aspect ratio.\n
 *              On designing we generally use relative coordinate of the standard size,
 *              which is more explicit and ignores unnecessary details.\n
 *              We strongly suggest avoiding using the factual coordinate(or we called rendering coordinate).\n\n
 *              According to this, we divided setters and getters into two types:\n
 *              - Relative: Its name doesn't contain "Render".\n
 *                          It means the setter's arguments should be the relative coordinate,
 *                          or the getter's return value is the relative coordinate, according to the standard size.\n
 *              - Absolute: Its name contains "Render".\n
 *                          It means the setter's arguments should be the absolute coordinate(or we called factual/rendering coordinate)
 *                          or the getter's return value is the absolute coordinate, according to the factual size of the window.\n
 *                          **Attention: Actually we don't recommend to use factual or rendering coordinate in setters.**
 */
class SDL_Widget {
public:
    virtual ~SDL_Widget() = default;
    virtual void SetPosition(const int& x, const int& y) = 0;
    virtual void SetPosition(const SDL_Point& position) = 0;
    [[nodiscard]] virtual SDL_Point GetPosition() const = 0;
    virtual void Render() = 0;
};

class SDL_InteractiveWidget : public SDL_Widget {
public:
    virtual void EventHandler(const SDL_Event & event) = 0;
};

#endif //_SDL_WIDGET_H_

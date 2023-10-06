/**
  * @file   SDL_OverflowWidget.h
  * @author 0And1Story
  * @date   2023-10-06
  * @brief  
  */

#ifndef _SDL_OVERFLOW_WIDGET_H_
#define _SDL_OVERFLOW_WIDGET_H_

#include "SDL.h"
#include "SDL_Widget.h"
#include <list>

class SDL_OverflowWidget : public SDL_Widget {
private:
    ::std::list<SDL_Widget*> _widgets;
    SDL_Point _position;

public:
    SDL_OverflowWidget();
    SDL_OverflowWidget(const int& x, const int& y);

    ~SDL_OverflowWidget() override;

    void AddWidget(SDL_Widget* widget_);

    void PushBack(SDL_Widget* widget_);
    void PopBack(SDL_Widget* widget_);

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    [[nodiscard]] SDL_Rect GetRect() const override;

    void Render() override;
};


#endif //_SDL_OVERFLOW_WIDGET_H_

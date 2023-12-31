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

class SDL_OverflowWidget : public SDL_InteractiveWidget {
private:
    ::std::list<SDL_Widget*> _widgets;
    SDL_Point _position;
    int _line_space = 0;

public:
    SDL_OverflowWidget();
    SDL_OverflowWidget(const int& x_, const int& y_);
    SDL_OverflowWidget(const int& x_, const int& y_, const int& line_space_);

    ~SDL_OverflowWidget() override;

    void AddWidget(SDL_Widget* widget_);

    void PushBack(SDL_Widget* widget_);
    void PopBack(SDL_Widget* widget_);

    bool Empty() const;

    void Clear();

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    [[nodiscard]] SDL_Rect GetRect() const override;

    int EventHandler(const SDL_Event& event_) override;

    void Render() override;
};


#endif //_SDL_OVERFLOW_WIDGET_H_

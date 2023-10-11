/**
  * @file   SDL_MultiColumnWidget.h
  * @author 0And1Story
  * @date   2023-10-11
  * @brief  
  */

#ifndef _SDL_MULTI_COLUMN_WIDGET_H_
#define _SDL_MULTI_COLUMN_WIDGET_H_

#include "SDL.h"
#include "SDL_Widget.h"
#include "SDL_Setting.h"

#include <list>
#include <string>

class SDL_MultiColumnWidget : public SDL_InteractiveWidget {
private:
    struct ListType { ::std::string name; SDL_Widget* widget; };
    ::std::list<ListType> _widgets;
    SDL_Rect _rect;

public:
    SDL_MultiColumnWidget();
    SDL_MultiColumnWidget(const int& x_, const int& y_);
    SDL_MultiColumnWidget(const int& x_, const int& y_, const int& w_, const int& h_);

    ~SDL_MultiColumnWidget() override;

    void AddWidget(const ::std::string& name_, SDL_Widget* widget_);
    void RemoveWidget(const ::std::string& name_);

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    [[nodiscard]] SDL_Rect GetRect() const override;

    int EventHandler(const SDL_Event& event_) override;

    void Render() override;
};


#endif //_SDL_MULTI_COLUMN_WIDGET_H_

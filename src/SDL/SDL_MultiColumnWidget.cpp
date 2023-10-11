/**
  * @file   SDL_MultiColumnWidget.cpp
  * @author 0And1Story
  * @date   2023-10-11
  * @brief  
  */

#include "SDL_MultiColumnWidget.h"

SDL_MultiColumnWidget::SDL_MultiColumnWidget():
        _widgets(), _rect(0, 0, settings.window.width, settings.window.height) {}

SDL_MultiColumnWidget::SDL_MultiColumnWidget(const int& x_, const int& y_):
        _widgets(), _rect(x_, y_, settings.window.width, settings.window.height) {}

SDL_MultiColumnWidget::SDL_MultiColumnWidget(const int& x_, const int& y_, const int& w_, const int& h_):
        _widgets(), _rect(x_, y_, w_, h_) {}

SDL_MultiColumnWidget::~SDL_MultiColumnWidget() {
    for (SDL_Widget* widget : _widgets) {
        delete widget;
    }
}

void SDL_MultiColumnWidget::AddWidget(SDL_Widget* widget_) {
    _widgets.push_back(widget_);
    int column_width = _rect.w / (int)_widgets.size();
    int n = 0;
    for (SDL_Widget* widget : _widgets) {
        SDL_Rect widget_rect = widget->GetRect();
        widget->SetPosition(n * column_width + column_width / 2 - widget_rect.w / 2, _rect.h - widget_rect.h);
        ++n;
    }
}

void SDL_MultiColumnWidget::SetPosition(const int& x_, const int& y_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _rect.x + x_, prev_position.y - _rect.y + y_);
    }
    _rect.x = x_;
    _rect.y = y_;
}

void SDL_MultiColumnWidget::SetPosition(const SDL_Point& position_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _rect.x + position_.x, prev_position.y - _rect.y + position_.y);
    }
    _rect.x = position_.x;
    _rect.y = position_.y;
}

SDL_Point SDL_MultiColumnWidget::GetPosition() const {
    return SDL_Point{ _rect.x, _rect.y };
}

SDL_Rect SDL_MultiColumnWidget::GetRect() const {
    return _rect;
}

int SDL_MultiColumnWidget::EventHandler(const SDL_Event& event_) {
    int handle_num = 0;
    for (SDL_Widget* widget : _widgets) {
        auto interactive_widget = dynamic_cast<SDL_InteractiveWidget*>(widget);
        if (interactive_widget == nullptr) continue;
        handle_num += interactive_widget->EventHandler(event_);
    }
    return handle_num;
}

void SDL_MultiColumnWidget::Render() {
    for (SDL_Widget* widget : _widgets) {
        widget->Render();
    }
}

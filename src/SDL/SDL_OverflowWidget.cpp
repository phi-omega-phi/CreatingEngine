/**
  * @file   SDL_OverflowWidget.cpp
  * @author 0And1Story
  * @date   2023-10-06
  * @brief  
  */

#include "SDL_OverflowWidget.h"

SDL_OverflowWidget::SDL_OverflowWidget(): _widgets(), _position() {}

SDL_OverflowWidget::SDL_OverflowWidget(const int& x_, const int& y_): _widgets(), _position(x_, y_) {}

SDL_OverflowWidget::SDL_OverflowWidget(const int& x_, const int& y_, const int& line_space_): _widgets(), _position(x_, y_), _line_space(line_space_) {}

SDL_OverflowWidget::~SDL_OverflowWidget() {
    for (SDL_Widget* widget : _widgets) {
        delete widget;
    }
}

void SDL_OverflowWidget::AddWidget(SDL_Widget* widget_) {
    if (widget_ == nullptr) return;
    if (_widgets.empty()) {
        widget_->SetPosition(_position.x, _position.y);
        _widgets.push_back(widget_);
        return;
    }
    SDL_Rect last_rect = (*::std::prev(_widgets.end()))->GetRect();
    widget_->SetPosition(_position.x, last_rect.y + last_rect.h + _line_space);
    _widgets.push_back(widget_);
}

void SDL_OverflowWidget::PushBack(SDL_Widget* widget_) {
    if (widget_ == nullptr) return;
    if (_widgets.empty()) {
        widget_->SetPosition(_position.x, _position.y);
        _widgets.push_back(widget_);
        return;
    }
    SDL_Rect last_rect = (*::std::prev(_widgets.end()))->GetRect();
    widget_->SetPosition(_position.x, last_rect.y + last_rect.h + _line_space);
    _widgets.push_back(widget_);
}

void SDL_OverflowWidget::PopBack(SDL_Widget* widget_) {
    _widgets.pop_back();
}

void SDL_OverflowWidget::Clear() {
    for (SDL_Widget* widget : _widgets) {
        delete widget;
    }
    _widgets.clear();
}

bool SDL_OverflowWidget::Empty() const {
    return _widgets.empty();
}

void SDL_OverflowWidget::SetPosition(const int& x_, const int& y_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _position.x + x_, prev_position.y - _position.y + y_);
    }
    _position.x = x_;
    _position.y = y_;
}

void SDL_OverflowWidget::SetPosition(const SDL_Point& position_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _position.x + position_.x, prev_position.y - _position.y + position_.y);
    }
    _position = position_;
}

SDL_Point SDL_OverflowWidget::GetPosition() const {
    return _position;
}

SDL_Rect SDL_OverflowWidget::GetRect() const {
    if (_widgets.empty()) return { _position.x, _position.y, 0, 0 };
    SDL_Rect last_rect = (*::std::prev(_widgets.end()))->GetRect();
    return { _position.x, _position.y, last_rect.w, last_rect.y + last_rect.h - _position.y };
}

int SDL_OverflowWidget::EventHandler(const SDL_Event& event_) {
    int handle_num = 0;
    for (SDL_Widget* widget : _widgets) {
        auto interactive_widget = dynamic_cast<SDL_InteractiveWidget*>(widget);
        if (interactive_widget == nullptr) continue;
        handle_num += interactive_widget->EventHandler(event_);
    }
    return handle_num;
}

void SDL_OverflowWidget::Render() {
    for (SDL_Widget* widget : _widgets) {
        widget->Render();
    }
}

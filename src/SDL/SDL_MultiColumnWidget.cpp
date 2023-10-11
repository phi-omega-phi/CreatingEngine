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
    for (ListType& widget : _widgets) {
        delete widget.widget;
    }
}

void SDL_MultiColumnWidget::AddWidget(const ::std::string& name_, SDL_Widget* widget_) {
    auto it = ::std::find_if(_widgets.begin(), _widgets.end(), [&name_](ListType& x)->bool { return x.name == name_; });
    if (it != _widgets.end()) {
        delete it->widget;
        it->widget = widget_;

        int n = (int)::std::distance(_widgets.begin(), it);
        int column_width = _rect.w / (int)_widgets.size();
        SDL_Rect widget_rect = it->widget->GetRect();

        it->widget->SetPosition(n * column_width + column_width / 2 - widget_rect.w / 2, _rect.h - widget_rect.h);
        return;
    }
    _widgets.push_back({ name_, widget_ });
    int column_width = _rect.w / (int)_widgets.size();
    int n = 0;
    for (ListType& widget : _widgets) {
        SDL_Rect widget_rect = widget.widget->GetRect();
        widget.widget->SetPosition(n * column_width + column_width / 2 - widget_rect.w / 2, _rect.h - widget_rect.h);
        ++n;
    }
}

void SDL_MultiColumnWidget::RemoveWidget(const ::std::string& name_) {
    ::std::erase_if(_widgets, [&name_](ListType& x)->bool { return x.name == name_; });
    if (_widgets.empty()) return;
    int column_width = _rect.w / (int)_widgets.size();
    int n = 0;
    for (ListType& widget : _widgets) {
        SDL_Rect widget_rect = widget.widget->GetRect();
        widget.widget->SetPosition(n * column_width + column_width / 2 - widget_rect.w / 2, _rect.h - widget_rect.h);
        ++n;
    }
}

void SDL_MultiColumnWidget::SetPosition(const int& x_, const int& y_) {
    for (ListType& widget : _widgets) {
        SDL_Point prev_position = widget.widget->GetPosition();
        widget.widget->SetPosition(prev_position.x - _rect.x + x_, prev_position.y - _rect.y + y_);
    }
    _rect.x = x_;
    _rect.y = y_;
}

void SDL_MultiColumnWidget::SetPosition(const SDL_Point& position_) {
    for (ListType& widget : _widgets) {
        SDL_Point prev_position = widget.widget->GetPosition();
        widget.widget->SetPosition(prev_position.x - _rect.x + position_.x, prev_position.y - _rect.y + position_.y);
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
    for (ListType& widget : _widgets) {
        auto interactive_widget = dynamic_cast<SDL_InteractiveWidget*>(widget.widget);
        if (interactive_widget == nullptr) continue;
        handle_num += interactive_widget->EventHandler(event_);
    }
    return handle_num;
}

void SDL_MultiColumnWidget::Render() {
    for (ListType& widget : _widgets) {
        widget.widget->Render();
    }
}

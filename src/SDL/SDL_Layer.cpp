/**
  * @file   SDL_Layer.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "SDL_Layer.h"

SDL_Layer::SDL_Layer(): _widgets(), _position() {}

SDL_Layer::SDL_Layer(const int& x_, const int& y_): _widgets(), _position(x_, y_) {}

SDL_Layer::~SDL_Layer() {
    for (SDL_Widget* widget : _widgets) {
        delete widget;
    }
}

void SDL_Layer::AddWidget(SDL_Widget* widget_) {
    if (widget_ == nullptr) return;
    SDL_Point widget_pos_ = widget_->GetPosition();
    widget_->SetPosition(widget_pos_.x + _position.x, widget_pos_.y + _position.y);
    _widgets.push_back(widget_);
}

void SDL_Layer::PushBack(SDL_Widget* widget_) {
    SDL_Point widget_pos_ = widget_->GetPosition();
    widget_->SetPosition(widget_pos_.x + _position.x, widget_pos_.y + _position.y);
    _widgets.push_back(widget_);
}

void SDL_Layer::PushFront(SDL_Widget* widget_) {
    SDL_Point widget_pos_ = widget_->GetPosition();
    widget_->SetPosition(widget_pos_.x + _position.x, widget_pos_.y + _position.y);
    _widgets.push_front(widget_);
}

void SDL_Layer::PopBack() {
    _widgets.pop_back();
}

void SDL_Layer::PopFront() {
    _widgets.pop_front();
}

void SDL_Layer::Replace(SDL_Widget* old_widget_, SDL_Widget* new_widget_) {
    ::std::replace(_widgets.begin(), _widgets.end(), old_widget_, new_widget_);
}
void SDL_Layer::ReplaceRecursive(SDL_Widget* old_widget_, SDL_Widget* new_widget_) {
    for (auto& widget : _widgets) {
        if (widget == old_widget_) widget = new_widget_;
        auto layer_widget = dynamic_cast<SDL_Layer*>(widget);
        if (layer_widget != nullptr) layer_widget->ReplaceRecursive(old_widget_, new_widget_);
    }
}

void SDL_Layer::SetPosition(const int& x_, const int& y_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _position.x + x_, prev_position.y - _position.y + y_);
    }
    _position.x = x_;
    _position.y = y_;
}

void SDL_Layer::SetPosition(const SDL_Point& position_) {
    for (SDL_Widget* widget : _widgets) {
        SDL_Point prev_position = widget->GetPosition();
        widget->SetPosition(prev_position.x - _position.x + position_.x, prev_position.y - _position.y + position_.y);
    }
    _position = position_;
}

[[nodiscard]] SDL_Point SDL_Layer::GetPosition() const {
    return _position;
}

void SDL_Layer::EventHandler(const SDL_Event& event_) {
    for (SDL_Widget* widget : _widgets) {
        auto interactive_widget = dynamic_cast<SDL_InteractiveWidget*>(widget);
        if (interactive_widget == nullptr) continue;
        interactive_widget->EventHandler(event_);
    }
}

void SDL_Layer::Render() {
    for (SDL_Widget* widget : _widgets) {
        widget->Render();
    }
}

SDL_Layer* SDL_Layer::CreateLayerFromXML(const DOM::Node& node) {
    auto layer = new SDL_Layer;
    for (auto& child: node.childNodes) {
        layer->AddWidget(CreateWidgetFromXML(child));
    }
    return layer;
}

SDL_Widget* SDL_Layer::CreateWidgetFromXML(const DOM::Node& node) {
    if (node.tagName == "layer") {
        return SDL_Layer::CreateLayerFromXML(node);
    } else if (node.tagName == "texture") {
        return SDL_TextureEx::CreateTextureFromXML(node);
    } else if (node.tagName == "button") {
        return SDL_Button::CreateButtonFromXML(node);
    }
    return nullptr;
}

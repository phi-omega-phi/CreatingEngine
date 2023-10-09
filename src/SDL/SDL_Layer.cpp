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

SDL_Widget** SDL_Layer::AddWidget(SDL_Widget* widget_) {
    if (widget_ == nullptr) return {};
    SDL_Point widget_pos_ = widget_->GetPosition();
    widget_->SetPosition(widget_pos_.x + _position.x, widget_pos_.y + _position.y);
    _widgets.push_back(widget_);
    return &*::std::prev(_widgets.end());
}

SDL_Widget** SDL_Layer::PushBack(SDL_Widget* widget_) {
    if (widget_ == nullptr) {
        _widgets.push_back(widget_);
        return &*::std::prev(_widgets.end());
    }
    SDL_Point widget_pos_ = widget_->GetPosition();
    widget_->SetPosition(widget_pos_.x + _position.x, widget_pos_.y + _position.y);
    _widgets.push_back(widget_);
    return &*::std::prev(_widgets.end());
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

SDL_Widget*& SDL_Layer::GetWidgetByIndex(size_t index) {
    auto it = _widgets.begin();
    ::std::advance(it, index);
    return *it;
}

SDL_Widget*& SDL_Layer::operator[](size_t index) {
    auto it = _widgets.begin();
    ::std::advance(it, index);
    return *it;
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

[[nodiscard]] SDL_Rect SDL_Layer::GetRect() const {
    return { _position.x, _position.y, 0, 0 };
}

void SDL_Layer::Bind(CALLBACK_FUNC DefaultCallBack_, void* default_param_) {
    _DefaultCallback = DefaultCallBack_;
    _default_param = default_param_;
}

int SDL_Layer::EventHandler(const SDL_Event& event_) {
    int handle_num = 0;
    for (SDL_Widget* widget : _widgets) {
        auto interactive_widget = dynamic_cast<SDL_InteractiveWidget*>(widget);
        if (interactive_widget == nullptr) continue;
        handle_num += interactive_widget->EventHandler(event_);
    }
    if (handle_num == 0 && _DefaultCallback != nullptr && event_.type == SDL_MOUSEBUTTONUP) {
        _DefaultCallback(_default_param);
        ++handle_num;
    }
    return handle_num;
}

void SDL_Layer::Render() {
    for (SDL_Widget* widget : _widgets) {
        if (widget != nullptr) widget->Render();
    }
}

SDL_Layer* SDL_Layer::CreateLayerFromXML(const DOM::Node& node) {
    auto layer = new SDL_Layer;
    if (NodeAttrContains(x) && NodeAttrContains(y)) layer->SetPosition(NodeAttrInt(x), NodeAttrInt(y));
    if (NodeAttrContains(default)) {
        if (NodeAttrContains(param)) {
            char* param = new char[node.attributes.at("param").size()];
            strcpy(param, NodeAttr(param));
            layer->Bind(Preset_Callback.at(NodeAttr(default)), (void*)param);
        } else {
            layer->Bind(Preset_Callback.at(NodeAttr(default)), nullptr);
        }
    }
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
    } else if (node.tagName == "text") {
        if (NodeAttrContains(wrap)) return SDL_TextBox::CreateTextBoxFromXML(node);
        else return SDL_Text::CreateTextFromXML(node);
    } else if (node.tagName == "text_button") {
        return SDL_TextButton::CreateTextButtonFromXML(node);
    } else if (node.tagName == "animation") {
        return SDL_Animation::CreateAnimationFromXML(node);
    }
    return nullptr;
}

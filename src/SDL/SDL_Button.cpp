/**
  * @file   SDL_Button.cpp
  * @author 0And1Story
  * @date   2023-09-22
  * @brief  
  */
#include "SDL_Button.h"

const ::std::unordered_map<::std::string, CALLBACK_FUNC> OnClick_Preset_Func {
        {"log", [](void* log_str) {
            SDL_FileInfo((const char*)log_str);
        }},
        {"quit", [](void* none) {
            global.is_quit = true;
        }},
        {"current_layer", [](void* layer) {
            global.current_layer = (SDL_Layer*)layer;
        }}
};

SDL_Button::SDL_Button(const char* texture_path_, const char* texture_hover_path_, const char* texture_click_path_, CALLBACK_FUNC OnClick_, void* click_param_):
        _texture(new SDL_TextureEx(texture_path_)),
        _texture_hover(new SDL_TextureEx(texture_hover_path_)),
        _texture_click(new SDL_TextureEx(texture_click_path_)),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_Button::SDL_Button(const char* texture_path_, const char* texture_hover_path_, const char* texture_click_path_, const int& x_, const int& y_, CALLBACK_FUNC OnClick_, void* click_param_):
        _texture(new SDL_TextureEx(texture_path_, x_, y_)),
        _texture_hover(new SDL_TextureEx(texture_hover_path_, x_, y_)),
        _texture_click(new SDL_TextureEx(texture_click_path_, x_, y_)),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_Button::SDL_Button(SDL_ResourceID texture_id, SDL_ResourceID texture_hover_id, SDL_ResourceID texture_click_id, CALLBACK_FUNC OnClick_, void* click_param_):
        _texture(new SDL_TextureEx(texture_id)),
        _texture_hover(new SDL_TextureEx(texture_hover_id)),
        _texture_click(new SDL_TextureEx(texture_click_id)),
        _OnClick(OnClick_),
        _click_param(click_param_) {}


SDL_Button::SDL_Button(SDL_ResourceID texture_id, SDL_ResourceID texture_hover_id, SDL_ResourceID texture_click_id, const int& x_, const int& y_, CALLBACK_FUNC OnClick_, void* click_param_):
        _texture(new SDL_TextureEx(texture_id, x_, y_)),
        _texture_hover(new SDL_TextureEx(texture_hover_id, x_, y_)),
        _texture_click(new SDL_TextureEx(texture_click_id, x_, y_)),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_Button::SDL_Button(SDL_TextureEx* texture_, SDL_TextureEx* texture_hover_, SDL_TextureEx* texture_click_, CALLBACK_FUNC OnClick_, void* click_param_):
        _texture(texture_),
        _texture_hover(texture_hover_),
        _texture_click(texture_click_),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_Button::~SDL_Button() {
    delete _texture;
    delete _texture_hover;
    delete _texture_click;
}

void SDL_Button::Click() {
    if (_OnClick != nullptr) _OnClick(_click_param);
}

void SDL_Button::Bind(CALLBACK_FUNC OnClick_) {
    _OnClick = OnClick_;
}

void SDL_Button::SetPosition(const int& x_, const int& y_) {
    _texture->SetPosition(x_, y_);
    _texture_hover->SetPosition(x_, y_);
    _texture_click->SetPosition(x_, y_);
}

void SDL_Button::SetPosition(const SDL_Point& position_) {
    _texture->SetPosition(position_);
    _texture_hover->SetPosition(position_);
    _texture_click->SetPosition(position_);
}

[[nodiscard]] SDL_Point SDL_Button::GetPosition() const {
    return _texture->GetPosition();
}

[[nodiscard]] bool SDL_Button::IsRect(const int& x_, const int& y_) const {
    SDL_Rect rect_ = _texture->GetRect() * settings.window.scale;
    return x_ >= rect_.x && y_ >= rect_.y && x_ < rect_.x + rect_.w && y_ < rect_.y + rect_.h;
}

int SDL_Button::EventHandler(const SDL_Event& event_) {
    if (!IsRect(event_.motion.x, event_.motion.y)) {
        _status = ButtonStatus::NORMAL;
        return 0;
    }
    switch (event_.type) {
        case SDL_MOUSEBUTTONDOWN:
            _status = ButtonStatus::CLICK;
            break;

        case SDL_MOUSEBUTTONUP:
            Click();

        default:
            if (event_.button.state == SDL_RELEASED) {
                _status = ButtonStatus::HOVER;
            }
            break;
    }
    return 1;
}

void SDL_Button::Render() {
    switch (_status) {
        using enum ButtonStatus;
        case NORMAL:
            _texture->Render();
            break;

        case HOVER:
            _texture_hover->Render();
            break;

        case CLICK:
            _texture_click->Render();
            break;

        default:
            break;
    }
}

SDL_Button* SDL_Button::CreateButtonFromXML(const DOM::Node& node) {
    CALLBACK_FUNC OnClick = nullptr;
    void* click_param = nullptr;
    if (node.attributes.contains("onclick") && OnClick_Preset_Func.contains(node.attributes.at("onclick"))) {
        OnClick = OnClick_Preset_Func.at(node.attributes.at("onclick"));
        if (node.attributes.contains("param")) {
            char* param = new char[node.attributes.at("param").size() + 1];
            strcpy(param, node.attributes.at("param").c_str());
            param[node.attributes.at("param").size()] = '\0';
            click_param = (void*)param;
        }
    }
    if (node.attributes.contains("normal_id") && node.attributes.contains("hover_id") && node.attributes.contains("click_id")) {
        if (node.attributes.contains("x") && node.attributes.contains("y")) {
            return new SDL_Button(atoi(node.attributes.at("normal_id").c_str()),
                                  atoi(node.attributes.at("hover_id").c_str()),
                                  atoi(node.attributes.at("click_id").c_str()),
                                  atoi(node.attributes.at("x").c_str()),
                                  atoi(node.attributes.at("y").c_str()),
                                  OnClick,
                                  click_param);
        }
        return new SDL_Button(atoi(node.attributes.at("normal_id").c_str()),
                              atoi(node.attributes.at("hover_id").c_str()),
                              atoi(node.attributes.at("click_id").c_str()),
                              OnClick,
                              click_param);
    } else if (node.attributes.contains("normal_path") && node.attributes.contains("hover_path") && node.attributes.contains("click_path")) {
        if (node.attributes.contains("x") && node.attributes.contains("y")) {
            return new SDL_Button(node.attributes.at("normal_path").c_str(),
                                  node.attributes.at("hover_path").c_str(),
                                  node.attributes.at("click_path").c_str(),
                                  atoi(node.attributes.at("x").c_str()),
                                  atoi(node.attributes.at("y").c_str()),
                                  OnClick,
                                  click_param);
        }
        return new SDL_Button(node.attributes.at("normal_path").c_str(),
                              node.attributes.at("hover_path").c_str(),
                              node.attributes.at("click_path").c_str(),
                              OnClick,
                              click_param);
    }
    return nullptr;
}



SDL_TextButton::SDL_TextButton(SDL_Text *text_, SDL_Text *text_hover_, SDL_Text *text_click_, CALLBACK_FUNC OnClick_, void *click_param_):
        _text(text_),
        _text_hover(text_hover_),
        _text_click(text_click_),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_TextButton::SDL_TextButton(SDL_Text *text_, SDL_Text *text_hover_, SDL_Text *text_click_, const int &x_, const int &y_, CALLBACK_FUNC OnClick_, void *click_param_):
        _text(text_),
        _text_hover(text_hover_),
        _text_click(text_click_),
        _OnClick(OnClick_),
        _click_param(click_param_) {
    _text->SetPosition(x_, y_);
    _text_hover->SetPosition(x_, y_);
    _text_click->SetPosition(x_, y_);
}

SDL_TextButton::SDL_TextButton(TTF_Font* font, const char* text, int pt_size, SDL_Color fg, SDL_Color fg_hover, SDL_Color fg_click, const int& x_, const int& y_, CALLBACK_FUNC OnClick_, void* click_param_):
        _text(new SDL_Text(font, text, pt_size, fg, x_, y_)),
        _text_hover(new SDL_Text(font, text, pt_size, fg_hover, x_, y_)),
        _text_click(new SDL_Text(font, text, pt_size, fg_click, x_, y_)),
        _OnClick(OnClick_),
        _click_param(click_param_) {}

SDL_TextButton::~SDL_TextButton() {
    delete _text;
    delete _text_hover;
    delete _text_click;
}

void SDL_TextButton::Click() {
    if (_OnClick != nullptr) _OnClick(_click_param);
}

void SDL_TextButton::Bind(CALLBACK_FUNC OnClick_) {
    _OnClick = OnClick_;
}

void SDL_TextButton::SetPosition(const int& x_, const int& y_) {
    _text->SetPosition(x_, y_);
    _text_hover->SetPosition(x_, y_);
    _text_click->SetPosition(x_, y_);
}

void SDL_TextButton::SetPosition(const SDL_Point& position_) {
    _text->SetPosition(position_);
    _text_hover->SetPosition(position_);
    _text_click->SetPosition(position_);
}

[[nodiscard]] SDL_Point SDL_TextButton::GetPosition() const {
    return _text->GetPosition();
}

[[nodiscard]] bool SDL_TextButton::IsRect(const int& x_, const int& y_) const {
    SDL_Rect rect_ = _text->GetRect() * settings.window.scale;
    return x_ >= rect_.x && y_ >= rect_.y && x_ < rect_.x + rect_.w && y_ < rect_.y + rect_.h;
}

int SDL_TextButton::EventHandler(const SDL_Event& event_) {
    if (!IsRect(event_.motion.x, event_.motion.y)) {
        _status = ButtonStatus::NORMAL;
        return 0;
    }
    switch (event_.type) {
        case SDL_MOUSEBUTTONDOWN:
            _status = ButtonStatus::CLICK;
            break;

        case SDL_MOUSEBUTTONUP:
            Click();

        default:
            if (event_.button.state == SDL_RELEASED) {
                _status = ButtonStatus::HOVER;
            }
            break;
    }
    return 1;
}

void SDL_TextButton::Render() {
    switch (_status) {
        using enum ButtonStatus;
        case NORMAL:
            _text->Render();
            break;

        case HOVER:
            _text_hover->Render();
            break;

        case CLICK:
            _text_click->Render();
            break;

        default:
            break;
    }
}

SDL_TextButton* SDL_TextButton::CreateButtonFromXML(const DOM::Node& node) {
    return nullptr;
}

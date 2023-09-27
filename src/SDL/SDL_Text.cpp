/**
  * @file   SDL_Text.cpp
  * @author 0And1Story
  * @date   2023-09-26
  * @brief  
  */

#include "SDL_Text.h"

SDL_Text::SDL_Text(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, fg_color);
    _texture = new SDL_TextureEx(surface);
    SDL_FreeSurface(surface);
}

SDL_Text::SDL_Text(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color, const int &x_, const int &y_) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, fg_color);
    _texture = new SDL_TextureEx(surface, x_, y_);
    SDL_FreeSurface(surface);
}

SDL_Text::SDL_Text(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color, const int &x_, const int &y_, const int &w_, const int &h_) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, fg_color);
    _texture = new SDL_TextureEx(surface, x_, y_, w_, h_);
    SDL_FreeSurface(surface);
}

SDL_Text::~SDL_Text() {
    delete _texture;
}

void SDL_Text::SetRect(const SDL_Rect& rect_) {
    _rect = rect_;
    _rect *= settings.window.scale;
}

void SDL_Text::SetRect(const int& x_, const int& y_, const int& w_, const int& h_) {
    _rect.x = x_;
    _rect.y = y_;
    _rect.w = w_;
    _rect.h = h_;
    _rect *= settings.window.scale;
}

[[nodiscard]] SDL_Rect SDL_Text::GetRect() const {
    return _rect / settings.window.scale;
}

[[nodiscard]] SDL_Rect SDL_Text::GetRenderRect() const {
    return _rect;
}

void SDL_Text::SetPosition(const int& x_, const int& y_) {
    _rect.x = (int)(x_ * settings.window.scale);
    _rect.y = (int)(y_ * settings.window.scale);
}

void SDL_Text::SetPosition(const SDL_Point& position_) {
    _rect.x = (int)(position_.x * settings.window.scale);
    _rect.y = (int)(position_.y * settings.window.scale);
}

[[nodiscard]] SDL_Point SDL_Text::GetPosition() const {
    return SDL_Point { (int)(_rect.x / settings.window.scale), (int)(_rect.y / settings.window.scale) };
}

void SDL_Text::SetRenderPosition(const int& x_, const int& y_) {
    _rect.x = x_;
    _rect.y = y_;
}

void SDL_Text::SetRenderPosition(const SDL_Point& position_) {
    _rect.x = position_.x;
    _rect.y = position_.y;
}

[[nodiscard]] SDL_Point SDL_Text::GetRenderPosition() const {
    return SDL_Point { _rect.x, _rect.y };
}

void SDL_Text::SetSize(const int& w_, const int& h_) {
    _rect.w = (int)(w_ * settings.window.scale);
    _rect.h = (int)(h_ * settings.window.scale);
}

SDL_Size SDL_Text::GetSize() {
    return SDL_Size { (int)(_rect.w / settings.window.scale), (int)(_rect.h / settings.window.scale) };
}

void SDL_Text::Render() {
    _texture->Render();
}

SDL_Text* SDL_Text::CreateTextFromXML(const DOM::Node &node) {
    return nullptr;
}

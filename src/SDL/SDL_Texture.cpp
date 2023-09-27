/**
  * @file   SDL_Texture.cpp
  * @author 0And1Story
  * @date   2023-09-22
  * @brief  
  */
#include "SDL_Texture.h"

SDL_TextureEx::SDL_TextureEx(const char* texture_path_): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(SDL_ResourceReader.GetResourceID(texture_path_));
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { 0, 0, surface->w, surface->h };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(const char* texture_path_, const int& x_, const int& y_): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(SDL_ResourceReader.GetResourceID(texture_path_));
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { x_, y_, surface->w, surface->h };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(const char* texture_path_, const int& x_, const int& y_, const int& w_, const int& h_): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(SDL_ResourceReader.GetResourceID(texture_path_));
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { x_, y_, w_, h_ };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(SDL_ResourceID texture_id): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(texture_id);
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { 0, 0, surface->w, surface->h };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(SDL_ResourceID texture_id, const int& x_, const int& y_): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(texture_id);
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { x_, y_, surface->w, surface->h };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(SDL_ResourceID texture_id, const int& x_, const int& y_, const int& w_, const int& h_): _rect() {
    SDL_Surface* surface = SDL_ResourceReader.LoadImage(texture_id);
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface);
    _rect = { x_, y_, w_, h_ };
    SDL_FreeSurface(surface);
}

SDL_TextureEx::SDL_TextureEx(SDL_Texture* texture_): _rect() {
    int w_, h_;
    SDL_QueryTexture(texture_, nullptr, nullptr, &w_, &h_);
    _rect = { 0, 0,  w_, h_};
    _texture = texture_;
}

SDL_TextureEx::SDL_TextureEx(SDL_Texture* texture_, const int& x_, const int& y_): _rect() {
    int w_, h_;
    SDL_QueryTexture(texture_, nullptr, nullptr, &w_, &h_);
    _rect = { x_, y_,  w_, h_};
    _texture = texture_;
}

SDL_TextureEx::SDL_TextureEx(SDL_Texture* texture_, const int& x_, const int& y_, const int& w_, const int& h_): _rect() {
    _rect = { x_, y_,  w_, h_};
    _texture = texture_;
}

SDL_TextureEx::SDL_TextureEx(SDL_Surface* surface_): _rect() {
    _rect = { 0, 0,  surface_->w, surface_->h};
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface_);
}

SDL_TextureEx::SDL_TextureEx(SDL_Surface* surface_, const int& x_, const int& y_): _rect() {
    _rect = { x_, y_,  surface_->w, surface_->h};
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface_);
}

SDL_TextureEx::SDL_TextureEx(SDL_Surface* surface_, const int& x_, const int& y_, const int& w_, const int& h_): _rect() {
    _rect = { x_, y_,  w_, h_};
    _texture = SDL_CreateTextureFromSurface(settings.renderer, surface_);
}

SDL_TextureEx::~SDL_TextureEx() {
    SDL_DestroyTexture(_texture);
}

void SDL_TextureEx::SetRect(const SDL_Rect& rect_) {
    _rect = rect_;
}

void SDL_TextureEx::SetRect(const int& x_, const int& y_, const int& w_, const int& h_) {
    _rect.x = x_;
    _rect.y = y_;
    _rect.w = w_;
    _rect.h = h_;
}

[[nodiscard]] SDL_Rect SDL_TextureEx::GetRect() const {
    return _rect;
}

void SDL_TextureEx::SetPosition(const int& x_, const int& y_) {
    _rect.x = x_;
    _rect.y = y_;
}

void SDL_TextureEx::SetPosition(const SDL_Point& position_) {
    _rect.x = position_.x;
    _rect.y = position_.y;
}

[[nodiscard]] SDL_Point SDL_TextureEx::GetPosition() const {
    return SDL_Point { _rect.x, _rect.y };
}

void SDL_TextureEx::SetSize(const int& w_, const int& h_) {
    _rect.w = w_;
    _rect.h = h_;
}

SDL_Size SDL_TextureEx::GetSize() {
    return SDL_Size { _rect.w, _rect.h };
}

[[nodiscard]] int SDL_TextureEx::GetX() const { return _rect.x; }
[[nodiscard]] int SDL_TextureEx::GetY() const { return _rect.y; }
[[nodiscard]] int SDL_TextureEx::GetW() const { return _rect.w; }
[[nodiscard]] int SDL_TextureEx::GetH() const { return _rect.h; }

void SDL_TextureEx::Render() {
    SDL_RenderCopy(settings.renderer, _texture, nullptr, &_rect);
}

SDL_TextureEx* SDL_TextureEx::CreateTextureFromXML(const DOM::Node& node) {
    if (node.attributes.contains("id")) {
        if (node.attributes.contains("x") && node.attributes.contains("y")) {
            if (node.attributes.contains("w") && node.attributes.contains("h")) {
                return new SDL_TextureEx(atoi(node.attributes.at("id").c_str()),
                                         atoi(node.attributes.at("x").c_str()),
                                         atoi(node.attributes.at("y").c_str()),
                                         atoi(node.attributes.at("w").c_str()),
                                         atoi(node.attributes.at("h").c_str()));
            }
            return new SDL_TextureEx(atoi(node.attributes.at("id").c_str()),
                                     atoi(node.attributes.at("x").c_str()),
                                     atoi(node.attributes.at("y").c_str()));
        }
        return new SDL_TextureEx(atoi(node.attributes.at("id").c_str()));
    } else if (node.attributes.contains("path")) {
        if (node.attributes.contains("x") && node.attributes.contains("y")) {
            if (node.attributes.contains("w") && node.attributes.contains("h")) {
                return new SDL_TextureEx(node.attributes.at("path").c_str(),
                                         atoi(node.attributes.at("x").c_str()),
                                         atoi(node.attributes.at("y").c_str()),
                                         atoi(node.attributes.at("w").c_str()),
                                         atoi(node.attributes.at("h").c_str()));
            }
            return new SDL_TextureEx(node.attributes.at("path").c_str(),
                                     atoi(node.attributes.at("x").c_str()),
                                     atoi(node.attributes.at("y").c_str()));
        }
        return new SDL_TextureEx(node.attributes.at("path").c_str());
    }
    return nullptr;
}

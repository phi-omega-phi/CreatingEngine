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
    _texture->SetRect(rect_);
}

void SDL_Text::SetRect(const int& x_, const int& y_, const int& w_, const int& h_) {
    _texture->SetRect(x_, y_, w_, h_);
}

[[nodiscard]] SDL_Rect SDL_Text::GetRect() const {
    return _texture->GetRect();
}

void SDL_Text::SetPosition(const int& x_, const int& y_) {
    _texture->SetPosition(x_, y_);
}

void SDL_Text::SetPosition(const SDL_Point& position_) {
    _texture->SetPosition(position_);
}

[[nodiscard]] SDL_Point SDL_Text::GetPosition() const {
    return _texture->GetPosition();
}

void SDL_Text::SetSize(const int& w_, const int& h_) {
    _texture->SetSize(w_, h_);
}

SDL_Size SDL_Text::GetSize() {
    return _texture->GetSize();
}

void SDL_Text::Render() {
    _texture->Render();
}

SDL_Text* SDL_Text::CreateTextFromXML(const DOM::Node &node) {
    if (NodeAttrContains(font_id) && NodeAttrContains(content) && NodeAttrContains(pt) && NodeAttrContains(fg)) {
        if (NodeAttrContains(x) && NodeAttrContains(y)) {
            if (NodeAttrContains(w) && NodeAttrContains(h)) {
                return new SDL_Text(global.LoadFont(NodeAttrInt(font_id)),
                                    NodeAttr(content),
                                    NodeAttrInt(pt),
                                    NodeAttrColor(fg),
                                    NodeAttrInt(x),
                                    NodeAttrInt(y),
                                    NodeAttrInt(w),
                                    NodeAttrInt(h));
            }
            return new SDL_Text(global.LoadFont(NodeAttrInt(font_id)),
                                NodeAttr(content),
                                NodeAttrInt(pt),
                                NodeAttrColor(fg),
                                NodeAttrInt(x),
                                NodeAttrInt(y));
        }
        return new SDL_Text(global.LoadFont(NodeAttrInt(font_id)),
                            NodeAttr(content),
                            NodeAttrInt(pt),
                            NodeAttrColor(fg));
    } else if (NodeAttrContains(font_path) && NodeAttrContains(content) && NodeAttrContains(pt) && NodeAttrContains(fg)) {
        if (NodeAttrContains(x) && NodeAttrContains(y)) {
            if (NodeAttrContains(w) && NodeAttrContains(h)) {
                return new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                                    NodeAttr(content),
                                    NodeAttrInt(pt),
                                    NodeAttrColor(fg),
                                    NodeAttrInt(x),
                                    NodeAttrInt(y),
                                    NodeAttrInt(w),
                                    NodeAttrInt(h));
            }
            return new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                                NodeAttr(content),
                                NodeAttrInt(pt),
                                NodeAttrColor(fg),
                                NodeAttrInt(x),
                                NodeAttrInt(y));
        }
        return new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                            NodeAttr(content),
                            NodeAttrInt(pt),
                            NodeAttrColor(fg));
    }
    return nullptr;
}



SDL_TextBox::SDL_TextBox(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color, Uint32 wrap_length) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, fg_color, wrap_length);
    _texture = new SDL_TextureEx(surface);
    SDL_FreeSurface(surface);
}

SDL_TextBox::SDL_TextBox(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color, Uint32 wrap_length, const int &x_, const int &y_) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, fg_color, wrap_length);
    _texture = new SDL_TextureEx(surface, x_, y_);
    SDL_FreeSurface(surface);
}

SDL_TextBox::SDL_TextBox(TTF_Font *font, const char *text, int pt_size, SDL_Color fg_color, Uint32 wrap_length, const int &x_, const int &y_, const int &w_, const int &h_) {
    TTF_SetFontSize(font, pt_size);
    SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, text, fg_color, wrap_length);
    _texture = new SDL_TextureEx(surface, x_, y_, w_, h_);
    SDL_FreeSurface(surface);
}

SDL_TextBox::~SDL_TextBox() {
    delete _texture;
}

void SDL_TextBox::SetRect(const SDL_Rect& rect_) {
    _texture->SetRect(rect_);
}

void SDL_TextBox::SetRect(const int& x_, const int& y_, const int& w_, const int& h_) {
    _texture->SetRect(x_, y_, w_, h_);
}

[[nodiscard]] SDL_Rect SDL_TextBox::GetRect() const {
    return _texture->GetRect();
}

void SDL_TextBox::SetPosition(const int& x_, const int& y_) {
    _texture->SetPosition(x_, y_);
}

void SDL_TextBox::SetPosition(const SDL_Point& position_) {
    _texture->SetPosition(position_);
}

[[nodiscard]] SDL_Point SDL_TextBox::GetPosition() const {
    return _texture->GetPosition();
}

void SDL_TextBox::SetSize(const int& w_, const int& h_) {
    _texture->SetSize(w_, h_);
}

SDL_Size SDL_TextBox::GetSize() {
    return _texture->GetSize();
}

void SDL_TextBox::Render() {
    _texture->Render();
}

SDL_TextBox* SDL_TextBox::CreateTextBoxFromXML(const DOM::Node &node) {
    if (NodeAttrContains(font_id) && NodeAttrContains(content) && NodeAttrContains(pt) && NodeAttrContains(fg) && NodeAttrContains(wrap)) {
        if (NodeAttrContains(x) && NodeAttrContains(y)) {
            if (NodeAttrContains(w) && NodeAttrContains(h)) {
                return new SDL_TextBox(global.LoadFont(NodeAttrInt(font_id)),
                                    NodeAttr(content),
                                    NodeAttrInt(pt),
                                    NodeAttrColor(fg),
                                    NodeAttrInt(wrap),
                                    NodeAttrInt(x),
                                    NodeAttrInt(y),
                                    NodeAttrInt(w),
                                    NodeAttrInt(h));
            }
            return new SDL_TextBox(global.LoadFont(NodeAttrInt(font_id)),
                                NodeAttr(content),
                                NodeAttrInt(pt),
                                NodeAttrColor(fg),
                                NodeAttrInt(wrap),
                                NodeAttrInt(x),
                                NodeAttrInt(y));
        }
        return new SDL_TextBox(global.LoadFont(NodeAttrInt(font_id)),
                            NodeAttr(content),
                            NodeAttrInt(pt),
                            NodeAttrColor(fg),
                            NodeAttrInt(wrap));
    } else if (NodeAttrContains(font_path) && NodeAttrContains(content) && NodeAttrContains(pt) && NodeAttrContains(fg) && NodeAttrContains(wrap)) {
        if (NodeAttrContains(x) && NodeAttrContains(y)) {
            if (NodeAttrContains(w) && NodeAttrContains(h)) {
                return new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                                       NodeAttr(content),
                                       NodeAttrInt(pt),
                                       NodeAttrColor(fg),
                                       NodeAttrInt(wrap),
                                       NodeAttrInt(x),
                                       NodeAttrInt(y),
                                       NodeAttrInt(w),
                                       NodeAttrInt(h));
            }
            return new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                                   NodeAttr(content),
                                   NodeAttrInt(pt),
                                   NodeAttrColor(fg),
                                   NodeAttrInt(wrap),
                                   NodeAttrInt(x),
                                   NodeAttrInt(y));
        }
        return new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID(NodeAttr(font_path))),
                               NodeAttr(content),
                               NodeAttrInt(pt),
                               NodeAttrColor(fg),
                               NodeAttrInt(wrap));
    }
    return nullptr;
}

/**
  * @file   SDL_Text.h
  * @author 0And1Story
  * @date   2023-09-26
  * @brief  
  */

#ifndef _SDL_TEXT_H_
#define _SDL_TEXT_H_

#include "SDL_ttf.h"
#include "SDL_Widget.h"
#include "SDL_Texture.h"
#include "SDL_Global.h"

class SDL_Text : public SDL_Widget {
private:
    SDL_TextureEx* _texture;

public:
    SDL_Text(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color);
    SDL_Text(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color, const int& x_, const int& y_);
    SDL_Text(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color, const int& x_, const int& y_, const int& w_, const int& h_);

    ~SDL_Text() override;

    void SetRect(const SDL_Rect& rect_);
    void SetRect(const int& x_, const int& y_, const int& w_, const int& h_);
    [[nodiscard]] SDL_Rect GetRect() const override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void SetSize(const int& w_, const int& h_);
    SDL_Size GetSize();

    void Render() override;

    static SDL_Text* CreateTextFromXML(const DOM::Node& node);
};

class SDL_TextBox : public SDL_Widget {
private:
    SDL_TextureEx* _texture;

public:
    SDL_TextBox(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color, Uint32 wrap_length);
    SDL_TextBox(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color, Uint32 wrap_length, const int& x_, const int& y_);
    SDL_TextBox(TTF_Font* font, const char* text, int pt_size, SDL_Color fg_color, Uint32 wrap_length, const int& x_, const int& y_, const int& w_, const int& h_);

    ~SDL_TextBox() override;

    void SetRect(const SDL_Rect& rect_);
    void SetRect(const int& x_, const int& y_, const int& w_, const int& h_);
    [[nodiscard]] SDL_Rect GetRect() const override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void SetSize(const int& w_, const int& h_);
    SDL_Size GetSize();

    void Render() override;

    static SDL_TextBox* CreateTextBoxFromXML(const DOM::Node& node);
};


#endif //_SDL_TEXT_H_

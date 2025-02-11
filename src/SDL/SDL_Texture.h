/**
 * @file    SDL_Texture.h
 * @author  0And1Story
 * @date    2023-7-7
 * @brief   The Extended Texture Module for SDL.
 */

#ifndef _SDL_TEXTURE_H_
#define _SDL_TEXTURE_H_

#include "SDL.h"
#include <utility>
#include "SDL_Const.h"
#include "SDL_Setting.h"
#include "SDL_Widget.h"
#include "SDL_ResourceReader.h"
#include "XML_Parser.h"

#define SDL_CreateTextureEx(...) new SDL_TextureEx(__VA_ARGS__)
#define SDL_DestroyTextureEx(texture) delete texture

/**
 * @brief       The interface of textures.
 * @interface   SDL_TextureInterface
 * @inherit     SDL_Widget
 */
class SDL_TextureInterface : public SDL_Widget {
public:
    virtual void SetRect(const SDL_Rect& rect_) = 0;
    virtual void SetRect(const int& x_, const int& y_, const int& w_, const int& h_) = 0;
    virtual void SetSize(const int& w_, const int& h_) = 0;
    [[nodiscard]] virtual SDL_Size GetSize() = 0;

    [[nodiscard]] virtual int GetX() const = 0;
    [[nodiscard]] virtual int GetY() const = 0;
    [[nodiscard]] virtual int GetW() const = 0;
    [[nodiscard]] virtual int GetH() const = 0;
};

/**
 * @brief   The extended version of SDL_Texture.
 * @class   SDL_TextureEx
 * @inherit SDL_TextureInterface
 */
class SDL_TextureEx : public SDL_TextureInterface {
private:
    SDL_Texture* _texture;          ///< The texture.
    SDL_Rect _rect;                 ///< The layout rectangle of the texture.

public:
    explicit SDL_TextureEx(const char* texture_path_);
    SDL_TextureEx(const char* texture_path_, const int& x_, const int& y_);
    SDL_TextureEx(const char* texture_path_, const int& x_, const int& y_, const int& w_, const int& h_);
    explicit SDL_TextureEx(SDL_ResourceID texture_id);
    SDL_TextureEx(SDL_ResourceID texture_id, const int& x_, const int& y_);
    SDL_TextureEx(SDL_ResourceID texture_id, const int& x_, const int& y_, const int& w_, const int& h_);
    explicit SDL_TextureEx(SDL_Texture* texture_);
    SDL_TextureEx(SDL_Texture* texture_, const int& x_, const int& y_);
    SDL_TextureEx(SDL_Texture* texture_, const int& x_, const int& y_, const int& w_, const int& h_);
    explicit SDL_TextureEx(SDL_Surface* surface_);
    SDL_TextureEx(SDL_Surface* surface_, const int& x_, const int& y_);
    SDL_TextureEx(SDL_Surface* surface_, const int& x_, const int& y_, const int& w_, const int& h_);

    ~SDL_TextureEx() override;

    void SetRect(const SDL_Rect& rect_) override;
    void SetRect(const int& x_, const int& y_, const int& w_, const int& h_) override;
    [[nodiscard]] SDL_Rect GetRect() const override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void SetSize(const int& w_, const int& h_) override;
    SDL_Size GetSize() override;

    [[nodiscard]] int GetX() const override;
    [[nodiscard]] int GetY() const override;
    [[nodiscard]] int GetW() const override;
    [[nodiscard]] int GetH() const override;

    void Render() override;

    static SDL_TextureEx* CreateTextureFromXML(const DOM::Node& node);

    void LoadThumbnail(const char* file_name);
};

#endif //_SDL_TEXTURE_H_

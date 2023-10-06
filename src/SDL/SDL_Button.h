/**
 * @file    SDL_Button.h
 * @author  0And1Story
 * @date    2023-7-6
 * @brief   The Button Module for SDL.
 */

#ifndef _SDL_BUTTON_H_
#define _SDL_BUTTON_H_

#include "SDL.h"
#include "SDL_Const.h"
#include "SDL_Setting.h"
#include "SDL_Widget.h"
#include "SDL_Texture.h"
#include "SDL_Text.h"
#include "SDL_FileLog.h"
#include "XML_Parser.h"
#include <map>
#include <unordered_map>
#include <string>

#define SDL_CreateButton(...) new SDL_Button(__VA_ARGS__)
#define SDL_DestroyButton(button) delete button

/**
 * @brief       The interface of buttons.
 * @interface   SDL_ButtonInterface
 * @inherit     SDL_Widget
 */
class SDL_ButtonInterface : public SDL_InteractiveWidget {
public:
    virtual void Click() = 0;
    virtual void Bind(CALLBACK_FUNC OnClick_, void* click_param_) = 0;
    [[nodiscard]] virtual bool IsRect(const int& x, const int& y) const = 0;
};

/**
 * @brief   The simple version of button, using 3 bitmaps to generate.
 * @class   SDL_Button
 * @inherit SDL_ButtonInterface
 */
class SDL_Button : public SDL_ButtonInterface {
private:
    SDL_TextureEx *_texture, *_texture_hover, *_texture_click;                     ///< The textures of bitmaps.
    CALLBACK_FUNC _OnClick;                                                      ///< The callback function.
    void* _click_param;
    enum class ButtonStatus { NORMAL, HOVER, CLICK };
    ButtonStatus _status = ButtonStatus::NORMAL; ///< The status of the button.

public:
    SDL_Button(const char* texture_path_, const char* texture_hover_path_, const char* texture_click_path_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_Button(const char* texture_path_, const char* texture_hover_path_, const char* texture_click_path_, const int& x_, const int& y_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_Button(SDL_ResourceID texture_id, SDL_ResourceID texture_hover_id, SDL_ResourceID texture_click_id, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_Button(SDL_ResourceID texture_id, SDL_ResourceID texture_hover_id, SDL_ResourceID texture_click_id, const int& x_, const int& y_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_Button(SDL_TextureEx* texture_, SDL_TextureEx* texture_hover_, SDL_TextureEx* texture_click_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);

    ~SDL_Button() override;

    void Click() override;

    void Bind(CALLBACK_FUNC OnClick_, void* click_param_) override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    [[nodiscard]] SDL_Rect GetRect() const override;

    [[nodiscard]] bool IsRect(const int& x_, const int& y_) const override;

    int EventHandler(const SDL_Event& event_) override;

    void Render() override;

    static SDL_Button* CreateButtonFromXML(const DOM::Node& node);
};

class SDL_TextButton : public SDL_ButtonInterface {
private:
    SDL_Text *_text, *_text_hover, *_text_click;
    CALLBACK_FUNC _OnClick;
    void* _click_param;
    enum class ButtonStatus { NORMAL, HOVER, CLICK };
    ButtonStatus _status = ButtonStatus::NORMAL;

public:
    SDL_TextButton(SDL_Text* text_, SDL_Text* text_hover_, SDL_Text* text_click_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_TextButton(SDL_Text* text_, SDL_Text* text_hover_, SDL_Text* text_click_, const int& x_, const int& y_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);
    SDL_TextButton(TTF_Font* font, const char* text, int pt_size, SDL_Color fg, SDL_Color fg_hover, SDL_Color fg_click, const int& x_, const int& y_, CALLBACK_FUNC OnClick_ = nullptr, void* click_param_ = nullptr);

    ~SDL_TextButton() override;

    void Click() override;

    void Bind(CALLBACK_FUNC OnClick_, void* click_param_) override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    [[nodiscard]] SDL_Rect GetRect() const override;

    [[nodiscard]] bool IsRect(const int& x_, const int& y_) const override;

    int EventHandler(const SDL_Event& event_) override;

    void Render() override;

    static SDL_TextButton* CreateTextButtonFromXML(const DOM::Node& node);
};

extern const ::std::unordered_map<::std::string, CALLBACK_FUNC> Preset_Callback;

#endif //_SDL_BUTTON_H_

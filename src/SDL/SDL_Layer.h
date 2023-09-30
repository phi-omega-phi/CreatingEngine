/**
 * @file    SDL_Layer.h
 * @author  0And1Story
 * @date    2023-7-9
 * @brief   The Layer Module for SDL.
 */

#ifndef _SDL_LAYER_H_
#define _SDL_LAYER_H_

#include "SDL.h"
#include "SDL_Setting.h"
#include "SDL_Widget.h"
#include "SDL_Texture.h"
#include "SDL_Button.h"
#include "XML_Parser.h"
#include <list>
#include <string>
#include <set>
#include <unordered_set>

#define SDL_CreateLayer(...) new SDL_Layer(__VA_ARGS__)
#define SDL_DestroyLayer(layer) delete layer

/**
 * @brief   The layer which contains widgets.
 * @class   SDL_Layer
 * @inherit SDL_Widget
 * @details The implementation of multi-layer rendering.\n
 */
class SDL_Layer : public SDL_InteractiveWidget {
private:
    ::std::list<SDL_Widget*> _widgets;  ///< The list of widgets.
    SDL_Point _position;                ///< The position of layer.
    CALLBACK_FUNC _DefaultCallback = nullptr;
    void* _default_param = nullptr;

public:
    SDL_Layer();
    SDL_Layer(const int& x_, const int& y_);

    ~SDL_Layer() override;

    void AddWidget(SDL_Widget* widget_);

    void PushBack(SDL_Widget* widget_);
    void PushFront(SDL_Widget* widget_);
    void PopBack();
    void PopFront();

    SDL_Widget*& GetWidgetByIndex(size_t index);
    SDL_Widget*& operator[](size_t index);

    void Replace(SDL_Widget* old_widget_, SDL_Widget* new_widget_);
    void ReplaceRecursive(SDL_Widget* old_widget_, SDL_Widget* new_widget_);

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void Bind(CALLBACK_FUNC DefaultCallBack_, void* default_param_);

    int EventHandler(const SDL_Event& event_) override;

    void Render() override;

    static SDL_Layer* CreateLayerFromXML(const DOM::Node& node);

    static SDL_Widget* CreateWidgetFromXML(const DOM::Node& node);
};

#endif //_SDL_LAYER_H_

/**
  * @file   SC_GamePlay.h
  * @author 0And1Story
  * @date   2023-10-09
  * @brief  
  */

#ifndef _SC_GAMEPLAY_H_
#define _SC_GAMEPLAY_H_

#include "SDL.h"
#include "SDL_Layer.h"
#include "SDL_Texture.h"
#include "SDL_Text.h"
#include "SDL_OverflowWidget.h"

#include <vector>
#include <string>

class SC_GamePlay {
public:
    SDL_Layer* dialogue_layer;

    typedef ::std::vector<::std::vector<::std::string>> ScriptList;
    ScriptList scripts{};
    ScriptList::iterator script{};

    SDL_TextureEx** dialogue_bg = nullptr;
    SDL_TextureEx** dialogue_light = nullptr;
    SDL_TextureEx** dialogue_textbox_bg = nullptr;
    SDL_TextureEx** dialogue_textbox_overflow_bg = nullptr;
    SDL_TextBox** dialogue_textbox = nullptr;
    SDL_OverflowWidget** dialogue_textbox_overflow = nullptr;
    SDL_Text** dialogue_textbox_title = nullptr;

    SDL_TextureEx* texture_textbox_bg;
    SDL_TextureEx* texture_textbox_overflow_bg;
    SDL_TextureEx* texture_light_off;

public:
    SC_GamePlay(SDL_Layer* dialogue_layer_);
    ~SC_GamePlay();

    void LoadScript(SDL_ResourceID id);

    void ResetScript();
    void NextScript();
    void AdvanceScript(int n);
    void SetScript(int n);

    void ExecuteScript();
};


#endif //_SC_GAMEPLAY_H_

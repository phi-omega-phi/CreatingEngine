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
#include "SDL_MultiColumnWidget.h"

#include "SC_Const.h"

#include "SaveSystem.h"

#include <vector>
#include <string>
#include <unordered_map>

class SC_GamePlay {
public:
    SDL_Layer* dialogue_layer;

    typedef ::std::vector<::std::string> ScriptType;
    typedef ::std::vector<ScriptType> ScriptList;
    typedef ::std::string LabelType;
    typedef ::std::unordered_map<LabelType, int> LabelMap;
    SDL_ResourceID script_file{};
    ScriptList scripts{};
    ScriptList::iterator script{};
    LabelMap labels{};

    SaveData::Bitmap screenshot;

    SDL_TextureEx** dialogue_bg = nullptr;
    SDL_MultiColumnWidget** dialogue_fg = nullptr;
    SDL_TextureEx** dialogue_light = nullptr;
    SDL_TextureEx** dialogue_textbox_bg = nullptr;
    SDL_TextureEx** dialogue_textbox_overflow_bg = nullptr;
    SDL_TextBox** dialogue_textbox = nullptr;
    SDL_OverflowWidget** dialogue_textbox_overflow = nullptr;
    SDL_Text** dialogue_textbox_title = nullptr;
    SDL_OverflowWidget** dialogue_choice = nullptr;
    SDL_OverflowWidget* dialogue_choice_invisible = nullptr;

    SDL_TextureEx* texture_textbox_bg;
    SDL_TextureEx* texture_textbox_overflow_bg;
    SDL_TextureEx* texture_light_off;

public:
    SC_GamePlay(SDL_Layer* dialogue_layer_);
    ~SC_GamePlay();

    void ResetEnvironment();

    void LoadScript(SDL_ResourceID id);

    void ResetScript();
    void NextScript();
    void NextScript(ScriptList::iterator& it);
    void AdvanceScript(int n);
    void AdvanceScript(ScriptList::iterator& it, int n);
    void SetScript(int n);
    void ResumeScript();

    void ExecuteScript();
    void ExecuteScript(ScriptList::iterator& it);
    bool ExecuteScript(ScriptType& command);

    ::std::string CommandString(ScriptType& command);

    void ShowChoice(const ::std::vector<ScriptList::iterator>& choice_list);
    void HideChoice(int line);

    void Save(const char* file_name);
    void Load(const char* file_name);

    void CaptureScreenshot();
};


#endif //_SC_GAMEPLAY_H_

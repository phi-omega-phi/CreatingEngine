/**
  * @file   SC_GamePlay.cpp
  * @author 0And1Story
  * @date   2023-10-09
  * @brief  
  */

#include "SC_GamePlay.h"

#include "SDL_FileLog.h"
#include "SDL_Button.h"

SC_GamePlay::SC_GamePlay(SDL_Layer* dialogue_layer_): dialogue_layer(dialogue_layer_) {
    dialogue_bg = (SDL_TextureEx**)dialogue_layer->PushBack(nullptr);
    dialogue_fg = (SDL_MultiColumnWidget**)dialogue_layer->PushBack(new SDL_MultiColumnWidget);
    dialogue_light = (SDL_TextureEx**)dialogue_layer->PushBack(nullptr);
    dialogue_textbox_bg = (SDL_TextureEx**)dialogue_layer->PushBack(nullptr);
    dialogue_textbox_overflow_bg = (SDL_TextureEx**)dialogue_layer->PushBack(nullptr);
    dialogue_textbox = (SDL_TextBox**)dialogue_layer->PushBack(nullptr);
    dialogue_textbox_overflow = (SDL_OverflowWidget**)dialogue_layer->PushBack(new SDL_OverflowWidget(100, 100, 50));
    dialogue_textbox_title = (SDL_Text**)dialogue_layer->PushBack(nullptr);
    dialogue_choice = (SDL_OverflowWidget**)dialogue_layer->PushBack(nullptr);

    dialogue_choice_invisible = new SDL_OverflowWidget(0, 0, 50);

    texture_textbox_bg = new SDL_TextureEx("gui/textbox.png", 0, 535);
    texture_textbox_overflow_bg = new SDL_TextureEx("gui/nvl.png");
    texture_light_off = new SDL_TextureEx("presets/translucent.png");
}

SC_GamePlay::~SC_GamePlay() = default;

void SC_GamePlay::LoadScript(SDL_ResourceID id) {
    void* script_buffer = SDL_ResourceReader.LoadText(SDL_ResourceReader.GetResourceID("script/bx.css"));
    std::string script_str((const char*)script_buffer);
    SDL_ResourceReader.FreeResource(script_buffer);
    scripts = ::std::split_each(::std::split(script_str), '\t');
    script = scripts.begin();
}

void SC_GamePlay::ResetScript() {
    script = scripts.begin();
}

void SC_GamePlay::NextScript() {
    if ((*script)[0] == "【开始选择支】") return;
    ++script;
}

void SC_GamePlay::AdvanceScript(int n) {
    ::std::advance(script, n);
}

void SC_GamePlay::SetScript(int n) {
    script = scripts.begin();
    ::std::advance(script, n - 1);
}

void SC_GamePlay::ExecuteScript() {
#if !defined(NDEBUG) && false
    ::std::string str;
    for (auto& command : *script) str += command + '\t';
    SDL_FileDebug("Execute: {}", str);
#endif
    if ((*script)[0] == "【全屏旁白】") {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = nullptr;
        *dialogue_textbox_bg = nullptr;
        *dialogue_textbox_overflow_bg = texture_textbox_overflow_bg;
        delete *dialogue_textbox;
        *dialogue_textbox = nullptr;
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->AddWidget(new SDL_Text(
                global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                (*script)[1].c_str(), 26, {255,255,255,255}));
    } else if ((*script)[0] == "【旁白】") {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = nullptr;
        *dialogue_textbox_bg = texture_textbox_bg;
        *dialogue_textbox_overflow_bg = nullptr;
        delete *dialogue_textbox;
        *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                            (*script)[1].c_str(), 26, {255,255,255,255},
                                            settings.window.width - 400, 200, 580);
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else if ((*script)[0] == "【清屏】") {
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else if ((*script)[0] == "【背景】") {
        delete *dialogue_bg;
        *dialogue_bg = new SDL_TextureEx(SDL_ResourceReader.GetResourceID((*script)[1].c_str()),
                                         0, 0, settings.window.width, settings.window.height);
        NextScript();
        ExecuteScript();
    } else if ((*script)[0] == "【关灯】") {
        *dialogue_light = texture_light_off;
        NextScript();
        ExecuteScript();
    } else if ((*script)[0] == "【开灯】") {
        *dialogue_light = nullptr;
        NextScript();
        ExecuteScript();
    } else if ((*script)[0] == "【登场】") {
        (*dialogue_fg)->AddWidget((*script)[1], new SDL_TextureEx(SDL_ResourceReader.GetResourceID((*script)[2].c_str())));
    } else if ((*script)[0] == "【退场】") {
        (*dialogue_fg)->RemoveWidget((*script)[1]);
    } else if ((*script)[0] == "【跳转】") {
        SetScript(::std::stoi((*script)[1]));
        ExecuteScript();
        NextScript();
    } else if ((*script)[0] == "【开始选择支】") {
        ::std::vector<ScriptList::iterator> choice_list;
        for (auto it = script; (*it)[0] != "【结束选择支】"; ++it) {
            if ((*it)[0] == "【选项】") {
                choice_list.push_back(it);
            }
        }
        ShowChoice(choice_list);
    } else if ((*script)[0].substr(0, 3) != "【" && (*script).size() == 2) {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")),
                                               (*script)[0].c_str(), 35, {223, 183, 139},
                                               150, 540);
        *dialogue_textbox_bg = texture_textbox_bg;
        *dialogue_textbox_overflow_bg = nullptr;
        delete *dialogue_textbox;
        if ((*script)[1].substr(0, 3) != "「" && (*script)[1].substr((*script)[1].size() - 3, 3) != "」")
            (*script)[1] = "「" + (*script)[1] + "」";
        *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                            ((*script)[1]).c_str(), 26, {255,255,255,255},
                                            settings.window.width - 400, 200, 580);
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else {
        ::std::string str;
        for (auto& command : *script) str += command + '\t';
        SDL_FileWarning("Skip Script: {}", str);
        NextScript();
        ExecuteScript();
    }
}

void SC_GamePlay::ShowChoice(const ::std::vector<ScriptList::iterator>& choice_list) {
    if (*dialogue_choice != nullptr) return;
    (*dialogue_choice) = dialogue_choice_invisible;
    dialogue_choice_invisible = nullptr;
    (*dialogue_choice)->Clear();
    for (auto& choice : choice_list) {
        auto button_layer = new SDL_Layer;
        auto button_bg = new SDL_Button("gui/button/choice_idle_background.png", "gui/button/choice_hover_background.png", "gui/button/choice_hover_background.png",
                                        Preset_Callback.at("send_choice"), (void*)(::std::distance(scripts.begin(), choice) + 1));
        auto button_text = new SDL_Text(SDL_ResourceReader.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")), (*choice)[1].c_str(), 30, {255,255,255,255});

        auto bg_rect = button_bg->GetRect();
        auto text_rect = button_text->GetRect();
        button_text->SetPosition((bg_rect.w - text_rect.w) / 2, (bg_rect.h - text_rect.h) / 2);

        button_layer->AddWidget(button_bg);
        button_layer->AddWidget(button_text);

        (*dialogue_choice)->AddWidget(button_layer);

        SDL_Rect choice_button_rect = (*dialogue_choice)->GetRect();
        (*dialogue_choice)->SetPosition((settings.window.width - choice_button_rect.w) / 2, (settings.window.height - choice_button_rect.h) / 2);
    }
}

void SC_GamePlay::HideChoice(int line) {
    dialogue_choice_invisible = (*dialogue_choice);
    (*dialogue_choice) = nullptr;
    SetScript(line);
    ExecuteScript();
    NextScript();
}

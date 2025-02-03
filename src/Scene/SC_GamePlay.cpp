/**
  * @file   SC_GamePlay.cpp
  * @author 0And1Story
  * @date   2023-10-09
  * @brief  
  */

#include "SC_GamePlay.h"

#include "SDL_FileLog.h"
#include "SDL_Button.h"
#include "SDL_Sound.h"

#include "SaveSystem.h"

#include <set>

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
    script_file = id;

    void* script_buffer = SDL_ResourceReader.LoadText(id);
    std::string script_str((const char*)script_buffer);
    SDL_ResourceReader.FreeResource(script_buffer);
    scripts = ::std::split_each(::std::split(script_str), '\t');

    // Initialize the label list.
    for (auto it = scripts.begin(); it != scripts.end(); ++it) {
        if (!it->empty() && (*it)[0] == "【标签】") {
            labels[(*it)[1]] = it - scripts.begin() + 1;
        }
    }

    script = scripts.begin();
}

void SC_GamePlay::ResetScript() {
    script = scripts.begin();
}

void SC_GamePlay::NextScript() {
    NextScript(script);
}

void SC_GamePlay::NextScript(ScriptList::iterator& it) {
    if (!it->empty() && (*it)[0] == "【开始选择支】") return;
    ++it;
}

void SC_GamePlay::AdvanceScript(int n) {
    ::std::advance(script, n);
}

void SC_GamePlay::AdvanceScript(ScriptList::iterator& it, int n) {
    ::std::advance(it, n);
}

void SC_GamePlay::SetScript(int n) {
    script = scripts.begin();
    ::std::advance(script, n - 1);
}

void SC_GamePlay::ResumeScript() {
    auto last_bg = script;
    ::std::set<::std::string> needs{"【背景】", "【音乐】"};
    while (last_bg != scripts.begin() && !needs.empty()) {
        if (!last_bg->empty() && needs.contains((*last_bg)[0])) needs.erase((*last_bg)[0]);
        --last_bg;
    }
    auto tmp = script;
    script = last_bg;
    while (script != tmp) {
        if (!script->empty() && (*script)[0] == "【开始选择支】") continue;
        ExecuteScript();
        NextScript();
    }
}

void SC_GamePlay::ExecuteScript() {
    ExecuteScript(script);
}

void SC_GamePlay::ExecuteScript(ScriptList::iterator& it) {
    // If the script should be skipped, then execute the next script.
    if (ExecuteScript(*it)) {
        NextScript(it);
        ExecuteScript(it);
    }
}

/**
 * @brief   Execute the script.
 * @param   command The script.
 * @return  Whether the script should be skipped and execute the next script immediately.
 */
bool SC_GamePlay::ExecuteScript(ScriptType& command) {
#if !defined(NDEBUG) && SCRIPT_LOG
    SDL_FileDebug("Execute: {}", CommandString(command));
#endif
    if (command.empty()) {
        return true;
    } else if (command[0] == "【全屏旁白】") {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = nullptr;
        *dialogue_textbox_bg = nullptr;
        *dialogue_textbox_overflow_bg = texture_textbox_overflow_bg;
        delete *dialogue_textbox;
        *dialogue_textbox = nullptr;
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->AddWidget(new SDL_Text(
                global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                command[1].c_str(), 26, {255,255,255,255}));
    } else if (command[0] == "【旁白】") {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = nullptr;
        *dialogue_textbox_bg = texture_textbox_bg;
        *dialogue_textbox_overflow_bg = nullptr;
        delete *dialogue_textbox;
        *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                            command[1].c_str(), 26, {255,255,255,255},
                                            settings.window.width - 400, 200, 580);
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else if (command[0] == "【清屏】") {
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else if (command[0] == "【背景】") {
        delete *dialogue_bg;
        *dialogue_bg = new SDL_TextureEx(SDL_ResourceReader.GetResourceID(command[1].c_str()),
                                         0, 0, settings.window.width, settings.window.height);
        return true;
    } else if (command[0] == "【关灯】") {
        *dialogue_light = texture_light_off;
        return true;
    } else if (command[0] == "【开灯】") {
        *dialogue_light = nullptr;
        return true;
    } else if (command[0] == "【登场】") {
        (*dialogue_fg)->AddWidget(command[1], new SDL_TextureEx(SDL_ResourceReader.GetResourceID(command[2].c_str())));
    } else if (command[0] == "【退场】") {
        (*dialogue_fg)->RemoveWidget(command[1]);
    } else if (command[0] == "【跳转】") {
        if (command[1] == "【标签】") SetScript(labels.at(command[2]));
        else if (command[1] == "【行号】") SetScript(::std::stoi(command[2]));
        return true;
    } else if (command[0] == "【开始选择支】") {
        ::std::vector<ScriptList::iterator> choice_list;
        for (auto it = script; (*it)[0] != "【结束选择支】"; ++it) {
            if ((*it)[0] == "【选项】") {
                choice_list.push_back(it);
            }
        }
        ShowChoice(choice_list);
    } else if (command[0] == "【结束选择支】") {
        return true;
    } else if (command[0] == "【选项】") {
        while ((*script)[0] != "【结束选择支】") NextScript();
        return true;
    } else if (command[0] == "【音乐】") {
        if (command[1] == "【播放】") {
            if (!SDL_Sound.LoadMusic(SDL_ResourceReader.GetResourceID(command[2].c_str()))) return true;
            if (command.size() >= 5) {
                if (command[3] == "【淡入】") SDL_Sound.FadeInMusic(::std::stoi(command[4]));
                else SDL_Sound.PlayMusic();
            } else {
                SDL_Sound.PlayMusic();
            }
        } else if (command[1] == "【停止】") {
            if (command.size() >= 4) {
                if (command[2] == "【淡出】") SDL_Sound.FadeOutMusic(::std::stoi(command[3]));
                else SDL_Sound.StopMusic();
            } else {
                SDL_Sound.StopMusic();
            }
        }
        return true;
    } else if (command[0] == "【】") {
    } else if (command[0].substr(0, 3) != "【" && command.size() == 2) {
        delete *dialogue_textbox_title;
        *dialogue_textbox_title = new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")),
                                               command[0].c_str(), 35, {223, 183, 139},
                                               150, 540);
        *dialogue_textbox_bg = texture_textbox_bg;
        *dialogue_textbox_overflow_bg = nullptr;
        delete *dialogue_textbox;
        if (command[1].substr(0, 3) != "「" && command[1].substr(command[1].size() - 3, 3) != "」")
            command[1] = "「" + command[1] + "」";
        *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                            (command[1]).c_str(), 26, {255,255,255,255},
                                            settings.window.width - 400, 200, 580);
        ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
    } else {
        SDL_FileWarning("Skip Script: [{}] {}", script - scripts.begin() + 1, CommandString(command));
        return true;
    }
    // No need to skip the script, then we return false as default.
    return false;
}

::std::string SC_GamePlay::CommandString(SC_GamePlay::ScriptType& command) {
    ::std::string str;
    for (auto& param : command) str += param + '\t';
    return str;
}

void SC_GamePlay::ShowChoice(const ::std::vector<ScriptList::iterator>& choice_list) {
    if (*dialogue_choice != nullptr) return;
    (*dialogue_choice) = dialogue_choice_invisible;
    dialogue_choice_invisible = nullptr;
    (*dialogue_choice)->Clear();
    for (auto& choice : choice_list) {
        auto button_layer = new SDL_Layer;
        auto* line = new int;
        *line = (int)::std::distance(scripts.begin(), choice) + 1;
        auto button_bg = new SDL_Button("gui/button/choice_idle_background.png", "gui/button/choice_hover_background.png", "gui/button/choice_hover_background.png",
                                        Preset_Callback.at("send_choice"), (void*)line);
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
    SetScript(line + 1);
    ExecuteScript();
    NextScript();
}

void SC_GamePlay::Save(const char* file_name) {
    SaveData save_data;
    save_data.title = CommandString(*script);
    save_data.chapter = "";
    save_data.time = std::chrono::system_clock::now();
    save_data.progress.file = script_file;
    save_data.progress.line = script - scripts.begin() + 1;

    save_data.save(file_name);
}

void SC_GamePlay::Load(const char* file_name) {
    SaveData save_data;
    save_data.load(file_name);

    this->LoadScript(save_data.progress.file);
    this->SetScript(save_data.progress.line);
    this->ResumeScript();
}

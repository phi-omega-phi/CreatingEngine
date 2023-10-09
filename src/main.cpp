/**
 * @file    main.cpp
 * @author  0And1Story
 * @date    2023-7-2
 * @brief   The entry point of the program.
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_Global.h"
#include "SDL_Texture.h"
#include "SDL_Button.h"
#include "SDL_Layer.h"
#include "SDL_FileLog.h"
#include "SDL_Text.h"
#include "SDL_OverflowWidget.h"

#include <sstream>

int main(int argc, char* argv[]) {

    SDL_FileLog.CreateFileByTime("log");
    SDL_FileLog("Hello, World!");

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_FileLog("SDL Init Failed.");
        return 1;
    }
    SDL_FileLog("SDL Init Successfully.");
    TTF_Init();

    settings.SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    settings.SetWindowScale(WINDOW_SCALE);

    SDL_FileLog("WINDOW_WIDTH:{} WINDOW_HEIGHT:{}", settings.window.width, settings.window.height);

    SDL_Rect window_rect = {SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, settings.window.width,
                            settings.window.height};

    SDL_Window *main_window = SDL_CreateWindow(
            "Creating Engine",
            window_rect.x, window_rect.y, (int) (window_rect.w * settings.window.scale),
            (int) (window_rect.h * settings.window.scale),
            SDL_WINDOW_SHOWN
    );
    SDL_SetWindowIcon(main_window, SDL_ResourceReader.LoadImage(SDL_ResourceReader.GetResourceID("gui/icon.png")));
    SDL_Renderer *renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    settings.SetWindowHandler(main_window);
    settings.SetRenderer(renderer);
    if (settings.Check()) {
        SDL_Log("Missing necessary settings!");
        return 1;
    }
    SDL_FileLog("Settings loaded successfully.");
    SDL_RenderSetScale(renderer, settings.window.scale, settings.window.scale);

    auto layer_1 = global.LoadLayerFromXML(SDL_ResourceReader.GetResourceID("gui/main_menu.csui"));
    auto layer_2 = global.LoadLayerFromXML(SDL_ResourceReader.GetResourceID("gui/test_layer.csui"));

    auto texture_bg_1 = (SDL_TextureEx*)layer_1->GetWidgetByIndex(0);
    auto texture_bg_2 = (SDL_TextureEx*)layer_2->GetWidgetByIndex(0);

//    auto overflow_1 = new SDL_OverflowWidget(50, 100);
//    layer_1->AddWidget(overflow_1);
//    overflow_1->AddWidget(new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")), "123", 40, {0,0,0,255}));
//    overflow_1->AddWidget(new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")), "456", 40, {0,0,0,255}));
//    overflow_1->AddWidget(new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")), "789", 40, {0,0,0,255}));

    auto textbox_bg = new SDL_TextureEx("gui/textbox.png", 0, 535);
    auto textbox_overflow_bg = new SDL_TextureEx("gui/nvl.png");
    auto texture_light_off = new SDL_TextureEx("presets/translucent.png");

    auto dialogue_layer = new SDL_Layer;
    auto dialogue_bg = dialogue_layer->PushBack((SDL_TextureEx*)nullptr);
    auto dialogue_light = dialogue_layer->PushBack((SDL_TextureEx*)nullptr);
    auto dialogue_textbox_bg = dialogue_layer->PushBack(nullptr);
    auto dialogue_textbox_overflow_bg = dialogue_layer->PushBack(nullptr);
    auto dialogue_textbox = dialogue_layer->PushBack((SDL_TextBox*) nullptr);
    auto dialogue_textbox_overflow = dialogue_layer->PushBack(new SDL_OverflowWidget(100, 100, 50));
    auto dialogue_textbox_title = dialogue_layer->PushBack((SDL_Text*) nullptr);

    global.current_layer = dialogue_layer;

    void* script_buffer = SDL_ResourceReader.LoadText(SDL_ResourceReader.GetResourceID("script/bx.css"));
    std::string script((const char*)script_buffer);
    SDL_ResourceReader.FreeResource(script_buffer);

    auto scripts = std::split_each(std::split(script), '\t');
    size_t script_now = -1;

    global.is_quit = false;
    global.is_render = false;
    SDL_Event event;
    while (!global.is_quit) {
        global.is_render = false;
        SDL_WaitEvent(&event);
//        SDL_PollEvent(&event);
//        SDL_Log("%d %d\n", event.motion.x, event.motion.y);
        do {
            switch (event.type) {
                case SDL_QUIT:
                    global.is_quit = true;
                    break;

                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    if (!global.current_layer->EventHandler(event) && event.type == SDL_MOUSEBUTTONUP) {
                        ++script_now;
                        if (scripts[script_now][0] == "【全屏旁白】") {
                            delete *dialogue_textbox_title;
                            *dialogue_textbox_title = nullptr;
                            *dialogue_textbox_bg = nullptr;
                            *dialogue_textbox_overflow_bg = textbox_overflow_bg;
                            delete *dialogue_textbox;
                            *dialogue_textbox = nullptr;
                            ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->AddWidget(new SDL_Text(
                                    global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                    scripts[script_now][1].c_str(), 26, {255,255,255,255}));
                        } else if (scripts[script_now][0] == "【旁白】") {
                            delete *dialogue_textbox_title;
                            *dialogue_textbox_title = nullptr;
                            *dialogue_textbox_bg = textbox_bg;
                            *dialogue_textbox_overflow_bg = nullptr;
                            delete *dialogue_textbox;
                            *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                                                scripts[script_now][1].c_str(), 26, {255,255,255,255},
                                                                settings.window.width - 100, 50, 560);
                            ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
                        } else if (scripts[script_now][0] == "【清屏】") {
                            ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
                        } else if (scripts[script_now][0] == "【背景】") {
                            delete *dialogue_bg;
                            *dialogue_bg = new SDL_TextureEx(SDL_ResourceReader.GetResourceID(scripts[script_now][1].c_str()),
                                                             0, 0, settings.window.width, settings.window.height);
                        } else if (scripts[script_now][0] == "【关灯】") {
                            *dialogue_light = texture_light_off;
                        } else if (scripts[script_now][0] == "【开灯】") {
                            *dialogue_light = nullptr;
                        } else if (scripts[script_now][0].substr(0, 3) != "【" && scripts[script_now].size() == 2) {
                            delete *dialogue_textbox_title;
                            *dialogue_textbox_title = new SDL_Text(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf")),
                                                                   scripts[script_now][0].c_str(), 30, {255,255,255,255},
                                                                   50, 500);
                            *dialogue_textbox_bg = textbox_bg;
                            *dialogue_textbox_overflow_bg = nullptr;
                            delete *dialogue_textbox;
                            if (scripts[script_now][1].substr(0, 3) != "「" && scripts[script_now][1].substr(scripts[script_now][1].size() - 4) != "」")
                                scripts[script_now][1] = "「" + scripts[script_now][1] + "」";
                            *dialogue_textbox = new SDL_TextBox(global.LoadFont(SDL_ResourceReader.GetResourceID("fonts/text.ttf")),
                                                                (scripts[script_now][1]).c_str(), 26, {255,255,255,255},
                                                                settings.window.width - 100, 50, 560);
                            ((SDL_OverflowWidget*)(*dialogue_textbox_overflow))->Clear();
                        }
                    }
                    global.is_render = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat) break;
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
//                        layer_1->ReplaceRecursive(texture_bg, texture_2);
                        layer_1->GetWidgetByIndex(0) = texture_bg_2;
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        global.current_layer->SetPosition(50, 50);
                        global.is_render = true;
                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
//                        layer_1->ReplaceRecursive(texture_2, texture_bg);
                        layer_1->GetWidgetByIndex(0) = texture_bg_1;
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        global.current_layer->SetPosition(0, 0);
                        global.is_render = true;
                    }
                    break;

                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    break;

                case SDL_USER_RENDER:
                    global.is_render = true;
                    break;

                default:
//                    SDL_Log("%d\n", event.type);
                    global.is_render = true;
                    break;
            }
        } while (SDL_PollEvent(&event));

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if (!global.is_render) continue;

        global.current_layer->Render();

        SDL_RenderPresent(renderer);
    }

    delete layer_1;
    delete layer_2;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);

    TTF_Quit();
    SDL_Quit();

    SDL_FileLog("SDL Quit.");

    SDL_FileLog.CloseFile();

    return 0;
}

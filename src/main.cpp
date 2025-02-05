/**
 * @file    main.cpp
 * @author  0And1Story
 * @date    2023-7-2
 * @brief   The entry point of the program.
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_Global.h"
#include "SDL_Texture.h"
#include "SDL_Button.h"
#include "SDL_Layer.h"
#include "SDL_FileLog.h"
#include "SDL_Text.h"
#include "SDL_OverflowWidget.h"
#include "SDL_MultiColumnWidget.h"

#include "SDL_Sound.h"

#include "SC_GamePlay.h"

int main(int argc, char* argv[]) {

    SDL_FileLog.CreateFileByTime("log");
    SDL_FileLog("Hello, World!");

    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        SDL_FileLog("SDL Init Failed.");
        return 1;
    }
    SDL_FileLog("SDL Init Successfully.");
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP | IMG_INIT_JXL | IMG_INIT_AVIF);
    TTF_Init();
    Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID | MIX_INIT_OPUS);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

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
    settings.SetSavePath("./save");
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

    auto dialogue_layer = global.LoadLayerFromXML(SDL_ResourceReader.GetResourceID("gui/game_play.csui"));
    SC_GamePlay game_play(dialogue_layer);
    global.game_play = &game_play;
    game_play.LoadScript(SDL_ResourceReader.GetResourceID("script/bx.css"));
    game_play.dialogue_layer->AddWidget(global.LoadLayerFromXML(SDL_ResourceReader.GetResourceID("gui/game_play_buttons.csui")));

//    global.current_layer = layer_1;
    global.PushLayer(layer_1);

//    SDL_Sound.LoadMusic(SDL_ResourceReader.GetResourceID("bgm/title.ogg"));
//    SDL_Sound.PlayMusic();

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
                case SDL_MOUSEBUTTONUP: {
                        int handle_num = global.current_layer->EventHandler(event);
                        if (global.current_layer == game_play.dialogue_layer && !handle_num && event.type == SDL_MOUSEBUTTONUP) {
                            game_play.ExecuteScript();
                            game_play.NextScript();
                        }
                    }
                    global.is_render = true;
                    break;

                case SDL_MOUSEWHEEL:
                    if (event.wheel.y < 0 && global.current_layer == game_play.dialogue_layer) {
                        game_play.ExecuteScript();
                        game_play.NextScript();
                    }
                    global.is_render = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat) break;
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                        layer_1->GetWidgetByIndex(0) = texture_bg_2;
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        global.current_layer->SetPosition(50, 50);
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                        SDL_Sound.PauseMusic();
                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                        layer_1->GetWidgetByIndex(0) = texture_bg_1;
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        global.current_layer->SetPosition(0, 0);
                        global.is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
                        SDL_Sound.ContinueMusic();
                    }
                    break;

                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    break;

                case SDL_USER_RENDER:
                    global.is_render = true;
                    break;

                case SDL_USER_GAMESTART:
                    game_play.ResumeScript();

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
    delete dialogue_layer;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);

    SDL_CloseAudio();

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();

    SDL_FileLog("SDL Quit.");

    SDL_FileLog.CloseFile();

    return 0;
}

/**
 * @file    main.cpp
 * @author  0And1Story
 * @date    2023-7-2
 * @brief   The entry point of the program.
 */

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_Texture.h"
#include "SDL_Button.h"
#include "SDL_Layer.h"
#include "SDL_FileLog.h"
#include "SDL_Text.h"

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

    auto texture = new SDL_TextureEx("resources/title_logo1.bmp");
    auto texture_bg = new SDL_TextureEx("gui/main_menu.png", 0, 0, settings.window.width, settings.window.height);
    texture->SetPosition((window_rect.w - texture->GetW()) / 2 + 150, (window_rect.h - texture->GetH()) / 2);
    auto layer_1 = new SDL_Layer;
    layer_1->AddWidget(texture_bg);
    layer_1->AddWidget(texture);
    SDL_Layer* current_layer = layer_1;

    TTF_Font* font = SDL_ResourceReader.LoadFont(SDL_ResourceReader.GetResourceID("fonts/gui.ttf"));
    auto text_1 = new SDL_Text(font, "开始游戏", 40, {255, 255, 255, 255}, 120, 120);
    layer_1->AddWidget(text_1);
    TTF_CloseFont(font);

    auto texture_2 = new SDL_TextureEx("resources/BG200_000.bmp", 0, 0, settings.window.width, settings.window.height);

    bool is_quit = false;
    bool is_render = false;
    SDL_Event event;
    while (!is_quit) {
        is_render = false;
        SDL_WaitEvent(&event);
//        SDL_PollEvent(&event);
//        SDL_Log("%d %d\n", event.motion.x, event.motion.y);
        do {
            switch (event.type) {
                case SDL_QUIT:
                    is_quit = true;
                    break;

                case SDL_MOUSEMOTION:
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    current_layer->EventHandler(event);
                    is_render = true;
                    break;

                case SDL_KEYDOWN:
                    if (event.key.repeat) break;
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                        current_layer->ReplaceRecursive(texture_bg, texture_2);
                        is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        current_layer->SetPosition(50, 50);
                        is_render = true;
                    }
                    break;

                case SDL_KEYUP:
                    if (event.key.keysym.scancode == SDL_SCANCODE_F) {
                        current_layer->ReplaceRecursive(texture_2, texture_bg);
                        is_render = true;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
                        current_layer->SetPosition(0, 0);
                        is_render = true;
                    }
                    break;

                case SDL_TEXTINPUT:
                case SDL_TEXTEDITING:
                    break;

                case SDL_USER_RENDER:
                    is_render = true;
                    break;

                default:
//                    SDL_Log("%d\n", event.type);
                    is_render = true;
                    break;
            }
        } while (SDL_PollEvent(&event));

//        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//        SDL_RenderClear(renderer);

        if (!is_render) continue;

        current_layer->Render();

        SDL_RenderPresent(renderer);
    }

    delete layer_1;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(main_window);

    TTF_Quit();
    SDL_Quit();

    SDL_FileLog("SDL Quit.");

    SDL_FileLog.CloseFile();

    return 0;
}

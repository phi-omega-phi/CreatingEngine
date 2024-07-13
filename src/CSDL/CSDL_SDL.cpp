/**
  * @file   CSDL_SDL.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_SDL.h"

#include "CSDL_error.h"

namespace CSDL::SDL {
    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING)) throw error::SDLInitError();
    }

    void init(Uint32 flags) {
        if (SDL_Init(flags)) throw error::SDLInitError();
    }

    void quit() {
        SDL_Quit();
    }
}

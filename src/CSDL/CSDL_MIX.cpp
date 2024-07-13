/**
  * @file   CSDL_MIX.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_MIX.h"

#include "SDL_mixer.h"

#include "CSDL_error.h"

namespace CSDL::MIX {
    void init() {
        if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID) != (MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID)) throw error::SDLInitError();
    }

    void init(int flags) {
        if (Mix_Init(flags) != flags) throw error::SDLInitError();
    }

    void quit() {
        Mix_Quit();
    }
}

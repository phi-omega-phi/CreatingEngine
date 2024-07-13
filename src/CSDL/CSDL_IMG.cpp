/**
  * @file   CSDL_IMG.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_IMG.h"

#include "SDL_image.h"

#include "CSDL_error.h"

namespace CSDL::IMG {
    void init() {
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) throw error::SDLInitError();
    }

    void init(int flags) {
        if (IMG_Init(flags) != flags) throw error::SDLInitError();
    }

    void quit() {
        IMG_Quit();
    }
}

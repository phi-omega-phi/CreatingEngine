/**
  * @file   CSDL_TTF.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_TTF.h"

#include "SDL_ttf.h"

#include "CSDL_error.h"

namespace CSDL::TTF {
    void init() {
        if (TTF_Init()) throw error::SDLInitError();
    }

    void quit() {
        TTF_Quit();
    }
}

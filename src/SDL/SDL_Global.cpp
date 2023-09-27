/**
  * @file   SDL_Global.cpp
  * @author 0And1Story
  * @date   2023-09-27
  * @brief  
  */
#include "SDL_Global.h"

__SDL_Global& __SDL_Global::Instance() {
    static __SDL_Global instance;
    return instance;
}

__SDL_Global& global = __SDL_Global::Instance();

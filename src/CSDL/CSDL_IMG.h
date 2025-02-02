/**
  * @file   CSDL_IMG.h
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#ifndef _CSDL_IMG_H_
#define _CSDL_IMG_H_

#include "SDL_rwops.h"

namespace CSDL::SDL {
    class Surface;
    class Texture;
    class Renderer;
}

namespace CSDL::IMG {
    void init();
    void init(int flags);
    void quit();

    SDL::Surface Load(const char* file);
    SDL::Texture LoadTexture(SDL::Renderer& renderer, const char* file);
    SDL::Surface Load_RW(SDL_RWops *src, int freesrc);
    SDL::Surface LoadFromMem(void* mem, size_t size);
}

#endif //_CSDL_IMG_H_

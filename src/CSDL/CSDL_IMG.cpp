/**
  * @file   CSDL_IMG.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_IMG.h"

#include "SDL_image.h"

#include "CSDL_error.h"
#include "CSDL_Surface.h"
#include "CSDL_Texture.h"
#include "CSDL_Renderer.h"

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

    SDL::Surface Load(const char* file) {
        return IMG_Load(file);
    }

    SDL::Texture LoadTexture(SDL::Renderer& renderer, const char* file) {
        return IMG_LoadTexture(*renderer, file);
    }

    SDL::Surface Load_RW(SDL_RWops* src, int freesrc) {
        return IMG_Load_RW(src, freesrc);
    }

    SDL::Surface LoadFromMem(void* mem, size_t size) {
        return IMG_Load_RW(SDL_RWFromConstMem(mem, size), 1);
    }
}

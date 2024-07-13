/**
  * @file   CSDL_SDL.h
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#ifndef _CSDL_SDL_H_
#define _CSDL_SDL_H_

#include "SDL.h"

namespace CSDL::SDL {
    void init();
    void init(Uint32 flags);
    void quit();
}

#include "CSDL_Window.h"
#include "CSDL_Surface.h"
#include "CSDL_Renderer.h"
#include "CSDL_Texture.h"

#endif //_CSDL_SDL_H_

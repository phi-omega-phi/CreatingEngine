/**
  * @file   CSDL.h
  * @author 0And1Story
  * @date   2024-02-26
  * @brief  
  */

#ifndef _CSDL_H_
#define _CSDL_H_

#include "CSDL_SDL.h"
#include "CSDL_IMG.h"
#include "CSDL_TTF.h"
#include "CSDL_MIX.h"

namespace CSDL {
    void init();
    void quit();

    class SDL_Environment {
    public:
        SDL_Environment();
        ~SDL_Environment();
    };
}

#endif //_CSDL_H_

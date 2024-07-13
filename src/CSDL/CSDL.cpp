/**
  * @file   CSDL.cpp
  * @author 0And1Story
  * @date   2024-02-26
  * @brief  
  */

#include "CSDL.h"

#include <exception>

namespace CSDL {
    void init() {
        SDL::init();
        IMG::init();
        TTF::init();
        MIX::init();
    }

    void quit() {
        IMG::quit();
        TTF::quit();
        MIX::quit();
        SDL::quit();
    }

    SDL_Environment::SDL_Environment() {
        init();
    }

    SDL_Environment::~SDL_Environment() {
        quit();
    }
}

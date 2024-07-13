/**
  * @file   CSDL_error.cpp
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#include "CSDL_error.h"

namespace CSDL::error {
    const char* SDLError::what() const noexcept {
        return SDL_GetError();
    }
}

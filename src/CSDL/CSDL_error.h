/**
  * @file   CSDL_error.h
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#ifndef _CSDL_ERROR_H_
#define _CSDL_ERROR_H_

#include "SDL.h"
#include "SDL_image.h"

#include <exception>

namespace CSDL::error {
    class SDLError : public std::exception {
    public:
        const char * what() const noexcept override;

        SDLError() = default;
        SDLError(const char* info);
    };

    using SDLInitError = SDLError;
    using SDLWindowError = SDLError;
    using SDLSurfaceError = SDLError;
    using SDLRenderError = SDLError;
    using SDLTextureError = SDLError;

    using SDLIMGError = SDLError;
}

#endif //_CSDL_ERROR_H_

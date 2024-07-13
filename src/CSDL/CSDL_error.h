/**
  * @file   CSDL_error.h
  * @author 0And1Story
  * @date   2024-02-27
  * @brief  
  */

#ifndef _CSDL_ERROR_H_
#define _CSDL_ERROR_H_

#include "SDL.h"

#include <exception>

namespace CSDL::error {
    class SDLError : public std::exception {
    public:
        const char * what() const noexcept override;
    };

    using SDLInitError = SDLError;
    using SDLWindowError = SDLError;
    using SDLSurfaceError = SDLError;
    using SDLRenderError = SDLError;
    using SDLTextureError = SDLError;
}

#endif //_CSDL_ERROR_H_

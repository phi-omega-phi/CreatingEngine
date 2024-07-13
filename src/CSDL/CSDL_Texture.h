/**
  * @file   CSDL_Texture.h
  * @author 0And1Story
  * @date   2024-05-03
  * @brief  
  */

#ifndef _CSDL_TEXTURE_H_
#define _CSDL_TEXTURE_H_

#include "SDL.h"

#include "CSDL_Rect.h"

#include <cstddef>

namespace CSDL::SDL {
    class Surface;
    class Renderer;

    class Texture {
    private:
        SDL_Texture* _texture;

    public:
        Texture(SDL_Texture* texture);
        Texture(Renderer& renderer, Uint32 format, int access, int w, int h);
        Texture(Renderer& renderer, Surface& surface);
        ~Texture();

        Texture(Texture&& other) noexcept;
        Texture(const Texture&) = delete;
        Texture& operator=(Texture&& other) noexcept;
        Texture& operator=(const Texture&) = delete;

        [[nodiscard]] SDL_Texture* GetHandler() const noexcept;
        [[nodiscard]] SDL_Texture** GetAddress() noexcept;

        SDL_Texture* operator*() const noexcept;
        SDL_Texture* operator->() const noexcept;

        static Texture CreateTexture(Renderer& renderer, Uint32 format, int access, int w, int h);
        static Texture CreateTextureFromSurface(Renderer& renderer, Surface& surface);

        void Query(Uint32& format, int& access, int& w, int& h);

        void SetColorMod(Uint8 r, Uint8 g, Uint8 b);
        void GetColorMod(Uint8& r, Uint8& g, Uint8& b);
        void SetAlphaMod(Uint8 alpha);
        void GetAlphaMod(Uint8& alpha);
        void SetBlendMode(SDL_BlendMode blendMode);
        void GetBlendMode(SDL_BlendMode& blendMode);
        void SetScaleMode(SDL_ScaleMode scaleMode);
        void GetScaleMode(SDL_ScaleMode& scaleMode);
        void SetUserData(void* userdata);
        void* GetUserData();

        void Update(const Rect& rect, const void* pixels, int pitch);
        void Update(std::nullptr_t rect, const void* pixels, int pitch);

        void UpdateYUVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch);
        void UpdateYUVTexture(std::nullptr_t rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch);
        void UpdateNVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* UVplane, int UVpitch);
        void UpdateNVTexture(std::nullptr_t rect, const Uint8* Yplane, int Ypitch, const Uint8* UVplane, int UVpitch);

        void Lock(const Rect& rect, void*& pixels, int& pitch);
        void LockToSurface(const Rect& rect, Surface& surface);
        void Unlock();

        void GL_BindTexture(float* texw, float* texh);
        void GL_UnbindTexture();
    };
}

#endif //_CSDL_TEXTURE_H_

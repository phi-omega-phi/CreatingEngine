/**
  * @file   CSDL_Texture.cpp
  * @author 0And1Story
  * @date   2024-05-03
  * @brief  
  */

#include "CSDL_Texture.h"
#include "CSDL_Surface.h"
#include "CSDL_Renderer.h"

#include "CSDL_error.h"

namespace  CSDL::SDL {
    Texture::Texture(SDL_Texture* texture) : _texture(texture) {}

    Texture::Texture(Renderer& renderer, Uint32 format, int access, int w, int h) {
        _texture = SDL_CreateTexture(*renderer, format, access, w, h);
    }

    Texture::Texture(Renderer& renderer, Surface& surface) {
        _texture = SDL_CreateTextureFromSurface(*renderer, *surface);
    }

    Texture::~Texture() {
        SDL_DestroyTexture(_texture);
    }

    Texture::Texture(Texture&& other) noexcept : _texture(other._texture) {
        other._texture = nullptr;
    }

    Texture& Texture::operator=(Texture&& other) noexcept {
        if (std::addressof(other) == this) return *this;
        SDL_DestroyTexture(_texture);
        _texture = other._texture;
        other._texture = nullptr;
        return *this;
    }

    SDL_Texture* Texture::GetHandler() const noexcept {
        return _texture;
    }

    /**
     * To get the address of the SDL_Texture pointer.
     * @warning When using this function, you should have known what you are doing. You can make changes to the private pointer, which may lead to memory leak.
     * @return The address of the SDL_Texture pointer.
     */
    SDL_Texture** Texture::GetAddress() noexcept {
        return &_texture;
    }

    SDL_Texture* Texture::operator*() const noexcept {
        return _texture;
    }

    SDL_Texture* Texture::operator->() const noexcept {
        return _texture;
    }

    Texture Texture::CreateTexture(Renderer& renderer, Uint32 format, int access, int w, int h) {
        return SDL_CreateTexture(*renderer, format, access, w, h);
    }

    Texture Texture::CreateTextureFromSurface(Renderer& renderer, Surface& surface) {
        return SDL_CreateTextureFromSurface(*renderer, *surface);
    }

    void Texture::Query(Uint32& format, int& access, int& w, int& h) {
        if (SDL_QueryTexture(_texture, &format, &access, &w, &h)) throw error::SDLTextureError();
    }

    void Texture::SetColorMod(Uint8 r, Uint8 g, Uint8 b) {
        if (SDL_SetTextureColorMod(_texture, r, g, b)) throw error::SDLTextureError();
    }

    void Texture::GetColorMod(Uint8& r, Uint8& g, Uint8& b) {
        if (SDL_GetTextureColorMod(_texture, &r, &g, &b)) throw error::SDLTextureError();
    }

    void Texture::SetAlphaMod(Uint8 alpha) {
        if (SDL_SetTextureAlphaMod(_texture, alpha)) throw error::SDLTextureError();
    }

    void Texture::GetAlphaMod(Uint8& alpha) {
        if (SDL_GetTextureAlphaMod(_texture, &alpha)) throw error::SDLTextureError();
    }

    void Texture::SetBlendMode(SDL_BlendMode blendMode) {
        if (SDL_SetTextureBlendMode(_texture, blendMode)) throw error::SDLTextureError();
    }

    void Texture::GetBlendMode(SDL_BlendMode& blendMode) {
        if (SDL_GetTextureBlendMode(_texture, &blendMode)) throw error::SDLTextureError();
    }

    void Texture::SetScaleMode(SDL_ScaleMode scaleMode) {
        if (SDL_SetTextureScaleMode(_texture, scaleMode)) throw error::SDLTextureError();
    }

    void Texture::GetScaleMode(SDL_ScaleMode& scaleMode) {
        if (SDL_GetTextureScaleMode(_texture, &scaleMode)) throw error::SDLTextureError();
    }

    void Texture::SetUserData(void* userdata) {
        if (SDL_SetTextureUserData(_texture, userdata)) throw error::SDLTextureError();
    }

    void* Texture::GetUserData() {
        return SDL_GetTextureUserData(_texture);
    }

    void Texture::Update(const Rect& rect, const void* pixels, int pitch) {
        if (SDL_UpdateTexture(_texture, &rect, pixels, pitch)) throw error::SDLTextureError();
    }

    void Texture::Update(std::nullptr_t rect, const void* pixels, int pitch) {
        if (SDL_UpdateTexture(_texture, rect, pixels, pitch)) throw error::SDLTextureError();
    }

    void Texture::UpdateYUVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch) {
        if (SDL_UpdateYUVTexture(_texture, &rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch)) throw error::SDLTextureError();
    }

    void Texture::UpdateNVTexture(const Rect& rect, const Uint8* Yplane, int Ypitch, const Uint8* UVplane, int UVpitch) {
        if (SDL_UpdateNVTexture(_texture, &rect, Yplane, Ypitch, UVplane, UVpitch)) throw error::SDLTextureError();
    }

    void Texture::UpdateYUVTexture(std::nullptr_t rect, const Uint8* Yplane, int Ypitch, const Uint8* Uplane, int Upitch, const Uint8* Vplane, int Vpitch) {
        if (SDL_UpdateYUVTexture(_texture, rect, Yplane, Ypitch, Uplane, Upitch, Vplane, Vpitch)) throw error::SDLTextureError();
    }

    void Texture::UpdateNVTexture(std::nullptr_t rect, const Uint8* Yplane, int Ypitch, const Uint8* UVplane, int UVpitch) {
        if (SDL_UpdateNVTexture(_texture, rect, Yplane, Ypitch, UVplane, UVpitch)) throw error::SDLTextureError();
    }

    void Texture::Lock(const Rect& rect, void*& pixels, int& pitch) {
        if (SDL_LockTexture(_texture, &rect, &pixels, &pitch)) throw error::SDLTextureError();
    }

    void Texture::LockToSurface(const Rect& rect, Surface& surface) {
        if (SDL_LockTextureToSurface(_texture, &rect, &surface.GetHandler())) throw error::SDLTextureError();
    }

    void Texture::Unlock() {
        SDL_UnlockTexture(_texture);
    }

    void Texture::GL_BindTexture(float* texw, float* texh) {
        if (SDL_GL_BindTexture(_texture, texw, texh)) throw error::SDLTextureError();
    }

    void Texture::GL_UnbindTexture() {
        if (SDL_GL_UnbindTexture(_texture)) throw error::SDLTextureError();
    }
}

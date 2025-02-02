/**
  * @file   CSDL_Surface.cpp
  * @author 0And1Story
  * @date   2024-02-29
  * @brief  
  */

#include "CSDL_Surface.h"

#include "CSDL_error.h"

namespace CSDL::SDL {
    Surface::Surface(SDL_Surface* SDL_surface): _surface(SDL_surface) {}

    Surface::Surface(Uint32 flags, int width, int height, int depth,
                     Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask):
        _surface(SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask)) {}

    Surface::Surface(void* pixels, int width, int height, int depth, int pitch,
                     Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask):
        _surface(SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask)) {}

    Surface::~Surface() {
        SDL_FreeSurface(_surface);
    }

    Surface::Surface(Surface&& other) noexcept : _surface(other._surface) {
        other._surface = nullptr;
    }

    Surface& Surface::operator=(Surface&& other) noexcept {
        if (std::addressof(other) == this) return *this;
        SDL_FreeSurface(_surface);
        _surface = other._surface;
        other._surface = nullptr;
        return *this;
    }

    SDL_Surface* Surface::GetHandler() const noexcept {
        return _surface;
    }

    SDL_Surface*& Surface::GetHandler() noexcept {
        return _surface;
    }

    /**
     * To get the address of the SDL_Surface pointer.
     * @warning When using this function, you should have known what you are doing. You can make changes to the private pointer, which may lead to memory leak.
     * @return The address of the SDL_Surface pointer.
     */
    SDL_Surface** Surface::GetAddress() noexcept {
        return &_surface;
    }

    SDL_Surface* Surface::operator*() const noexcept {
        return _surface;
    }

    SDL_Surface* Surface::operator->() const noexcept {
        return _surface;
    }

    Surface Surface::CreateRGBSurface(Uint32 flags, int width, int height, int depth,
                                      Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
        return SDL_CreateRGBSurface(flags, width, height, depth, Rmask, Gmask, Bmask, Amask);
    }

    Surface Surface::CreateRGBSurfaceFrom(void* pixels, int width, int height, int depth, int pitch,
                                          Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask) {
        return SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, Rmask, Gmask, Bmask, Amask);
    }

    Surface Surface::CreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format) {
        return SDL_CreateRGBSurfaceWithFormat(flags, width, height, depth, format);
    }

    Surface Surface::CreateRGBSurfaceWithFormatFrom(void* pixels, int width, int height, int depth, int pitch, Uint32 format) {
        return SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, format);
    }

    Surface Surface::LoadBMP(const char* file) {
        return SDL_LoadBMP(file);
    }

    Surface Surface::LoadBMP_RW(SDL_RWops* src, int freesrc) {
        return SDL_LoadBMP_RW(src, freesrc);
    }

    Surface Surface::LoadBMPFromMem(void* mem, size_t size) {
        return SDL_LoadBMP_RW(SDL_RWFromConstMem(mem, size), 1);
    }

    void Surface::SaveBMP(const char* file) {
        if (SDL_SaveBMP(_surface, file)) throw error::SDLSurfaceError();
    }

    void Surface::Lock() const {
        if (SDL_LockSurface(_surface)) throw error::SDLSurfaceError();
    }

    void Surface::Unlock() const {
        SDL_UnlockSurface(_surface);
    }

    bool Surface::MustLock() const {
        return SDL_MUSTLOCK(_surface);
    }

    void Surface::Blit(const Surface& src, const Rect& srcrect, const Surface& dst, const Rect& dstrect) {
        SDL_BlitSurface(src._surface, const_cast<Rect*>(&srcrect), dst._surface, const_cast<Rect*>(&dstrect));
    }

    void Surface::Blit(const Surface& src, std::nullptr_t srcrect, const Surface& dst, const Rect& dstrect) {
        SDL_BlitSurface(src._surface, srcrect, dst._surface, const_cast<Rect*>(&dstrect));
    }

    void Surface::Blit(const Surface& src, const Rect& srcrect, const Surface& dst, std::nullptr_t dstrect) {
        SDL_BlitSurface(src._surface, const_cast<Rect*>(&srcrect), dst._surface, dstrect);
    }

    void Surface::Blit(const Surface& src, std::nullptr_t srcrect, const Surface& dst, std::nullptr_t dstrect) {
        SDL_BlitSurface(src._surface, srcrect, dst._surface, dstrect);
    }

    void Surface::BlitScaled(const Surface& src, const Rect& srcrect, const Surface& dst, const Rect& dstrect) {
        SDL_BlitSurface(src._surface, const_cast<Rect*>(&srcrect), dst._surface, const_cast<Rect*>(&dstrect));
    }

    void Surface::BlitScaled(const Surface& src, std::nullptr_t srcrect, const Surface& dst, const Rect& dstrect) {
        SDL_BlitSurface(src._surface, srcrect, dst._surface, const_cast<Rect*>(&dstrect));
    }

    void Surface::BlitScaled(const Surface& src, const Rect& srcrect, const Surface& dst, std::nullptr_t dstrect) {
        SDL_BlitSurface(src._surface, const_cast<Rect*>(&srcrect), dst._surface, dstrect);
    }

    void Surface::BlitScaled(const Surface& src, std::nullptr_t srcrect, const Surface& dst, std::nullptr_t dstrect) {
        SDL_BlitSurface(src._surface, srcrect, dst._surface, dstrect);
    }

    Surface Surface::Convert(const SDL_PixelFormat& fmt, Uint32 flags) const {
        SDL_Surface* dst = SDL_ConvertSurface(_surface, &fmt, flags);
        if (dst == nullptr) throw error::SDLSurfaceError();
        return dst;
    }

    Surface Surface::Convert(const Surface& src, const SDL_PixelFormat& fmt, Uint32 flags) {
        SDL_Surface* dst = SDL_ConvertSurface(src._surface, &fmt, flags);
        if (dst == nullptr) throw error::SDLSurfaceError();
        return dst;
    }

    Surface Surface::ConvertFormat(Uint32 pixel_format, Uint32 flags) const {
        SDL_Surface* dst = SDL_ConvertSurfaceFormat(_surface, pixel_format, flags);
        if (dst == nullptr) throw error::SDLSurfaceError();
        return dst;
    }

    Surface Surface::ConvertFormat(const Surface& src, Uint32 pixel_format, Uint32 flags) {
        SDL_Surface* dst = SDL_ConvertSurfaceFormat(src._surface, pixel_format, flags);
        if (dst == nullptr) throw error::SDLSurfaceError();
        return dst;
    }

    void Surface::SetRLE(int flag) {
        if (SDL_SetSurfaceRLE(_surface, flag)) throw error::SDLSurfaceError();
    }

    bool Surface::HasRLE() {
        return SDL_HasSurfaceRLE(_surface);
    }

    void Surface::SetColorKey(int flag, Uint32 key) {
        if (SDL_SetColorKey(_surface, flag, key)) throw error::SDLSurfaceError();
    }

    bool Surface::HasColorKey() {
        return SDL_HasColorKey(_surface);
    }

    Uint32 Surface::GetColorKey() {
        Uint32 key;
        if (SDL_GetColorKey(_surface, &key)) throw error::SDLSurfaceError();
        return key;
    }

    void Surface::SetPalette(SDL_Palette* palette) {
        if (SDL_SetSurfacePalette(_surface, palette)) throw error::SDLSurfaceError();
    }

    void Surface::SetColorMod(Uint8 r, Uint8 g, Uint8 b) {
        if (SDL_SetSurfaceColorMod(_surface, r, g, b)) throw error::SDLSurfaceError();
    }

    void Surface::GetColorMod(Uint8& r, Uint8& g, Uint8& b) {
        if (SDL_GetSurfaceColorMod(_surface, &r, &g, &b)) throw error::SDLSurfaceError();
    }

    void Surface::SetAlphaMod(Uint8 alpha) {
        if (SDL_SetSurfaceAlphaMod(_surface, alpha)) throw error::SDLSurfaceError();
    }

    Uint8 Surface::GetAlphaMod() {
        Uint8 alpha;
        if (SDL_GetSurfaceAlphaMod(_surface, &alpha)) throw error::SDLSurfaceError();
        return alpha;
    }

    void Surface::SetBlendMode(SDL_BlendMode blendMode) {
        if (SDL_SetSurfaceBlendMode(_surface, blendMode)) throw error::SDLSurfaceError();
    }

    SDL_BlendMode Surface::GetBlendMode() {
        SDL_BlendMode blendMode;
        if (SDL_GetSurfaceBlendMode(_surface, &blendMode)) throw error::SDLSurfaceError();
        return blendMode;
    }

    bool Surface::SetClipRect(const Rect& rect) {
        return SDL_SetClipRect(_surface, &rect);
    }

    Rect Surface::GetClipRect() {
        Rect rect;
        SDL_GetClipRect(_surface, &rect);
        return rect;
    }

    Surface Surface::DuplicateSurface() const noexcept {
        return SDL_DuplicateSurface(_surface);
    }

    void Surface::FillRect(const Rect& rect, Uint32 color) {
        if (SDL_FillRect(_surface, &rect, color)) throw error::SDLSurfaceError();
    }

    void Surface::FillRects(const Rect* rects, int count, Uint32 color) {
        if (SDL_FillRects(_surface, rects, count, color)) throw error::SDLSurfaceError();
    }

    void Surface::SoftStretch(Surface& src, const Rect& srcrect, Surface& dst, const Rect& dstrect) {
        if (SDL_SoftStretch(src._surface, &srcrect, dst._surface, &dstrect)) throw error::SDLSurfaceError();
    }

    void Surface::SoftStretchLinear(Surface& src, const Rect& srcrect, Surface& dst, const Rect& dstrect) {
        if (SDL_SoftStretchLinear(src._surface, &srcrect, dst._surface, &dstrect)) throw error::SDLSurfaceError();
    }
}

/**
  * @file   CSDL_Surface.h
  * @author 0And1Story
  * @date   2024-02-29
  * @brief  
  */

#ifndef _CSDL_SURFACE_H_
#define _CSDL_SURFACE_H_

#include "SDL.h"

#include "CSDL_Rect.h"

#include <cstddef>

namespace CSDL::SDL {
    class Surface {
    private:
        SDL_Surface* _surface;

    public:
        Surface(SDL_Surface* SDL_surface);
        Surface(Uint32 flags, int width, int height, int depth,
                Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
        Surface(void* pixels, int width, int height, int depth, int pitch,
                Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
        ~Surface();

        Surface(Surface&& other) noexcept;
        Surface(const Surface&) = delete;
        Surface& operator=(Surface&& other) noexcept;
        Surface& operator=(const Surface&) = delete;

        [[nodiscard]] SDL_Surface* GetHandler() const noexcept;
        [[nodiscard]] SDL_Surface*& GetHandler() noexcept;
        [[nodiscard]] SDL_Surface** GetAddress() noexcept;

        SDL_Surface* operator*() const noexcept;
        SDL_Surface* operator->() const noexcept;

        [[nodiscard]] static Surface CreateRGBSurface(Uint32 flags, int width, int height, int depth,
                                        Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
        [[nodiscard]] static Surface CreateRGBSurfaceFrom(void* pixels, int width, int height, int depth, int pitch,
                                            Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask);
        [[nodiscard]] static Surface CreateRGBSurfaceWithFormat(Uint32 flags, int width, int height, int depth, Uint32 format);
        [[nodiscard]] static Surface CreateRGBSurfaceWithFormatFrom(void* pixels, int width, int height, int depth, int pitch, Uint32 format);

        [[nodiscard]] static Surface LoadBMP(const char* file);
        [[nodiscard]] static Surface LoadBMP_RW(SDL_RWops *src, int freesrc);
        [[nodiscard]] static Surface LoadBMPFromMem(void* mem, size_t size);
        void SaveBMP(const char* file);

        void Lock() const;
        void Unlock() const;
        [[nodiscard]] bool MustLock() const;

        static void Blit(const Surface& src, const Rect& srcrect, const Surface& dst, const Rect& dstrect);
        static void Blit(const Surface& src, std::nullptr_t srcrect, const Surface& dst, const Rect& dstrect);
        static void Blit(const Surface& src, const Rect& srcrect, const Surface& dst, std::nullptr_t dstrect);
        static void Blit(const Surface& src, std::nullptr_t srcrect, const Surface& dst, std::nullptr_t dstrect);
        static void BlitScaled(const Surface& src, const Rect& srcrect, const Surface& dst, const Rect& dstrect);
        static void BlitScaled(const Surface& src, std::nullptr_t srcrect, const Surface& dst, const Rect& dstrect);
        static void BlitScaled(const Surface& src, const Rect& srcrect, const Surface& dst, std::nullptr_t dstrect);
        static void BlitScaled(const Surface& src, std::nullptr_t srcrect, const Surface& dst, std::nullptr_t dstrect);

        [[nodiscard]] Surface Convert(const SDL_PixelFormat& fmt, Uint32 flags) const;
        [[nodiscard]] static Surface Convert(const Surface& src, const SDL_PixelFormat& fmt, Uint32 flags);
        [[nodiscard]] Surface ConvertFormat(Uint32 pixel_format, Uint32 flags) const;
        [[nodiscard]] static Surface ConvertFormat(const Surface& src, Uint32 pixel_format, Uint32 flags);

        void SetRLE(int flag);
        [[nodiscard]] bool HasRLE();

        void SetColorKey(int flag, Uint32 key);
        [[nodiscard]] bool HasColorKey();
        [[nodiscard]] Uint32 GetColorKey();

        void SetPalette(SDL_Palette* palette);

        void SetColorMod(Uint8 r, Uint8 g, Uint8 b);
        void GetColorMod(Uint8& r, Uint8& g, Uint8& b);
        void SetAlphaMod(Uint8 alpha);
        [[nodiscard]] Uint8 GetAlphaMod();
        void SetBlendMode(SDL_BlendMode blendMode);
        [[nodiscard]] SDL_BlendMode GetBlendMode();

        bool SetClipRect(const Rect& rect);
        [[nodiscard]] Rect GetClipRect();

        [[nodiscard]] Surface DuplicateSurface() const noexcept;

        void FillRect(const Rect& rect, Uint32 color);
        void FillRects(const Rect* rects, int count, Uint32 color);

        static void SoftStretch(Surface& src, const Rect& srcrect, Surface& dst, const Rect& dstrect);
        static void SoftStretchLinear(Surface& src, const Rect& srcrect, Surface& dst, const Rect& dstrect);
    };
}

#endif //_CSDL_SURFACE_H_

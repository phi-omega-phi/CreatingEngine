/**
  * @file   CSDL_Renderer.cpp
  * @author 0And1Story
  * @date   2024-05-03
  * @brief  
  */

#include "CSDL_Renderer.h"
#include "CSDL_Texture.h"

#include "CSDL_error.h"

namespace CSDL::SDL {
    Renderer::Renderer(SDL_Renderer* renderer): _renderer(renderer) {}

    Renderer::Renderer(Window& window, int index, Uint32 flags) {
        _renderer = SDL_CreateRenderer(window.GetHandler(), index, flags);
    }

    Renderer::Renderer(Surface& surface) {
        _renderer = SDL_CreateSoftwareRenderer(surface.GetHandler());
    }

    Renderer::~Renderer() {
        SDL_DestroyRenderer(_renderer);
    }

    Renderer::Renderer(Renderer&& other) noexcept : _renderer(other._renderer) {
        other._renderer = nullptr;
    }

    Renderer& Renderer::operator=(Renderer&& other) noexcept {
        if (std::addressof(other) == this) return *this;
        SDL_DestroyRenderer(_renderer);
        _renderer = other._renderer;
        other._renderer = nullptr;
        return *this;
    }

    SDL_Renderer* Renderer::GetHandler() const noexcept {
        return _renderer;
    }

    SDL_Renderer* Renderer::operator*() const noexcept {
        return _renderer;
    }

    SDL_Renderer* Renderer::operator->() const noexcept {
        return _renderer;
    }

    Renderer Renderer::CreateRenderer(const Window& window, int index, Uint32 flags) {
        return SDL_CreateRenderer(window.GetHandler(), index, flags);
    }

    Renderer Renderer::CreateSoftwareRenderer(const Surface& surface) {
        return SDL_CreateSoftwareRenderer(surface.GetHandler());
    }

    Window Renderer::GetWindow() {
        return SDL_RenderGetWindow(_renderer);
    }

    void Renderer::GetRendererInfo(SDL_RendererInfo* info) {
        if (SDL_GetRendererInfo(_renderer, info)) throw error::SDLRenderError();
    }

    void Renderer::GetRendererOutputSize(int& w, int& h) {
        if (SDL_GetRendererOutputSize(_renderer, &w, &h)) throw error::SDLRenderError();
    }

    int Renderer::GetNumRenderDrivers() {
        return SDL_GetNumRenderDrivers();
    }

    void Renderer::GetRenderDriverInfo(int index, SDL_RendererInfo* info) {
        if (SDL_GetRenderDriverInfo(index, info)) throw error::SDLRenderError();
    }

    bool Renderer::RenderTargetSupported() {
        return SDL_RenderTargetSupported(_renderer);
    }

    void Renderer::SetRenderTarget(Texture& texture) {
        if (SDL_SetRenderTarget(_renderer, texture.GetHandler())) throw error::SDLRenderError();
    }

    Texture Renderer::GetRenderTarget() {
        return SDL_GetRenderTarget(_renderer);
    }

    void Renderer::SetLogicalSize(int w, int h) {
        if (SDL_RenderSetLogicalSize(_renderer, w, h)) throw error::SDLRenderError();
    }

    void Renderer::GetLogicalSize(int& w, int& h) {
        SDL_RenderGetLogicalSize(_renderer, &w, &h);
    }

    void Renderer::SetIntegerScale(bool enable) {
        if (SDL_RenderSetIntegerScale(_renderer, static_cast<SDL_bool>(enable))) throw error::SDLRenderError();
    }

    bool Renderer::GetIntegerScale() {
        return SDL_RenderGetIntegerScale(_renderer);
    }

    void Renderer::SetViewport(const Rect& rect) {
        if (SDL_RenderSetViewport(_renderer, &rect)) throw error::SDLRenderError();
    }

    Rect Renderer::GetViewport() {
        Rect rect;
        SDL_RenderGetViewport(_renderer, &rect);
        return rect;
    }

    void Renderer::SetClipRect(const Rect& rect) {
        if (SDL_RenderSetClipRect(_renderer, &rect)) throw error::SDLRenderError();
    }

    Rect Renderer::GetClipRect() {
        Rect rect;
        SDL_RenderGetClipRect(_renderer, &rect);
        return rect;
    }

    bool Renderer::IsClipEnabled() {
        return SDL_RenderIsClipEnabled(_renderer);
    }

    void Renderer::SetScale(float scaleX, float scaleY) {
        if (SDL_RenderSetScale(_renderer, scaleX, scaleY)) throw error::SDLRenderError();
    }

    void Renderer::GetScale(float& scaleX, float& scaleY) {
        SDL_RenderGetScale(_renderer, &scaleX, &scaleY);
    }

    void Renderer::WindowToLogical(int windowX, int windowY, float& logicalX, float& logicalY) {
        SDL_RenderWindowToLogical(_renderer, windowX, windowY, &logicalX, &logicalY);
    }

    void Renderer::LogicalToWindow(float logicalX, float logicalY, int& windowX, int& windowY) {
        SDL_RenderLogicalToWindow(_renderer, logicalX, logicalY, &windowX, &windowY);
    }

    void Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        if (SDL_SetRenderDrawColor(_renderer, r, g, b, a)) throw error::SDLRenderError();
    }

    void Renderer::GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a) {
        if (SDL_GetRenderDrawColor(_renderer, &r, &g, &b, &a)) throw error::SDLRenderError();
    }

    void Renderer::SetDrawBlendMode(SDL_BlendMode blendMode) {
        if (SDL_SetRenderDrawBlendMode(_renderer, blendMode)) throw error::SDLRenderError();
    }

    void Renderer::GetDrawBlendMode(SDL_BlendMode& blendMode) {
        if (SDL_GetRenderDrawBlendMode(_renderer, &blendMode)) throw error::SDLRenderError();
    }

    void Renderer::Clear() {
        if (SDL_RenderClear(_renderer)) throw error::SDLRenderError();
    }

    void Renderer::DrawPoint(int x, int y) {
        if (SDL_RenderDrawPoint(_renderer, x, y)) throw error::SDLRenderError();
    }

    void Renderer::DrawPoints(const Point* points, int count) {
        if (SDL_RenderDrawPoints(_renderer, points, count)) throw error::SDLRenderError();
    }

    void Renderer::DrawLine(int x1, int y1, int x2, int y2) {
        if (SDL_RenderDrawLine(_renderer, x1, y1, x2, y2)) throw error::SDLRenderError();
    }

    void Renderer::DrawLines(const Point* points, int count) {
        if (SDL_RenderDrawLines(_renderer, points, count)) throw error::SDLRenderError();
    }

    void Renderer::DrawRect(const Rect& rect) {
        if (SDL_RenderDrawRect(_renderer, &rect)) throw error::SDLRenderError();
    }

    void Renderer::DrawRects(const Rect* rects, int count) {
        if (SDL_RenderDrawRects(_renderer, rects, count)) throw error::SDLRenderError();
    }

    void Renderer::FillRect(const Rect& rect) {
        if (SDL_RenderFillRect(_renderer, &rect)) throw error::SDLRenderError();
    }

    void Renderer::FillRects(const Rect* rects, int count) {
        if (SDL_RenderFillRects(_renderer, rects, count)) throw error::SDLRenderError();
    }

    void Renderer::Copy(Texture& texture, const Rect& srcrect, const Rect& dstrect) {
        if (SDL_RenderCopy(_renderer, *texture, &srcrect, &dstrect)) throw error::SDLRenderError();
    }

    void Renderer::Copy(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect) {
        if (SDL_RenderCopy(_renderer, *texture, srcrect, &dstrect)) throw error::SDLRenderError();
    }

    void Renderer::Copy(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect) {
        if (SDL_RenderCopy(_renderer, *texture, &srcrect, dstrect)) throw error::SDLRenderError();
    }

    void Renderer::Copy(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect) {
        if (SDL_RenderCopy(_renderer, *texture, srcrect, dstrect)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, const Rect& srcrect, const Rect& dstrect, double angle, const Point& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, &srcrect, &dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, const Rect& srcrect, const Rect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, &srcrect, &dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, const Point& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, &srcrect, dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, &srcrect, dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect, double angle, const Point& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, srcrect, &dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, srcrect, &dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, const Point& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, srcrect, dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyEx(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyEx(_renderer, *texture, srcrect, dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::DrawPointF(float x, float y) {
        if (SDL_RenderDrawPointF(_renderer, x, y)) throw error::SDLRenderError();
    }

    void Renderer::DrawPointsF(const FPoint* points, int count) {
        if (SDL_RenderDrawPointsF(_renderer, points, count)) throw error::SDLRenderError();
    }

    void Renderer::DrawLineF(float x1, float y1, float x2, float y2) {
        if (SDL_RenderDrawLineF(_renderer, x1, y1, x2, y2)) throw error::SDLRenderError();
    }

    void Renderer::DrawLinesF(const FPoint* points, int count) {
        if (SDL_RenderDrawLinesF(_renderer, points, count)) throw error::SDLRenderError();
    }

    void Renderer::DrawRectF(const FRect& rect) {
        if (SDL_RenderDrawRectF(_renderer, &rect)) throw error::SDLRenderError();
    }

    void Renderer::DrawRectsF(const FRect* rects, int count) {
        if (SDL_RenderDrawRectsF(_renderer, rects, count)) throw error::SDLRenderError();
    }

    void Renderer::FillRectF(const FRect& rect) {
        if (SDL_RenderFillRectF(_renderer, &rect)) throw error::SDLRenderError();
    }

    void Renderer::FillRectsF(const FRect* rects, int count) {
        if (SDL_RenderFillRectsF(_renderer, rects, count)) throw error::SDLRenderError();
    }

    void Renderer::CopyF(Texture& texture, const Rect& srcrect, const FRect& dstrect) {
        if (SDL_RenderCopyF(_renderer, *texture, &srcrect, &dstrect)) throw error::SDLRenderError();
    }

    void Renderer::CopyF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect) {
        if (SDL_RenderCopyF(_renderer, *texture, &srcrect, dstrect)) throw error::SDLRenderError();
    }

    void Renderer::CopyF(Texture& texture, std::nullptr_t srcrect, const FRect& dstrect) {
        if (SDL_RenderCopyF(_renderer, *texture, srcrect, &dstrect)) throw error::SDLRenderError();
    }

    void Renderer::CopyF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect) {
        if (SDL_RenderCopyF(_renderer, *texture, srcrect, dstrect)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, const Rect& srcrect, const SDL_FRect& dstrect, double angle, const FPoint& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, &srcrect, &dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, const Rect& srcrect, const SDL_FRect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, &srcrect, &dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, const FPoint& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, &srcrect, dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, &srcrect, dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, std::nullptr_t srcrect, const SDL_FRect& dstrect, double angle, const FPoint& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, srcrect, &dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, std::nullptr_t srcrect, const SDL_FRect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, srcrect, &dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, const FPoint& center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, srcrect, dstrect, angle, &center, flip)) throw error::SDLRenderError();
    }

    void Renderer::CopyExF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip) {
        if (SDL_RenderCopyExF(_renderer, *texture, srcrect, dstrect, angle, center, flip)) throw error::SDLRenderError();
    }

    void Renderer::Geometry(Texture& texture, const Vertex* vertices, int num_vertices, const int* indices, int num_indices) {
        if (SDL_RenderGeometry(_renderer, *texture, vertices, num_vertices, indices, num_indices)) throw error::SDLRenderError();
    }

    void
    Renderer::GeometryRaw(Texture& texture, const float* xy, int xy_stride, const SDL_Color* color, int color_stride, const float* uv, int uv_stride, int num_vertices, const void* indices, int num_indices, int size_indices) {
        if (SDL_RenderGeometryRaw(_renderer, *texture, xy, xy_stride, color, color_stride, uv, uv_stride, num_vertices, indices, num_indices, size_indices)) throw error::SDLRenderError();
    }

    void Renderer::ReadPixels(const Rect& rect, Uint32 format, void* pixels, int pitch) {
        if (SDL_RenderReadPixels(_renderer, &rect, format, pixels, pitch)) throw error::SDLRenderError();
    }

    void Renderer::Present() {
        SDL_RenderPresent(_renderer);
    }

    void Renderer::Flush() {
        SDL_RenderFlush(_renderer);
    }

    void Renderer::SetVSync(int vsync) {
        if (SDL_RenderSetVSync(_renderer, vsync)) throw error::SDLRenderError();
    }
}

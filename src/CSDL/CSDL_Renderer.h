/**
  * @file   CSDL_Renderer.h
  * @author 0And1Story
  * @date   2024-05-03
  * @brief  
  */

#ifndef _CSDL_RENDERER_H_
#define _CSDL_RENDERER_H_

#include "SDL.h"

#include "CSDL_Window.h"

namespace CSDL::SDL {
    class Texture;

    using Vertex = SDL_Vertex;

    class Renderer {
    private:
        SDL_Renderer* _renderer;

    public:
        Renderer(SDL_Renderer* renderer);
        Renderer(Window& window, int index, Uint32 flags);
        explicit Renderer(Surface& surface);
        ~Renderer();

        Renderer(Renderer&& other) noexcept;
        Renderer(const Renderer&) = delete;
        Renderer& operator=(Renderer&& other) noexcept;
        Renderer& operator=(const Renderer&) = delete;

        [[nodiscard]] SDL_Renderer* GetHandler() const noexcept;

        SDL_Renderer* operator*() const noexcept;
        SDL_Renderer* operator->() const noexcept;

        static Renderer CreateRenderer(const Window& window, int index, Uint32 flags);
        static Renderer CreateSoftwareRenderer(const Surface& surface);

        Window GetWindow();

        void GetRendererInfo(SDL_RendererInfo* info);
        void GetRendererOutputSize(int& w, int& h);
        static int GetNumRenderDrivers();
        static void GetRenderDriverInfo(int index, SDL_RendererInfo* info);

        bool RenderTargetSupported();
        void SetRenderTarget(Texture& texture);
        Texture GetRenderTarget();

        void SetLogicalSize(int w, int h);
        void GetLogicalSize(int& w, int& h);
        void SetIntegerScale(bool enable);
        bool GetIntegerScale();
        void SetViewport(const Rect& rect);
        Rect GetViewport();
        void SetClipRect(const Rect& rect);
        Rect GetClipRect();
        bool IsClipEnabled();
        void SetScale(float scaleX, float scaleY);
        void GetScale(float& scaleX, float& scaleY);

        void WindowToLogical(int windowX, int windowY, float& logicalX, float& logicalY);
        void LogicalToWindow(float logicalX, float logicalY, int& windowX, int& windowY);

        void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void GetDrawColor(Uint8& r, Uint8& g, Uint8& b, Uint8& a);
        void SetDrawBlendMode(SDL_BlendMode blendMode);
        void GetDrawBlendMode(SDL_BlendMode& blendMode);

        void Clear();
        void DrawPoint(int x, int y);
        void DrawPoints(const Point* points, int count);
        void DrawLine(int x1, int y1, int x2, int y2);
        void DrawLines(const Point* points, int count);
        void DrawRect(const Rect& rect);
        void DrawRects(const Rect* rects, int count);
        void FillRect(const Rect& rect);
        void FillRects(const Rect* rects, int count);
        void Copy(Texture& texture, const Rect& srcrect, const Rect& dstrect);
        void Copy(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect);
        void Copy(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect);
        void Copy(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect);
        void CopyEx(Texture& texture, const Rect& srcrect, const Rect& dstrect, double angle, const Point& center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, const Rect& srcrect, const Rect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, const Point& center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect, double angle, const Point& center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, std::nullptr_t srcrect, const Rect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, const Point& center, SDL_RendererFlip flip);
        void CopyEx(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void DrawPointF(float x, float y);
        void DrawPointsF(const FPoint* points, int count);
        void DrawLineF(float x1, float y1, float x2, float y2);
        void DrawLinesF(const FPoint* points, int count);
        void DrawRectF(const FRect& rect);
        void DrawRectsF(const FRect* rects, int count);
        void FillRectF(const FRect& rect);
        void FillRectsF(const FRect* rects, int count);
        void CopyF(Texture& texture, const Rect& srcrect, const FRect& dstrect);
        void CopyF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect);
        void CopyF(Texture& texture, std::nullptr_t srcrect, const FRect& dstrect);
        void CopyF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect);
        void CopyExF(Texture& texture, const Rect& srcrect, const SDL_FRect& dstrect, double angle, const FPoint& center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, const Rect& srcrect, const SDL_FRect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, const FPoint& center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, const Rect& srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, std::nullptr_t srcrect, const SDL_FRect& dstrect, double angle, const FPoint& center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, std::nullptr_t srcrect, const SDL_FRect& dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, const FPoint& center, SDL_RendererFlip flip);
        void CopyExF(Texture& texture, std::nullptr_t srcrect, std::nullptr_t dstrect, double angle, std::nullptr_t center, SDL_RendererFlip flip);
        void Geometry(Texture& texture, const Vertex* vertices, int num_vertices, const int* indices, int num_indices);
        void GeometryRaw(Texture& texture, const float* xy, int xy_stride, const SDL_Color* color, int color_stride, const float* uv, int uv_stride, int num_vertices, const void* indices, int num_indices, int size_indices);
        void ReadPixels(const Rect& rect, Uint32 format, void* pixels, int pitch);

        void Present();
        void Flush();

        void SetVSync(int vsync);
    };
}

#endif //_CSDL_RENDERER_H_

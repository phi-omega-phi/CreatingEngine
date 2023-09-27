/**
  * @file   SDL_Motion.h
  * @author 0And1Story
  * @date   2023-09-13
  * @brief  
  */

#ifndef _SDL_MOTION_H_
#define _SDL_MOTION_H_

#include "SDL_Widget.h"
#include "SDL_Const.h"
#include "SDL_Setting.h"
#include "SDL_Texture.h"
#include "SDL_ResourceReader.h"
#include "SDL.h"

#define SDL_CreateMotion(...) new SDL_Motion(__VA_ARGS__)
#define SDL_DestroyMotion(motion) delete motion

typedef SDL_Point (*MOTION_FUNC)(Uint32 ticks, void* param);

class SDL_Motion : public SDL_Widget {
private:
    SDL_TextureEx* _texture;
    MOTION_FUNC _MotionFunc;
    void* _motion_param;
    SDL_Point _position;
    Uint32 _duration;
    Uint32 _flush_interval;
    SDL_TimerID _timer_id = -1;
    Uint32 _start = 0;
    Uint32 _now = 0;
    bool _repeat;
    bool _reverse;
    bool _alternate;

public:
    SDL_Motion(SDL_TextureEx* texture_, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_ = nullptr, const int& x = 0, const int& y = 0, const bool& repeat_ = false, const bool& reverse_ = false, const bool& alternate_ = false);
    SDL_Motion(const char* texture_path_, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_ = nullptr, const int& x = 0, const int& y = 0, const bool& repeat_ = false, const bool& reverse_ = false, const bool& alternate_ = false);
    SDL_Motion(SDL_ResourceID texture_id, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_ = nullptr, const int& x = 0, const int& y = 0, const bool& repeat_ = false, const bool& reverse_ = false, const bool& alternate_ = false);

    ~SDL_Motion() override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void SetRenderPosition(const int& x_, const int& y_) override;
    void SetRenderPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetRenderPosition() const override;

    void Render() override;

    void Play();
    void Stop();
    void Pause();
    void Continue();

    void Reset();

    void Reverse();

    void SetFlushInterval(Uint32 flush_interval_);
    [[nodiscard]] Uint32 GetFlushInterval() const;

    void SetReverse(bool reverse_);
    [[nodiscard]] bool GetReverse() const;

    void SetRepeat(bool repeat_);
    [[nodiscard]] bool GetRepeat() const;

    void SetAlternate(bool alternate_);
    [[nodiscard]] bool GetAlternate() const;
};

#endif //_SDL_MOTION_H_

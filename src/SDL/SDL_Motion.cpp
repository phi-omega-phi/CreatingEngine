/**
  * @file   SDL_Motion.cpp
  * @author 0And1Story
  * @date   2023-09-22
  * @brief  
  */
#include "SDL_Motion.h"
#include "SDL_Texture.h"

SDL_Motion::SDL_Motion(SDL_TextureEx* texture_, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_, const int& x, const int& y, const bool& repeat_, const bool& reverse_, const bool& alternate_):
        _texture(texture_), _MotionFunc(MotionFunc_), _motion_param(motion_param_), _position(x, y), _duration(duration_), _flush_interval(interval_), _repeat(repeat_), _reverse(reverse_), _alternate(alternate_) {}

SDL_Motion::SDL_Motion(const char* texture_path_, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_, const int& x, const int& y, const bool& repeat_, const bool& reverse_, const bool& alternate_):
        _texture(new SDL_TextureEx(texture_path_)), _MotionFunc(MotionFunc_), _motion_param(motion_param_), _position(x, y), _duration(duration_), _flush_interval(interval_), _repeat(repeat_), _reverse(reverse_), _alternate(alternate_) {}

SDL_Motion::SDL_Motion(SDL_ResourceID texture_id, Uint32 duration_, Uint32 interval_, MOTION_FUNC MotionFunc_, void* motion_param_, const int& x, const int& y, const bool& repeat_, const bool& reverse_, const bool& alternate_):
        _texture(new SDL_TextureEx(texture_id)), _MotionFunc(MotionFunc_), _motion_param(motion_param_), _position(x, y), _duration(duration_), _flush_interval(interval_), _repeat(repeat_), _reverse(reverse_), _alternate(alternate_) {}

SDL_Motion::~SDL_Motion() {
    if (_timer_id != -1) Stop();
    delete _texture;
}

void SDL_Motion::SetPosition(const int& x_, const int& y_) {
    _position.x = x_;
    _position.y = y_;
}

void SDL_Motion::SetPosition(const SDL_Point& position_) {
    _position.x = position_.x;
    _position.y = position_.y;
}

[[nodiscard]] SDL_Point SDL_Motion::GetPosition() const {
    return _position;
}

void SDL_Motion::Render() {
    _texture->Render();
}

void SDL_Motion::Play() {
    _start = SDL_GetTicks();
    _timer_id = SDL_AddTimer(_flush_interval, [](Uint32 interval, void* param)->Uint32 {
        ((SDL_Motion*)param)->_now = SDL_GetTicks() - ((SDL_Motion*)param)->_start;
        if (((SDL_Motion*)param)->_now  > ((SDL_Motion*)param)->_duration) {
            if (!((SDL_Motion*)param)->_repeat) return 0;
            if (((SDL_Motion*)param)->_alternate) ((SDL_Motion*)param)->_reverse = !((SDL_Motion*)param)->_reverse;
            ((SDL_Motion*)param)->_start += ((SDL_Motion*)param)->_duration;
            return interval;
        }
        if (!((SDL_Motion*)param)->_reverse) ((SDL_Motion*)param)->_texture->SetPosition(((SDL_Motion*)param)->_position + ((SDL_Motion*)param)->_MotionFunc(((SDL_Motion*)param)->_now, ((SDL_Motion*)param)->_motion_param));
        else ((SDL_Motion*)param)->_texture->SetPosition(((SDL_Motion*)param)->_position + ((SDL_Motion*)param)->_MotionFunc(((SDL_Motion*)param)->_duration - ((SDL_Motion*)param)->_now, ((SDL_Motion*)param)->_motion_param));
        SDL_Event event;
        event.type = SDL_USER_RENDER;
        SDL_PushEvent(&event);
        return interval;
    }, this);
}

void SDL_Motion::Stop() {
    if (_timer_id == -1) return;
    SDL_RemoveTimer(_timer_id);
    _timer_id = -1;
    _now = 0;
}

void SDL_Motion::Pause() {
    if (_timer_id == -1) return;
    SDL_RemoveTimer(_timer_id);
    _timer_id = -1;
}

void SDL_Motion::Continue() {
    _start = SDL_GetTicks() - _now;
    _timer_id = SDL_AddTimer(_flush_interval, [](Uint32 interval, void* param)->Uint32 {
        ((SDL_Motion*)param)->_now = SDL_GetTicks() - ((SDL_Motion*)param)->_start;
        if (((SDL_Motion*)param)->_now  > ((SDL_Motion*)param)->_duration) {
            if (!((SDL_Motion*)param)->_repeat) return 0;
            if (((SDL_Motion*)param)->_alternate) ((SDL_Motion*)param)->_reverse = !((SDL_Motion*)param)->_reverse;
            ((SDL_Motion*)param)->_start += ((SDL_Motion*)param)->_duration;
            return interval;
        }
        if (!((SDL_Motion*)param)->_reverse) ((SDL_Motion*)param)->_texture->SetPosition(((SDL_Motion*)param)->_position + ((SDL_Motion*)param)->_MotionFunc(((SDL_Motion*)param)->_now, ((SDL_Motion*)param)->_motion_param));
        else ((SDL_Motion*)param)->_texture->SetPosition(((SDL_Motion*)param)->_position + ((SDL_Motion*)param)->_MotionFunc(((SDL_Motion*)param)->_duration - ((SDL_Motion*)param)->_now, ((SDL_Motion*)param)->_motion_param));
        SDL_Event event;
        event.type = SDL_USER_RENDER;
        SDL_PushEvent(&event);
        return interval;
    }, this);
}

void SDL_Motion::Reset() {
    _now = 0;
}

void SDL_Motion::Reverse() {
    _reverse = !_reverse;
    _start += _now - (_duration - _now);
}

void SDL_Motion::SetFlushInterval(Uint32 flush_interval_) {
    _flush_interval = flush_interval_;
}

[[nodiscard]] Uint32 SDL_Motion::GetFlushInterval() const {
    return _flush_interval;
}

void SDL_Motion::SetReverse(bool reverse_) {
    if (_reverse == reverse_) return;
    _reverse = reverse_;
    _start += _now - (_duration - _now);
}

[[nodiscard]] bool SDL_Motion::GetReverse() const {
    return _reverse;
}

void SDL_Motion::SetRepeat(bool repeat_) {
    _repeat = repeat_;
}

[[nodiscard]] bool SDL_Motion::GetRepeat() const {
    return _repeat;
}

void SDL_Motion::SetAlternate(bool alternate_) {
    _alternate = alternate_;
}

[[nodiscard]] bool SDL_Motion::GetAlternate() const {
    return _alternate;
}

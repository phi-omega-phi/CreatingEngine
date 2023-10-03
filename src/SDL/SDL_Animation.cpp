/**
  * @file   SDL_Animation.cpp
  * @author 0And1Story
  * @date   2023-09-22
  * @brief  
  */
#include "SDL_Animation.h"

SDL_Animation::SDL_Animation(const Uint32& interval_, const int& x_, const int& y_, const bool& repeat_, const bool& reverse_):
        _frames(), _current_frame(), _interval(interval_), _position(x_, y_), _repeat(repeat_), _reverse(reverse_) {}

SDL_Animation::SDL_Animation(const Uint32& interval_, ::std::initializer_list<SDL_TextureEx*> init_, const int& x_, const int& y_, const bool& repeat_, const bool& reverse_):
        _frames(init_), _current_frame(_frames.begin()), _interval(interval_), _position(x_, y_), _repeat(repeat_), _reverse(reverse_) {}

SDL_Animation::~SDL_Animation() {
    if (_timer_id != -1) Stop();
    for (SDL_TextureEx* frame : _frames) {
        delete frame;
    }
}

void SDL_Animation::SetPosition(const int& x_, const int& y_) {
    for (SDL_TextureEx* frame : _frames) {
        SDL_Point prev_position = frame->GetPosition();
        frame->SetPosition(prev_position.x - _position.x + x_, prev_position.y - _position.y + y_);
    }
    _position.x = x_;
    _position.y = y_;
}

void SDL_Animation::SetPosition(const SDL_Point& position_) {
    for (SDL_TextureEx* frame : _frames) {
        SDL_Point prev_position = frame->GetPosition();
        frame->SetPosition(prev_position.x - _position.x + position_.x, prev_position.y - _position.y + position_.y);
    }
    _position = position_;
}

[[nodiscard]] SDL_Point SDL_Animation::GetPosition() const {
    return _position;
}

void SDL_Animation::Render() {
    (*_current_frame)->Render();
}

void SDL_Animation::AddFrame(SDL_TextureEx* frame_) {
    frame_->SetPosition(frame_->GetPosition() + _position);
    _frames.push_back(frame_);
}

void SDL_Animation::AddFrame(const char* frame_path_) {
    auto frame_ = new SDL_TextureEx(frame_path_);
    frame_->SetPosition(frame_->GetPosition() + _position);
    _frames.push_back(frame_);
}

void SDL_Animation::AddFrame(SDL_ResourceID frame_id) {
    auto frame_ = new SDL_TextureEx(frame_id);
    frame_->SetPosition(frame_->GetPosition() + _position);
    _frames.push_back(frame_);
}

void SDL_Animation::PushBack(SDL_TextureEx* frame_) {
    frame_->SetPosition(frame_->GetPosition() + _position);
    _frames.push_back(frame_);
}

void SDL_Animation::PushFront(SDL_TextureEx* frame_) {
    frame_->SetPosition(frame_->GetPosition() + _position);
    _frames.push_front(frame_);
}

void SDL_Animation::PopBack() {
    _frames.pop_back();
}

void SDL_Animation::PopFront() {
    _frames.pop_front();
}

void SDL_Animation::ResetFrame() {
    _current_frame = _frames.begin();
}

void SDL_Animation::NextFrame() {
    if (!_reverse) {
        ++_current_frame;
        if (_current_frame == _frames.end()) {
            _current_frame = _frames.begin();
            ++_play_count;
        }
    } else {
        if (_current_frame == _frames.begin()) {
            _current_frame = _frames.end();
            ++_play_count;
        }
        --_current_frame;
    }
}

[[nodiscard]] bool SDL_Animation::Finished() const {
    return _play_count;
}

[[nodiscard]] int SDL_Animation::GetPlayCount() const {
    return _play_count;
}

void SDL_Animation::ResetPlayCount() {
    _play_count = 0;
}

void SDL_Animation::Play(bool reset_) {
    if (_timer_id != -1) return;
    if (reset_) ResetFrame();
    _timer_id = SDL_AddTimer(_interval, [](Uint32 interval, void* param)->Uint32 {
        if (!((SDL_Animation*)param)->_repeat && ((SDL_Animation*)param)->Finished()) return 0;
        ((SDL_Animation*)param)->NextFrame();
        SDL_Event event;
        event.type = SDL_USER_RENDER;
        SDL_PushEvent(&event);
        return interval;
    }, this);
}

void SDL_Animation::Stop() {
    if (_timer_id == -1) return;
    SDL_RemoveTimer(_timer_id);
    _timer_id = -1;
    ResetFrame();
}

void SDL_Animation::Pause() {
    if (_timer_id == -1) return;
    SDL_RemoveTimer(_timer_id);
    _timer_id = -1;
}

void SDL_Animation::Continue() {
    if (_timer_id != -1) return;
    _timer_id = SDL_AddTimer(_interval, [](Uint32 interval, void* param)->Uint32 {
        if (!((SDL_Animation*)param)->_repeat && ((SDL_Animation*)param)->Finished()) return 0;
        ((SDL_Animation*)param)->NextFrame();
        SDL_Event event;
        event.type = SDL_USER_RENDER;
        SDL_PushEvent(&event);
        return interval;
    }, this);
}

void SDL_Animation::Reverse() {
    _reverse = !_reverse;
}

void SDL_Animation::SetInterval(Uint32 interval_) {
    _interval = interval_;
}

[[nodiscard]] Uint32 SDL_Animation::GetInterval() const {
    return _interval;
}

void SDL_Animation::SetReverse(bool reverse_) {
    _reverse = reverse_;
}

[[nodiscard]] bool SDL_Animation::GetReverse() const {
    return _reverse;
}

void SDL_Animation::SetRepeat(bool repeat_) {
    _repeat = repeat_;
}

[[nodiscard]] bool SDL_Animation::GetRepeat() const {
    return _repeat;
}

/**
  * @file   SDL_Animation.h
  * @author 0And1Story
  * @date   2023-09-08
  * @brief  The Animation Module.
  */

#ifndef _SDL_ANIMATION_H_
#define _SDL_ANIMATION_H_

#include "SDL.h"
#include "SDL_Widget.h"
#include "SDL_Texture.h"
#include "SDL_Const.h"
#include "SDL_Setting.h"
#include <list>

#define SDL_CreateAnimation(...) new SDL_Animation(__VA_ARGS__)
#define SDL_DestroyAnimation(animation) delete animation

class SDL_Animation : public SDL_Widget {
private:
    ::std::list<SDL_TextureEx*> _frames;
    ::std::list<SDL_TextureEx*>::iterator _current_frame;
    Uint32 _interval;
    SDL_TimerID _timer_id = -1;
    SDL_Point _position;
    int _play_count = 0;
    bool _repeat;
    bool _reverse;

public:
    explicit SDL_Animation(const Uint32& interval_, const int& x_ = 0, const int& y_ = 0, const bool& repeat_ = false, const bool& reverse_ = false);
    SDL_Animation(const Uint32& interval_, ::std::list<SDL_TextureEx*>& frames_, const int& x_ = 0, const int& y_ = 0, const bool& repeat_ = false, const bool& reverse_ = false);
    template<class InputIt>
    SDL_Animation(const Uint32& interval_, const InputIt& first_, const InputIt& last_, const int& x_ = 0, const int& y_ = 0, const bool& repeat_ = false, const bool& reverse_ = false);
    SDL_Animation(const Uint32& interval_, ::std::initializer_list<SDL_TextureEx*> init_, const int& x_ = 0, const int& y_ = 0, const bool& repeat_ = false, const bool& reverse_ = false);
    SDL_Animation(const Uint32& interval_, ::std::list<SDL_TextureEx*>&& frames_, const int& x_ = 0, const int& y_ = 0, const bool& repeat_ = false, const bool& reverse_ = false);

    ~SDL_Animation() override;

    void SetPosition(const int& x_, const int& y_) override;
    void SetPosition(const SDL_Point& position_) override;
    [[nodiscard]] SDL_Point GetPosition() const override;

    void Render() override;

    void AddFrame(SDL_TextureEx* frame_);
    void AddFrame(const char* frame_path_);
    void AddFrame(SDL_ResourceID frame_id);

    void PushBack(SDL_TextureEx* frame_);
    void PushFront(SDL_TextureEx* frame_);
    void PopBack();
    void PopFront();

    void ResetFrame();

    void NextFrame();

    [[nodiscard]] bool Finished() const;

    [[nodiscard]] int GetPlayCount() const;

    void ResetPlayCount();

    void Play(bool reset_ = true);
    void Stop();
    void Pause();
    void Continue();
    void Reverse();

    void SetInterval(Uint32 interval_);
    [[nodiscard]] Uint32 GetInterval() const;

    void SetReverse(bool reverse_);
    [[nodiscard]] bool GetReverse() const;

    void SetRepeat(bool repeat_);
    [[nodiscard]] bool GetRepeat() const;
};

#endif //_SDL_ANIMATION_H_

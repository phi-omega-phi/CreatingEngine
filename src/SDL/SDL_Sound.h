/**
  * @file   SDL_Sound.h
  * @author 0And1Story
  * @date   2023-11-06
  * @brief  The Audio System.
  */

#ifndef _SDL_SOUND_H_
#define _SDL_SOUND_H_

#include "SDL_mixer.h"

#include "SDL_ResourceReader.h"

class __SDL_Sound {
private:
    Mix_Music* _music = nullptr;
    bool is_playing = false;

private:
    __SDL_Sound() = default;
    ~__SDL_Sound() = default;

public:
    __SDL_Sound(const __SDL_Sound&) = delete;
    const __SDL_Sound& operator=(const __SDL_Sound&) = delete;

    static __SDL_Sound& Instance();

    bool LoadMusic(SDL_ResourceID id);
    void FreeMusic();
    void PlayMusic();
    void StopMusic();
    void PauseMusic();
    void ContinueMusic();
    void RewindMusic();
    void FadeInMusic(int ms);
    void FadeOutMusic(int ms);

    void PlayChunk(SDL_ResourceID id);

    bool PlayingMusic();
};

extern __SDL_Sound& SDL_Sound;

#endif //_SDL_SOUND_H_

/**
  * @file   SDL_Sound.cpp
  * @author 0And1Story
  * @date   2023-11-06
  * @brief  The Audio System.
  */

#include "SDL_Sound.h"

#include "SDL.h"

#include "SDL_Global.h"

__SDL_Sound& __SDL_Sound::Instance() {
    static  __SDL_Sound instance;
    return instance;
}

void __SDL_Sound::LoadMusic(SDL_ResourceID id) {
    Mix_Music* music = global.LoadMusic(id);
    if (_music == music) return;
    _music = music;
    Mix_RewindMusic();
}

void __SDL_Sound::FreeMusic() {
    _music = nullptr;
}

void __SDL_Sound::PlayMusic() {
    if (_music == nullptr) return;
    Mix_PlayMusic(_music, -1);
}

void __SDL_Sound::StopMusic() {
    Mix_HaltMusic();
    Mix_RewindMusic();
}

void __SDL_Sound::PauseMusic() {
    Mix_PauseMusic();
}

void __SDL_Sound::ContinueMusic() {
    Mix_ResumeMusic();
}

void __SDL_Sound::RewindMusic() {
    Mix_RewindMusic();
}

void __SDL_Sound::FadeInMusic(int ms) {
    Mix_FadeInMusic(_music, -1, ms);
}

void __SDL_Sound::FadeOutMusic(int ms) {
    Mix_FadeOutMusic(ms);
}

void __SDL_Sound::PlayChunk(SDL_ResourceID id) {
    Mix_Chunk* chunk = SDL_ResourceReader.LoadChunk(id);
    Mix_PlayChannel(-1, chunk, 1);
}

__SDL_Sound& SDL_Sound = __SDL_Sound::Instance();

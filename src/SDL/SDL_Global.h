/**
  * @file   SDL_Global.h
  * @author 0And1Story
  * @date   2023-09-10
  * @brief  
  */

#ifndef _SDL_GLOBAL_H_
#define _SDL_GLOBAL_H_

#include <unordered_map>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_ResourceReader.h"
#include "XML_Parser.h"

class SDL_Layer;
class SDL_Animation;

class SC_GamePlay;

class __SDL_Global {
private:
    __SDL_Global() = default;
    ~__SDL_Global() = default;

private:
    ::std::vector<SDL_Layer*> _layer_stack;

public:
    bool is_quit;
    bool is_render;
    SDL_Layer* current_layer;
    SC_GamePlay* game_play;
    ::std::unordered_map<SDL_ResourceID, TTF_Font*> fonts;
    ::std::unordered_map<SDL_ResourceID, Mix_Music*> musics;
    ::std::unordered_map<SDL_ResourceID, SDL_Layer*> layers;

public:
    __SDL_Global(const __SDL_Global&) = delete;
    const __SDL_Global& operator=(const __SDL_Global&) = delete;

    static __SDL_Global& Instance();

    TTF_Font* LoadFont(SDL_ResourceID id);
    Mix_Music* LoadMusic(SDL_ResourceID id);
    SDL_Layer* LoadLayerFromXML(SDL_ResourceID id);

    void PushLayer(SDL_Layer* layer);
    void PopLayer();
};

extern __SDL_Global& global;

#endif //_SDL_GLOBAL_H_

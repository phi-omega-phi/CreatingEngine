/**
  * @file   SDL_Global.cpp
  * @author 0And1Story
  * @date   2023-09-27
  * @brief  
  */
#include "SDL_Global.h"
#include "SDL_Layer.h"

__SDL_Global& __SDL_Global::Instance() {
    static __SDL_Global instance;
    return instance;
}

__SDL_Global& global = __SDL_Global::Instance();

TTF_Font* __SDL_Global::LoadFont(SDL_ResourceID id) {
    if (fonts.contains(id)) return fonts[id];
    return fonts[id] = SDL_ResourceReader.LoadFont(id);
}

SDL_Layer* __SDL_Global::LoadLayerFromXML(SDL_ResourceID id) {
    if (layers.contains(id)) return layers[id];
    void* source = SDL_ResourceReader.LoadText(id);
    auto root = DOM::XMLParser((const char*)source);
    SDL_ResourceReader.FreeResource(source);
    return layers[id] = SDL_Layer::CreateLayerFromXML(root);
}

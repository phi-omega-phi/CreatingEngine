/**
  * @file   SDL_ResourceReader.h
  * @author 0And1Story
  * @date   2023-09-15
  * @brief  
  */

#ifndef _SDL_RESOURCE_READER_H_
#define _SDL_RESOURCE_READER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <dirent.h>
#include <list>
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_FileLog.h"

typedef int SDL_ResourceID;

class __SDL_ResourceReader {
private:
    struct Package {
        FILE* fp;
        int file_count;
        uint64_t* offset;
    };
    struct ResourceInfo {
        void* buffer;
        uint64_t file_size;
        FILE* fp;
    };
    ::std::list<Package> _pack_list;
    ::std::vector<::std::string> _index_list;
    int _file_count = 0;

private:
    __SDL_ResourceReader();
    ~__SDL_ResourceReader();

public:
    __SDL_ResourceReader(const __SDL_ResourceReader&) = delete;
    const __SDL_ResourceReader& operator=(const __SDL_ResourceReader&) = delete;

    static __SDL_ResourceReader& Instance();

    SDL_ResourceID GetResourceID(const char* file_path);

    uint64_t GetResourceSize(SDL_ResourceID id);

    void* LoadResource(SDL_ResourceID id);
    void LoadResource(SDL_ResourceID id, ResourceInfo& info);

    void FreeResource(void* buffer);

    void* LoadText(SDL_ResourceID id);

    SDL_Surface* LoadBMP(SDL_ResourceID id);
    SDL_Surface* LoadImage(SDL_ResourceID id);

    TTF_Font* LoadFont(SDL_ResourceID id);

    Mix_Music* LoadMusic(SDL_ResourceID id);
    Mix_Chunk* LoadChunk(SDL_ResourceID id);
};

extern __SDL_ResourceReader& SDL_ResourceReader;

#endif //_SDL_RESOURCE_READER_H_

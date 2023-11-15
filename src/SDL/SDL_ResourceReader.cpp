/**
  * @file   SDL_ResourceReader.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "SDL_ResourceReader.h"

__SDL_ResourceReader::__SDL_ResourceReader(): _pack_list(), _index_list() {
    FILE* _fp_index = fopen("index.txt", "r");
    if (_fp_index != nullptr) {
        char* strbuf = (char*)malloc(PATH_MAX * sizeof(char));
        _index_list.emplace_back("");

        while (fgets(strbuf, PATH_MAX, _fp_index)) {
            strbuf[strlen(strbuf) - 1] = '\0';
            if (strbuf[0] == ':') continue;
            _index_list.emplace_back(strbuf);
        }

        free(strbuf);
    }
    DIR* p_dir = opendir(".");
    struct dirent* p_dirent;
    while ((p_dirent = readdir(p_dir)) != nullptr) {
        size_t len = strlen(p_dirent->d_name);
        if (strlen(p_dirent->d_name) < 4 || p_dirent->d_name[0] == '.' || p_dirent->d_name[len - 4] != '.' || p_dirent->d_name[len - 3] != 'c' || p_dirent->d_name[len - 2] != 's' || p_dirent->d_name[len - 1] != 'p') continue;
        Package pack{};
        pack.fp = fopen(p_dirent->d_name, "rb");
        fread(&pack.file_count, sizeof(int), 1, pack.fp);
        pack.offset = (uint64_t*)malloc(sizeof(uint64_t) * (pack.file_count + 1));
        pack.offset[0] = 0;
        fread(pack.offset + 1, sizeof(uint64_t), pack.file_count, pack.fp);
        _file_count += pack.file_count;
        _pack_list.push_back(pack);
    }
}

__SDL_ResourceReader::~__SDL_ResourceReader() {
    for (Package& pack : _pack_list) {
        fclose(pack.fp);
    }
}

__SDL_ResourceReader& __SDL_ResourceReader::Instance() {
    static __SDL_ResourceReader instance;
    return instance;
}

SDL_ResourceID __SDL_ResourceReader::GetResourceID(const char* file_path) {
    auto it = std::find(_index_list.begin(), _index_list.end(), file_path);

    if (it == _index_list.end()) {
        SDL_FileCritical("Failed to get ResourceID: {}", file_path);
        return -1;
    }

    return it - _index_list.begin();
}

uint64_t __SDL_ResourceReader::GetResourceSize(SDL_ResourceID id) {
    if (id < 1 || id > _file_count) {
        SDL_FileCritical("Get Resource Size Failed. ID: {}", id);
        return 0;
    }
    for (Package& pack : _pack_list) {
        if (id > pack.file_count) {
            id -= pack.file_count;
            continue;
        }
        return pack.offset[id] - pack.offset[id - 1];
    }
    return 0;
}

void* __SDL_ResourceReader::LoadResource(SDL_ResourceID id) {
    if (id < 1 || id > _file_count) {
        SDL_FileCritical("Load Resource Failed. ID: {}", id);
        return nullptr;
    }
    for (Package& pack : _pack_list) {
        if (id > pack.file_count) {
            id -= pack.file_count;
            continue;
        }
        void* buffer = malloc(pack.offset[id] - pack.offset[id - 1] + 1);
        fseeko64(pack.fp,  sizeof(int) + sizeof(uint64_t) * pack.file_count + pack.offset[id - 1], SEEK_SET);
        fread(buffer, 1, pack.offset[id] - pack.offset[id - 1], pack.fp);
        return buffer;
    }
    return nullptr;
}

void __SDL_ResourceReader::LoadResource(SDL_ResourceID id, __SDL_ResourceReader::ResourceInfo& info) {
    if (id < 1 || id > _file_count) {
        SDL_FileCritical("Load Resource Failed. ID: {}", id);
        info.buffer = nullptr;
        return;
    }
    for (Package& pack : _pack_list) {
        if (id > pack.file_count) {
            id -= pack.file_count;
            continue;
        }
        void* buffer = malloc(pack.offset[id] - pack.offset[id - 1] + 1);
        fseeko64(pack.fp,  sizeof(int) + sizeof(uint64_t) * pack.file_count + pack.offset[id - 1], SEEK_SET);
        fread(buffer, 1, pack.offset[id] - pack.offset[id - 1], pack.fp);
        info.buffer = buffer;
        info.file_size = pack.offset[id] - pack.offset[id - 1];
        info.fp = pack.fp;
        return;
    }
    info.buffer = nullptr;
}

void __SDL_ResourceReader::FreeResource(void* buffer) {
    free(buffer);
}

void* __SDL_ResourceReader::LoadText(SDL_ResourceID id) {
    if (id < 1 || id > _file_count) {
        SDL_FileCritical("Load Resource Failed. ID: {}", id);
        return nullptr;
    }
    for (Package& pack : _pack_list) {
        if (id > pack.file_count) {
            id -= pack.file_count;
            continue;
        }
        void* buffer = malloc(pack.offset[id] - pack.offset[id - 1] + 1);
        fseeko64(pack.fp,  sizeof(int) + sizeof(uint64_t) * pack.file_count + pack.offset[id - 1], SEEK_SET);
        fread(buffer, 1, pack.offset[id] - pack.offset[id - 1], pack.fp);
        ((uint8_t*)buffer)[pack.offset[id] - pack.offset[id - 1]] = 0;
        return buffer;
    }
    return nullptr;
}

SDL_Surface* __SDL_ResourceReader::LoadBMP(SDL_ResourceID id) {
    ResourceInfo info{};
    LoadResource(id, info);
    SDL_Surface* surface = SDL_LoadBMP_RW(SDL_RWFromConstMem(info.buffer, info.file_size), 1);
    free(info.buffer);
    return surface;
}

SDL_Surface* __SDL_ResourceReader::LoadImage(SDL_ResourceID id) {
    ResourceInfo info{};
    LoadResource(id, info);
    SDL_Surface* surface = IMG_Load_RW(SDL_RWFromConstMem(info.buffer, info.file_size), 1);
    free(info.buffer);
    return surface;
}

TTF_Font* __SDL_ResourceReader::LoadFont(SDL_ResourceID id) {
    ResourceInfo info{};
    LoadResource(id, info);
    TTF_Font* font = TTF_OpenFontRW(SDL_RWFromConstMem(info.buffer, info.file_size), 1, 0);
    return font;
}

Mix_Music* __SDL_ResourceReader::LoadMusic(SDL_ResourceID id) {
    ResourceInfo info{};
    LoadResource(id, info);
    Mix_Music* music = Mix_LoadMUS_RW(SDL_RWFromConstMem(info.buffer, info.file_size), 1);
    return music;
}

Mix_Chunk* __SDL_ResourceReader::LoadChunk(SDL_ResourceID id) {
    ResourceInfo info{};
    LoadResource(id, info);
    Mix_Chunk* chunk = Mix_LoadWAV_RW(SDL_RWFromConstMem(info.buffer, info.file_size), 1);
    return chunk;
}

__SDL_ResourceReader& SDL_ResourceReader = __SDL_ResourceReader::Instance();

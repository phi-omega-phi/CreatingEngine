/**
  * @file   SDL_Global.h
  * @author 0And1Story
  * @date   2023-09-10
  * @brief  
  */

#ifndef _SDL_GLOBAL_H_
#define _SDL_GLOBAL_H_

class __SDL_Global {
private:
    __SDL_Global() = default;
    ~__SDL_Global() = default;

public:
    bool is_quit;
    bool is_render;

public:
    __SDL_Global(const __SDL_Global&) = delete;
    const __SDL_Global& operator=(const __SDL_Global&) = delete;

    static __SDL_Global& Instance() {
        static __SDL_Global instance;
        return instance;
    }
};

__SDL_Global& global = __SDL_Global::Instance();

#endif //_SDL_GLOBAL_H_
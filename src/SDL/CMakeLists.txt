add_library(SDL)

target_sources(
        SDL
    PUBLIC
        SDL_Widget.h
        SDL_Const.h
        SDL_Setting.h
        SDL_Global.h
        SDL_FileLog.h
        SDL_ResourceReader.h
        SDL_Texture.h
        SDL_Button.h
        SDL_Layer.h
        SDL_Animation.h
        SDL_Motion.h
        SDL_Text.h
        SDL_OverflowWidget.h
    PRIVATE
        SDL_Const.cpp
        SDL_Setting.cpp
        SDL_Global.cpp
        SDL_FileLog.cpp
        SDL_ResourceReader.cpp
        SDL_Texture.cpp
        SDL_Button.cpp
        SDL_Layer.cpp
        SDL_Animation.cpp
        SDL_Motion.cpp
        SDL_Text.cpp
        SDL_OverflowWidget.cpp
)

target_include_directories(SDL PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(SDL PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)
target_link_libraries(SDL PRIVATE Parser)

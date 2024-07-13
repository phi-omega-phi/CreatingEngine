add_library(CSDL)

target_sources(
        CSDL
    PUBLIC
        CSDL.h
        CSDL_SDL.h
        CSDL_IMG.h
        CSDL_TTF.h
        CSDL_MIX.h
        CSDL_Window.h
        CSDL_Surface.h
        CSDL_Renderer.h
        CSDL_Texture.h
        CSDL_Rect.h
        CSDL_error.h
    PRIVATE
        CSDL.cpp
        CSDL_SDL.cpp
        CSDL_IMG.cpp
        CSDL_TTF.cpp
        CSDL_MIX.cpp
        CSDL_Window.cpp
        CSDL_Surface.cpp
        CSDL_Renderer.cpp
        CSDL_Texture.cpp
        CSDL_Rect.cpp
        CSDL_error.cpp
)

target_include_directories(CSDL PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(CSDL PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)

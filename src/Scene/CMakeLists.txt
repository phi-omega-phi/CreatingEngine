add_library(Scene)

target_sources(
        Scene
    PUBLIC
        SC_GamePlay.h
    PRIVATE
        SC_GamePlay.cpp
)

target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(Scene PRIVATE SDL)
target_link_libraries(Scene PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf)
target_link_libraries(Scene PRIVATE Parser)
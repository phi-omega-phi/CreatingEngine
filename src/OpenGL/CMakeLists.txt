add_library(OpenGL)

target_sources(
        OpenGL
    PUBLIC
        opengl.h
    PRIVATE
        opengl.cpp
)

target_include_directories(OpenGL PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(OpenGL PRIVATE SDL2::SDL2 SDL2_image::SDL2_image)
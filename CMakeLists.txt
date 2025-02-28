cmake_minimum_required(VERSION 3.25)
project(CreatingEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static")

# Please configure the library paths here.
#file(TO_CMAKE_PATH "$ENV{SDL_ROOT}/x86_64-w64-mingw32" SDL_PATH)
# include_directories("$ENV{BOOST_ROOT}/include/boost-1_82")
# link_directories("$ENV{BOOST_ROOT}/lib")

include("lib/SDL/lib/cmake/SDL2/sdl2-config.cmake")
include("lib/SDL_image/lib/cmake/SDL2_image/sdl2_image-config.cmake")
include("lib/SDL_mixer/lib/cmake/SDL2_mixer/sdl2_mixer-config.cmake")
include("lib/SDL_ttf/lib/cmake/SDL2_ttf/sdl2_ttf-config.cmake")

include_directories("lib/opengl/include")
link_directories("lib/opengl/lib")

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main SDL2::SDL2)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_image::SDL2_image)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_mixer::SDL2_mixer)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2_ttf::SDL2_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 opengl32)
target_sources(${PROJECT_NAME} PRIVATE lib/opengl/src/glad.c)

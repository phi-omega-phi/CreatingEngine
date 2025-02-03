add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(SDL)
add_subdirectory(Parser)
add_subdirectory(FileSystem)
add_subdirectory(Scene)
add_subdirectory(CSDL)

target_link_libraries(
        ${PROJECT_NAME}
    PRIVATE
        SDL
        Parser
        FileSystem
        Scene
)

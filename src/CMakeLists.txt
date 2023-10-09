add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(SDL)
add_subdirectory(Parser)
add_subdirectory(Scene)

target_link_libraries(
        ${PROJECT_NAME}
    PRIVATE
        SDL
        Parser
        Scene
)

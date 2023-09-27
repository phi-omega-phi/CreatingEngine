add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(SDL)
add_subdirectory(Parser)

target_link_libraries(
        ${PROJECT_NAME}
    PRIVATE
        SDL
        Parser
)

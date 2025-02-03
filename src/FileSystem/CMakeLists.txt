add_library(FileSystem)

target_sources(
        FileSystem
    PUBLIC
        DumpFile.h
        SaveSystem.h
    PRIVATE
        DumpFile.cpp
        SaveSystem.cpp
)

target_include_directories(FileSystem PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_library(Parser)

target_sources(
        Parser
    PUBLIC
        XML_Parser.h
    PRIVATE
        XML_Parser.cpp
)

target_include_directories(Parser PUBLIC ${CMAKE_CURRENT_LIST_DIR})
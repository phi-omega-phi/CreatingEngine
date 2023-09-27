/**
  * @file   SDL_FileLog.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "SDL_FileLog.h"

__SDL_FileLog& __SDL_FileLog::Instance() {
    static __SDL_FileLog instance;
    return instance;
}

[[deprecated]] void __SDL_FileLog::SetFile(FILE* fp_) {
    _fp = fp_;
#ifndef NDEBUG
    setbuf(stderr, nullptr);
    setbuf(stdout, nullptr);
    setbuf(_fp, nullptr);
#endif
}

FILE* __SDL_FileLog::OpenFile(const char* file_path_) {
    if (_fp) fclose(_fp);
    _fp = fopen(file_path_, "w");
#ifndef NDEBUG
    setbuf(stderr, nullptr);
    setbuf(stdout, nullptr);
    setbuf(_fp, nullptr);
#endif
    return _fp;
}

void __SDL_FileLog::CloseFile() {
    fclose(_fp);
    _fp = nullptr;
}

void __SDL_FileLog::CreateFileByTime() {
    ::std::chrono::time_point now = ::std::chrono::system_clock::now();
    ::std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    ::std::tm* now_tm = ::std::localtime(&now_t);
    char file_name[PATH_MAX];
    ::std::strftime(file_name, sizeof(file_name), "%Y-%m-%d_%H-%M-%S.log", now_tm);

    if (_fp) fclose(_fp);
    _fp = fopen(file_name, "w");
#ifndef NDEBUG
    setbuf(stderr, nullptr);
    setbuf(stdout, nullptr);
    setbuf(_fp, nullptr);
#endif
}

void __SDL_FileLog::CreateFileByTime(const char* path_) {
    ::std::chrono::time_point now = ::std::chrono::system_clock::now();
    ::std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    ::std::tm* now_tm = ::std::localtime(&now_t);

    if (access(path_, 0)) mkdir(path_);

    char file_name[PATH_MAX];
    strcpy(file_name, path_);
    size_t path_len = strlen(path_);
    file_name[path_len] = '/';
    ::std::strftime(file_name + path_len + 1, sizeof(file_name) - path_len - 1, "%Y-%m-%d_%H-%M-%S.log", now_tm);

    if (_fp) fclose(_fp);
    _fp = fopen(file_name, "w");
#ifndef NDEBUG
    setbuf(stderr, nullptr);
    setbuf(stdout, nullptr);
    setbuf(_fp, nullptr);
#endif
}

const char* __SDL_FileLog::LogLevelType(LogLevel log_level) {
    switch (log_level) {
        case LOG_LEVEL_DEBUG:
            return "Debug";
        case LOG_LEVEL_INFO:
            return "Info";
        case LOG_LEVEL_WARNING:
            return "Warning";
        case LOG_LEVEL_ERROR:
            return "Error";
        case LOG_LEVEL_CRITICAL:
            return "Critical";
        default:
            return nullptr;
    }
    return nullptr;
}

const char* __SDL_FileLog::LogLevelColor(LogLevel log_level) {
    switch (log_level) {
        case LOG_LEVEL_DEBUG:
            return CONSOLE_GREEN;
        case LOG_LEVEL_INFO:
            return CONSOLE_NONE;
        case LOG_LEVEL_WARNING:
            return CONSOLE_MAGENTA;
        case LOG_LEVEL_ERROR:
            return CONSOLE_RED;
        case LOG_LEVEL_CRITICAL:
            return CONSOLE_BOLD CONSOLE_RED;
        default:
            return nullptr;
    }
    return nullptr;
}

void __SDL_FileLog::TimeHeader() {
#ifndef NDEBUG
    if (_is_even) fputs(CONSOLE_THEME_BG_DEFAULT, LOG_OUTPUT);
    fputs(CONSOLE_THEME_DEFAULT, LOG_OUTPUT);
#endif
    ::std::chrono::time_point now = ::std::chrono::system_clock::now();
    ::std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    ::std::tm* now_tm = ::std::localtime(&now_t);
    char time_str[64];
    ::std::strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S] ", now_tm);
    fputs(time_str, _fp);
#ifndef NDEBUG
    fputs(time_str, LOG_OUTPUT);
#endif
}

/// The global instance of SDL_FileLog.
__SDL_FileLog& SDL_FileLog = __SDL_FileLog::Instance();

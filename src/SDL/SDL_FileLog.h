/**
 * @file    SDL_FileLog.h
 * @author  0And1Story
 * @date    2023-7-26
 * @brief   The File Log Module.
 */

#ifndef _SDL_FILELOG_H_
#define _SDL_FILELOG_H_

#include <cstdio>
#include <string>
#include <format>
#include <chrono>
#include <ctime>
#include <dirent.h>

#include "SDL_Const.h"

/**
 * @name    ConsoleColor
 * @brief   The ANSI Escape Codes of console colors.
 * @{
 */
// Color Mode
#define CONSOLE_NONE                ""
#define CONSOLE_CLEAR               "\033[0m"
#define CONSOLE_RESET               "\033[0m"
#define CONSOLE_BOLD                "\033[1m"
#define CONSOLE_HIGHLIGHT           "\033[1m"
#define CONSOLE_DIM                 "\033[2m"
#define CONSOLE_FAINT               "\033[2m"
#define CONSOLE_ITALIC              "\033[3m"
#define CONSOLE_UNDERLINE           "\033[4m"
#define CONSOLE_BLINKING            "\033[5m"
#define CONSOLE_INVERSE             "\033[7m"
#define CONSOLE_REVERSE             "\033[7m"
#define CONSOLE_HIDDEN              "\033[8m"
#define CONSOLE_INVISIBLE           "\033[8m"
#define CONSOLE_DELETE              "\033[9m"
#define CONSOLE_STRIKETHROUGH       "\033[9m"

// Color Mode Reset
#define CONSOLE_BOLD_RESET          "\033[22m"
#define CONSOLE_HIGHLIGHT_RESET     "\033[22m"
#define CONSOLE_DIM_RESET           "\033[22m"
#define CONSOLE_FAINT_RESET         "\033[22m"
#define CONSOLE_ITALIC_RESET        "\033[23m"
#define CONSOLE_UNDERLINE_RESET     "\033[24m"
#define CONSOLE_BLINKING_RESET      "\033[25m"
#define CONSOLE_INVERSE_RESET       "\033[27m"
#define CONSOLE_REVERSE_RESET       "\033[27m"
#define CONSOLE_HIDDEN_RESET        "\033[28m"
#define CONSOLE_INVISIBLE_RESET     "\033[28m"
#define CONSOLE_DELETE_RESET        "\033[29m"
#define CONSOLE_STRIKETHROUGH_RESET "\033[29m"

// Color Codes(Foreground)
#define CONSOLE_DEFAULT             "\033[39m"
#define CONSOLE_BLACK               "\033[30m"
#define CONSOLE_RED                 "\033[31m"
#define CONSOLE_GREEN               "\033[32m"
#define CONSOLE_YELLOW              "\033[33m"
#define CONSOLE_BLUE                "\033[34m"
#define CONSOLE_MAGENTA             "\033[35m"
#define CONSOLE_CYAN                "\033[36m"
#define CONSOLE_WHITE               "\033[37m"
#define CONSOLE_BRIGHT_BLACK        "\033[90m"
#define CONSOLE_BRIGHT_RED          "\033[91m"
#define CONSOLE_BRIGHT_GREEN        "\033[92m"
#define CONSOLE_BRIGHT_YELLOW       "\033[93m"
#define CONSOLE_BRIGHT_BLUE         "\033[94m"
#define CONSOLE_BRIGHT_MAGENTA      "\033[95m"
#define CONSOLE_BRIGHT_CYAN         "\033[96m"
#define CONSOLE_BRIGHT_WHITE        "\033[97m"

// Color Codes(Background)
#define CONSOLE_BG_DEFAULT          "\033[49m"
#define CONSOLE_BG_BLACK            "\033[40m"
#define CONSOLE_BG_RED              "\033[41m"
#define CONSOLE_BG_GREEN            "\033[42m"
#define CONSOLE_BG_YELLOW           "\033[43m"
#define CONSOLE_BG_BLUE             "\033[44m"
#define CONSOLE_BG_MAGENTA          "\033[45m"
#define CONSOLE_BG_CYAN             "\033[46m"
#define CONSOLE_BG_WHITE            "\033[47m"
#define CONSOLE_BG_BRIGHT_BLACK     "\033[100m"
#define CONSOLE_BG_BRIGHT_RED       "\033[101m"
#define CONSOLE_BG_BRIGHT_GREEN     "\033[102m"
#define CONSOLE_BG_BRIGHT_YELLOW    "\033[103m"
#define CONSOLE_BG_BRIGHT_BLUE      "\033[104m"
#define CONSOLE_BG_BRIGHT_MAGENTA   "\033[105m"
#define CONSOLE_BG_BRIGHT_CYAN      "\033[106m"
#define CONSOLE_BG_BRIGHT_WHITE     "\033[107m"

// Color Codes(256 Colors and RGB Colors)
#define CONSOLE_256COLOR(ID)        "\033[38;5;"#ID"m"
#define CONSOLE_BG_256COLOR(ID)     "\033[48;5;"#ID"m"
#define CONSOLE_RGB(r, g, b)        "\033[38;2;"#r";"#g";"#b"m"

#define CONSOLE_ALMOST_WHITE        "\033[38;5;255m"
#define CONSOLE_ALMOST_BLACK        "\033[38;5;232m"
#define CONSOLE_BG_ALMOST_WHITE     "\033[48;5;255m"
#define CONSOLE_BG_ALMOST_BLACK     "\033[48;5;237m"

#if COLOR_THEME == LIGHT_THEME
#define CONSOLE_THEME_DEFAULT       CONSOLE_BLACK
#define CONSOLE_THEME_BG_DEFAULT    CONSOLE_BG_ALMOST_WHITE
#else
#define CONSOLE_THEME_DEFAULT       CONSOLE_BRIGHT_WHITE
#define CONSOLE_THEME_BG_DEFAULT    CONSOLE_BG_ALMOST_BLACK
#endif
/** @} */

/**
 * @name    LogLevelSystem
 * @brief   The log level system.
 * @{
 */
/**
 * @brief   The enum class of log levels.
 * @enum    LogLevel
 */

#define LogLevel    Uint16

#define LOG_LEVEL_DEBUG     1
#define LOG_LEVEL_INFO      2
#define LOG_LEVEL_WARNING   3
#define LOG_LEVEL_ERROR     4
#define LOG_LEVEL_CRITICAL  5

#define SDL_FileDebug(fmt, ...)     SDL_FileLog(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)
#define SDL_FileInfo(fmt, ...)      SDL_FileLog(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
#define SDL_FileWarning(fmt, ...)   SDL_FileLog(LOG_LEVEL_WARNING, __LINE__, __FUNCTION__, __FILE__, fmt, ##__VA_ARGS__)
#define SDL_FileError(fmt, ...)     SDL_FileLog(LOG_LEVEL_ERROR, __LINE__, __FUNCTION__, __FILE__, fmt, ##__VA_ARGS__)
#define SDL_FileCritical(fmt, ...)  SDL_FileLog(LOG_LEVEL_CRITICAL, __LINE__, __FUNCTION__, __FILE__, fmt, ##__VA_ARGS__)

#if LOG_LEVEL > LOG_LEVEL_CRITICAL
#warning "The log level shouldn't be higher than LOG_LEVEL_CRITICAL!"
#endif

#if LOG_LEVEL > LOG_LEVEL_DEBUG
#undef SDL_FileDebug
#define SDL_FileDebug
#endif
#if LOG_LEVEL > LOG_LEVEL_INFO
#undef SDL_FileInfo
#define SDL_FileInfo
#endif
#if LOG_LEVEL > LOG_LEVEL_WARNING
#undef SDL_FileWarning
#define SDL_FileWarning
#endif
#if LOG_LEVEL > LOG_LEVEL_ERROR
#undef SDL_FileError
#define SDL_FileError
#endif
#if LOG_LEVEL > LOG_LEVEL_CRITICAL
#undef SDL_FileCritical
#define SDL_FileCritical
#endif
/** @} */

/**
 * @brief       The Functor SDL_FileLog.
 * @details     Use functor(function object) to output file log.
 * @attention   This is a singleton.\n
 *              It can not be instantiated.\n
 *              Please use @code __SDL_FileLog::instance() @endcode to get the instance of the singleton if necessary,
 *              but there is a global instance called "SDL_FileLog" so we don't recommend.
 * @class       __SDL_FileLog
 */
class __SDL_FileLog {
private:
    FILE* _fp = nullptr;    ///< The pointer of the output file.
    bool _is_even = false;

private:
    __SDL_FileLog() = default;
    ~__SDL_FileLog() = default;

public:
    __SDL_FileLog(const __SDL_FileLog&) = delete;
    const __SDL_FileLog& operator=(const __SDL_FileLog&) = delete;

    static __SDL_FileLog& Instance();

    [[deprecated]] void SetFile(FILE* fp_);

    FILE* OpenFile(const char* file_path_);
    void CloseFile();

    void CreateFileByTime();
    void CreateFileByTime(const char* path_);

    static const char* LogLevelType(LogLevel log_level);
    static const char* LogLevelColor(LogLevel log_level);

    void TimeHeader();

    template<typename ...Args>
    void operator()(::std::string_view fmt, const Args& ...args);
    template<typename ...Args>
    void operator()(LogLevel log_level, ::std::string_view fmt, const Args& ...args);
    template<typename ...Args>
    void operator()(LogLevel log_level, int line, const char* func, const char* file_name, ::std::string_view fmt, const Args& ...args);
};

template<typename ...Args>
void __SDL_FileLog::operator()(::std::string_view fmt, const Args& ...args) {
#ifndef NDEBUG
    fputs(_is_even ? CONSOLE_THEME_BG_DEFAULT : CONSOLE_CLEAR, LOG_OUTPUT);
    fputs(CONSOLE_THEME_DEFAULT, LOG_OUTPUT);
#endif
    TimeHeader();
    ::std::string str = ::std::vformat(fmt, std::make_format_args(args...));
    fputs(str.c_str(), _fp);
    fputc('\n', _fp);
#ifndef NDEBUG
    fputs(str.c_str(), LOG_OUTPUT);
    fputc('\n', LOG_OUTPUT);
#endif
    _is_even = !_is_even;
}

template<typename ...Args>
void __SDL_FileLog::operator()(LogLevel log_level, ::std::string_view fmt, const Args& ...args) {
#ifndef NDEBUG
    fputs(_is_even ? CONSOLE_THEME_BG_DEFAULT : CONSOLE_CLEAR, LOG_OUTPUT);
#endif
    TimeHeader();
    ::std::string str = ::std::vformat(fmt, std::make_format_args(args...));
    fputs(::std::format("[{}] ", LogLevelType(log_level)).c_str(), _fp);
    fputs(str.c_str(), _fp);
    fputc('\n', _fp);
#ifndef NDEBUG
    fputs(::std::format("{}{}[{}]{}{}{} ", CONSOLE_THEME_DEFAULT, LogLevelColor(log_level), LogLevelType(log_level), CONSOLE_CLEAR, _is_even ? CONSOLE_THEME_BG_DEFAULT : "", CONSOLE_THEME_DEFAULT).c_str(), LOG_OUTPUT);
    fputs(str.c_str(), LOG_OUTPUT);
    fputc('\n', LOG_OUTPUT);
#endif
    _is_even = !_is_even;
}

template<typename ...Args>
void __SDL_FileLog::operator()(LogLevel log_level, int line, const char* func, const char* file_name, ::std::string_view fmt, const Args& ...args) {
    fputs(::std::format("[File: {} Line: {}] [At: {}()]\n", file_name, line, func).c_str(), _fp);
#ifndef NDEBUG
    fputs(_is_even ? CONSOLE_THEME_BG_DEFAULT : CONSOLE_CLEAR, LOG_OUTPUT);
    fputs(::std::format("{}[File: {} Line: {}] [At: {}{}(){}]\n", CONSOLE_THEME_DEFAULT, file_name, line, CONSOLE_ITALIC, func, CONSOLE_ITALIC_RESET).c_str(), LOG_OUTPUT);
#endif
    TimeHeader();
    ::std::string str = ::std::vformat(fmt, std::make_format_args(args...));
    fputs(::std::format("[{}] ", LogLevelType(log_level)).c_str(), _fp);
    fputs(str.c_str(), _fp);
    fputc('\n', _fp);
#ifndef NDEBUG
    fputs(::std::format("{}[{}]{}{}{} ", LogLevelColor(log_level), LogLevelType(log_level), CONSOLE_CLEAR, CONSOLE_THEME_DEFAULT, _is_even ? CONSOLE_THEME_BG_DEFAULT : "").c_str(), LOG_OUTPUT);
    fputs(str.c_str(), LOG_OUTPUT);
    fputc('\n', LOG_OUTPUT);
#endif
    _is_even = !_is_even;
}

extern __SDL_FileLog& SDL_FileLog;

#endif //_SDL_FILELOG_H_

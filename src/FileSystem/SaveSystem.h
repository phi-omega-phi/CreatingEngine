/**
  * @file   SaveSystem.h
  * @author 0And1Story
  * @date   2025-02-03
  * @brief  
  */

#ifndef _SAVESYSTEM_H_
#define _SAVESYSTEM_H_

#include <vector>
#include <string>
#include <chrono>

#include "DumpFile.h"

#define THUMBNAIL_FORMAT    SDL_PIXELFORMAT_RGBA8888
#define THUMBNAIL_SCALE     4

class SaveData : DumpRW {
public:
    using Byte = unsigned char;
    using Bytes = std::vector<Byte>;

    class Progress : DumpRW {
    public:
        using ResourceID = int;

        ResourceID file;
        int line;

        void write(const DumpFile& dump) const override;
        void read(const DumpFile& dump) override;
    };

    class Thumbnail : DumpRW {
    public:
        int width, height;
        Bytes pixels;

        void write(const DumpFile &dump) const override;
        void read(const DumpFile &dump) override;
    };

public:
    std::string title;
    std::string chapter;
    std::chrono::system_clock::time_point time;
    Progress progress;
    Thumbnail thumbnail;

public:
    void save(const char* file_name) const;
    void load(const char* file_name);
    static void remove(const char* file_name);

    void write(const DumpFile& dump) const override;
    void read(const DumpFile& dump) override;
};

#endif //_SAVESYSTEM_H_

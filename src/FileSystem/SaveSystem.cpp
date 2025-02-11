/**
  * @file   SaveSystem.cpp
  * @author 0And1Story
  * @date   2025-02-03
  * @brief  
  */

#include <filesystem>

#include "SaveSystem.h"

void SaveData::save(const char* file_name) const {
    DumpFile dump(file_name, DumpFile::Mode::WRITE);
    this->write(dump);
}

void SaveData::load(const char* file_name) {
    DumpFile dump(file_name, DumpFile::Mode::READ);
    this->read(dump);
}

void SaveData::remove(const char* file_name) {
    std::filesystem::remove(file_name);
}

void SaveData::write(const DumpFile& dump) const {
    dump.write(title);
    dump.write(chapter);
    dump.write(std::chrono::system_clock::to_time_t(time));
    progress.write(dump);
    thumbnail.write(dump);
}

void SaveData::read(const DumpFile& dump) {
    dump.read(title);
    dump.read(chapter);
    std::time_t timestamp;
    dump.read(timestamp);
    time = std::chrono::system_clock::from_time_t(timestamp);
    progress.read(dump);
    thumbnail.read(dump);
}

void SaveData::Progress::write(const DumpFile& dump) const {
    dump.write(file);
    dump.write(line);
}

void SaveData::Progress::read(const DumpFile& dump) {
    dump.read(file);
    dump.read(line);
}

void SaveData::Bitmap::write(const DumpFile& dump) const {
    dump.write(width), dump.write(height);
    dump.write(pixels);
}

void SaveData::Bitmap::read(const DumpFile& dump) {
    dump.read(width), dump.read(height);
    dump.read(pixels);
}

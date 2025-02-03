/**
  * @file   DumpFile.cpp
  * @author 0And1Story
  * @date   2025-02-02
  * @brief  
  */

#include "DumpFile.h"


DumpFile::DumpFile() noexcept : _fp(nullptr) {}

DumpFile::DumpFile(const char* file_name, Mode mode) noexcept {
    if (mode == Mode::READ) {
        _fp = fopen(file_name, "rb");
    } else if (mode == Mode::WRITE) {
        _fp = fopen(file_name, "wb");
    }
}

DumpFile::~DumpFile() noexcept {
    if (_fp) fclose(_fp), _fp = nullptr;
}

void DumpFile::open(const char* file_name, DumpFile::Mode mode) {
    if (_fp) fclose(_fp);
    if (mode == Mode::READ) {
        _fp = fopen(file_name, "rb");
    } else if (mode == Mode::WRITE) {
        _fp = fopen(file_name, "wb");
    }
}

void DumpFile::close() {
    if (_fp) fclose(_fp), _fp = nullptr;
}

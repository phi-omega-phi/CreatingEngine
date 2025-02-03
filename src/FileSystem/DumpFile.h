/**
  * @file   DumpFile.h
  * @author 0And1Story
  * @date   2025-02-02
  * @brief  
  */

#ifndef _DUMPFILE_H_
#define _DUMPFILE_H_

#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <concepts>

class DumpFile {
private:
    FILE* _fp;

public:
    enum class Mode { READ, WRITE };

public:
    DumpFile() noexcept;
    explicit DumpFile(const char* file_name, Mode mode) noexcept;
    ~DumpFile() noexcept;

    DumpFile(const DumpFile&) = delete;
    DumpFile(DumpFile&&) = delete;
    DumpFile& operator=(const DumpFile&) = delete;
    DumpFile& operator=(DumpFile&&) = delete;

    void open(const char* file_name, Mode mode);
    void close();

    void ReadBytes(void* obj, size_t size) const {
        fread(obj, size, 1, _fp);
    }

    void ReadBytesArray(void* arr, size_t size, size_t count) const {
        fread(arr, size, count, _fp);
    }

    void ReadCString(char* str, size_t max_size) const {
        char ch;
        size_t size = 0;
        while (true) {
            read(ch);
            if (ch == '\0') break;
            str[size++] = ch;
            if (size > max_size) break;
        }
        str[size] = '\0';
    }

    template<std::integral T>
    void read(T& x) const {
        ReadBytes(&x, sizeof(T));
    }

    template<typename CharT>
    void read(std::basic_string<CharT>& x) const {
        typename std::basic_string<CharT>::size_type len;
        read(len);
        x.resize(len);
        ReadBytes(x.data(), len);
    }

    template<typename T>
    void read(std::vector<T>& x) const {
        typename std::vector<T>::size_type size;
        read(size);
        x.resize(size);
        for (auto&& obj : x) read(obj);
    }

    void WriteBytes(const void* obj, size_t size) const {
        fwrite(obj, size, 1, _fp);
    }

    void WriteBytesArray(const void* arr, size_t size, size_t count) const {
        fwrite(arr, size, count, _fp);
    }

    void WriteCString(const char* str, size_t max_size) const {
        size_t size = 0;
        while (*str != '\0') {
            write(*str);
            ++str, ++size;
            if (size + 1 >= max_size) break;
        }
        write('\0');
    }

    template<std::integral T>
    void write(const T& x) const {
        WriteBytes(&x, sizeof(T));
    }

    template<typename CharT>
    void write(const std::basic_string<CharT>& x) const {
        typename std::basic_string<CharT>::size_type len = x.size();
        write(len);
        WriteBytes(x.data(), len);
    }

    template<typename T>
    void write(const std::vector<T>& x) const {
        typename std::vector<T>::size_type size = x.size();
        write(size);
        for (auto&& obj : x) write(obj);
    }

    template<typename CharT>
    void write(std::basic_string_view<CharT> x) const {
        typename std::basic_string_view<CharT>::size_type len = x.size();
        write(len);
        WriteBytes(x.data(), len);
    }

    void write(const char* x) const { write(std::string_view(x)); }
};

class DumpRW {
public:
    virtual void write(const DumpFile& dump) const = 0;
    virtual void read(const DumpFile& dump) = 0;
};

#endif //_DUMPFILE_H_

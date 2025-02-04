/**
  * @file   JSON_Parser.h
  * @author 0And1Story
  * @date   2025-02-04
  * @brief  
  */

#ifndef _JSON_PARSER_H_
#define _JSON_PARSER_H_

#include <vector>
#include <string>
#include <map>
#include <variant>
#include <cstdint>
#include <cstddef>

#define is_delimiter(x) ((x) == ' ' || (x) == ',' || (x) == ':')

namespace JSON {

class Object {
public:
    enum class Type { Undefined, Array, Object, String };
    typedef ::std::vector<Object> ArrayType;
    typedef ::std::map<::std::string, Object> ObjectType;
    typedef ::std::string StringType;
    typedef ::std::uint64_t IntegerType;
    typedef ::std::nullptr_t UndefinedType;
    typedef ::std::variant<UndefinedType, ArrayType, ObjectType, StringType> ValueType;

public:
    Type type = Type::Undefined;
    ValueType value = nullptr;

    Object() noexcept = default;
    ~Object() noexcept = default;

    Object(const Object&) noexcept = default;
    Object(Object&&) noexcept = default;
    Object& operator=(const Object&) noexcept = default;
    Object& operator=(Object&&) noexcept = default;

    explicit Object(Type t) noexcept { SetType(t); }

    template<typename T>
    Object(Type t, T v) noexcept { type = t, value = v; }

    Object& operator=(const ArrayType& array) noexcept;
    Object& operator=(const ObjectType& object) noexcept;
    Object& operator=(const StringType& str) noexcept;
    Object& operator=(const IntegerType& integer) noexcept;
    Object& operator=(const std::vector<std::string>& vec) noexcept;
    Object& operator=(const std::map<std::string, std::string>& mp) noexcept;

    bool operator==(const Object& rhs) const noexcept;

    [[nodiscard]] std::string toString() const;

    void SetType(Type t);

    [[nodiscard]] ArrayType& AsArray();
    [[nodiscard]] ObjectType& AsObject();
    [[nodiscard]] StringType& AsString();
    [[nodiscard]] IntegerType AsInteger() const;
    [[nodiscard]] std::vector<std::string> AsStringVector() const;
    [[nodiscard]] std::map<std::string, std::string> AsStringMap() const;

    const Object& operator[](size_t index) const noexcept;
    Object& operator[](size_t index) noexcept;
    const Object& operator[](const std::string& key) const noexcept;
    Object& operator[](const std::string& key) noexcept;

    void append(const Object& object);
    void append(Object&& object);
    void insert(const std::string& k, const Object& v);
    void insert(const std::string& k, const Object&& v);
};

Object Parse(std::string_view source);
std::string Stringify(const Object& object);

static auto UNDEFINED = Object{};
#define UNDEFINED UNDEFINED

}

#endif //_JSON_PARSER_H_

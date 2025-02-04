/**
  * @file   JSON_Parser.cpp
  * @author 0And1Story
  * @date   2025-02-04
  * @brief  
  */

#include "JSON_Parser.h"

namespace JSON {

std::string Object::toString() const {
    std::string res;

    if (type == Type::Array) {
        auto& array = std::get<ArrayType>(value);
        res += "[";
        if (!array.empty()) {
            res += array.front().toString();
            for (auto it = std::next(array.begin()); it != array.end(); ++it) {
                res += ", ";
                res += it->toString();
            }
        }
        res += "]";
    } else if (type == Type::Object) {
        auto& object = std::get<ObjectType>(value);
        res += "{";
        if (!object.empty()) {
            res += "\"", res += object.begin()->first, res += "\": ", res += object.begin()->second.toString();
            for (auto it = std::next(object.begin()); it != object.end(); ++it) {
                auto&& [k, v] = *it;
                res += ", ";
                res += "\"", res += k, res += "\": ", res += v.toString();
            }
        }
        res += "}";
    } else if (type == Type::String) {
        res = "\"" + std::get<StringType>(value) + "\"";
    } else if (type == Type::Undefined) {
        res = "undefined";
    }

    return res;
}

Object::ArrayType& Object::AsArray() {
    return std::get<ArrayType>(value);
}

Object::ObjectType& Object::AsObject() {
    return std::get<ObjectType>(value);
}

Object::StringType& Object::AsString() {
    return std::get<StringType>(value);
}

Object::IntegerType Object::AsInteger() const {
    return std::stoll(std::get<StringType>(value));
}

std::vector<std::string> Object::AsStringVector() const {
    std::vector<std::string> res;
    auto& array = std::get<ArrayType>(value);
    res.reserve(array.size());
    for (auto&& x: array) res.push_back(x.toString());
    return res;
}

std::map<std::string, std::string> Object::AsStringMap() const {
    std::map<std::string, std::string> res;
    auto& object = std::get<ObjectType>(value);
    for (auto&& [k, v]: object) res.emplace(k, v.toString());
    return res;
}

void Object::SetType(Object::Type t) {
    type = t;
    if (type == Type::Array) value = ArrayType();
    else if (type == Type::Object) value = ObjectType();
    else if (type == Type::String) value = StringType();
    else if (type == Type::Undefined) value = nullptr;
}

Object& Object::operator=(const Object::ArrayType& array) noexcept {
    type = Type::Array;
    value = array;
    return *this;
}

Object& Object::operator=(const Object::ObjectType& object) noexcept {
    type = Type::Object;
    value = object;
    return *this;
}

Object& Object::operator=(const Object::StringType& str) noexcept {
    type = Type::String;
    value = str;
    return *this;
}

Object& Object::operator=(const Object::IntegerType& integer) noexcept {
    type = Type::String;
    value = std::to_string(integer);
    return *this;
}

Object& Object::operator=(const std::vector<std::string>& vec) noexcept {
    type = Type::Array;
    value = ArrayType();
    auto& array = std::get<ArrayType>(value);
    array.reserve(vec.size());
    for (auto&& x: vec) array.emplace_back(Type::String, x);
    return *this;
}

Object& Object::operator=(const std::map<std::string, std::string>& mp) noexcept {
    type = Type::Object;
    value = ObjectType();
    auto& object = std::get<ObjectType>(value);
    for (auto&& [k, v]: mp) object.emplace(k, Object(Type::String, v));
    return *this;
}

const Object& Object::operator[](size_t index) const noexcept {
    if (type != Type::Array) return UNDEFINED;
    auto& array = std::get<ArrayType>(value);
    if (index >= array.size()) return UNDEFINED;
    return array[index];
}

Object& Object::operator[](size_t index) noexcept {
    if (type != Type::Array) return UNDEFINED;
    auto& array = std::get<ArrayType>(value);
    if (index >= array.size()) return UNDEFINED;
    return array[index];
}

const Object& Object::operator[](const std::string& key) const noexcept {
    if (type != Type::Object) return UNDEFINED;
    auto& object = std::get<ObjectType>(value);
    if (!object.contains(key)) return UNDEFINED;
    return object.at(key);
}

Object& Object::operator[](const std::string& key) noexcept {
    if (type != Type::Object) return UNDEFINED;
    auto& object = std::get<ObjectType>(value);
    if (!object.contains(key)) return UNDEFINED;
    return object[key];
}

bool Object::operator==(const Object& rhs) const noexcept {
    if (type == Type::Undefined && rhs.type == Type::Undefined) return true;
    return this == std::addressof(rhs);
}

void Object::append(const Object& object) {
    if (type != Type::Array) return;
    auto& array = std::get<ArrayType>(value);
    array.emplace_back(object);
}

void Object::append(Object&& object) {
    if (type != Type::Array) return;
    auto& array = std::get<ArrayType>(value);
    array.emplace_back(object);
}

void Object::insert(const std::string& k, const Object& v) {
    if (type != Type::Object) return;
    auto& object = std::get<ObjectType>(value);
    object.emplace(k, v);
}

void Object::insert(const std::string& k, const Object&& v) {
    if (type != Type::Object) return;
    auto& object = std::get<ObjectType>(value);
    object.emplace(k, v);
}


Object Parse(std::string_view source) {
    std::vector<Object> res;
    for (std::string_view::const_iterator i = source.begin(); i != source.end(); ++i) {
        if (*i == ' ' || *i == ',' || *i == ':') continue;
        if (*i == '[') {
            res.emplace_back(Object::Type::Array);
            continue;
        }
        if (*i == '{') {
            res.emplace_back(Object::Type::Object);
            continue;
        }
        if (*i == ']' || *i == '}') {
            if (res.empty()) return UNDEFINED;
            if (res.size() == 1) return res.front();
            if (std::prev(res.end(), 2)->type == Object::Type::String) {
                std::prev(res.end(), 3)->insert(std::prev(res.end(), 2)->AsString(), std::move(res.back()));
                res.pop_back(), res.pop_back();
            } else if (std::prev(res.end(), 2)->type == Object::Type::Array) {
                std::prev(res.end(), 2)->append(std::move(res.back()));
                res.pop_back();
            } else if (std::prev(res.end(), 2)->type == Object::Type::Object) {
                if (res.back().type != Object::Type::String) return UNDEFINED;
            }
            continue;
        }
        Object str(Object::Type::String);
        std::string_view::const_iterator j;
        if (*i == '"' || *i == '\'') {
            for (j = i + 1; !(*j == *i && *(j - 1) != '\\') && j != source.end(); ++j);
            if (j == source.end()) return UNDEFINED;
            str = std::string(i + 1, j);
        } else {
            for (j = i + 1; !((is_delimiter(*j) || *j == ']' || *j == '}') && *(j - 1) != '\\') && j != source.end(); ++j);
            str = std::string(i, j);
            --j;
        }

        if (res.empty()) return std::move(str);
        if (res.back().type == Object::Type::String) {
            std::prev(res.end(), 2)->insert(res.back().AsString(), std::move(str));
            res.pop_back();
        } else if (res.back().type == Object::Type::Array) {
            res.back().append(std::move(str));
        } else if (res.back().type == Object::Type::Object) {
            res.push_back(std::move(str));
        }
        i = j;
    }
    return {};
}

std::string Stringify(const Object& object) {
    return object.toString();
}

}

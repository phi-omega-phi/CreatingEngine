/**
  * @file   XML_Parser.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "XML_Parser.h"

namespace DOM {

Node::Node(::std::string tag) : tagName(::std::move(tag)), attributes(), childNodes() {}

void Node::append(Node& child) {
    childNodes.push_back(::std::move(child));
}

void Node::append(Node&& child) {
    childNodes.push_back(child);
}

void Node::setAttribute(const ::std::string& key, const ::std::string& value) {
    attributes[key] = value;
}

::std::string Node::getAttribute(const ::std::string& key) {
    return attributes[key];
}

Node XMLParser(const ::std::string& origin) {
    NodeList nodes;
    bool is_tag = false;
    for (size_t i = 0; i < origin.size(); ++i) {
        if (origin[i] == '<') {
            if (origin[i + 1] == '/') {
                size_t j;
                for (j = i + 2; is_identifier(origin[j]); ++j);
                if (nodes.size() == 1) return nodes[0];
                nodes[nodes.size() - 2].append(nodes[nodes.size() - 1]);
                nodes.pop_back();
                i = j;
                continue;
            }
            is_tag = true;
            size_t j;
            for (j = i + 1; is_identifier(origin[j]); ++j);
            Node node(origin.substr(i + 1, j - i - 1));
            nodes.push_back(node);
            i = j - 1;
            continue;
        }
        if (origin[i] == '>') {
            is_tag = false;
            if (origin[i - 1] == '/') {
                nodes[nodes.size() - 2].append(nodes[nodes.size() - 1]);
                nodes.pop_back();
            }
            continue;
        }
        if (is_tag && is_identifier(origin[i])) {
            size_t j;
            for (j = i; is_identifier(origin[j]); ++j);
            if (origin[j] != '=' || origin[j + 1] != '"') {
                nodes[nodes.size() - 1].attributes[origin.substr(i, j - i)] = "";
                i = j;
                continue;
            }
            size_t k;
            for (k = j + 2; origin[k] != '"' || origin[k - 1] == '\\'; ++k);
            nodes[nodes.size() - 1].attributes[origin.substr(i, j - i)] = origin.substr(j + 2, k - j - 2);
            i = k - 1;
            continue;
        }
    }
    return {};
}

Node XMLParserFromFile(const char *file_path) {
    struct _stat64 stat_{};
    stat64(file_path, &stat_);
    char *buffer = (char *) malloc(stat_.st_size);
//    buffer[stat_.st_size] = '\0';
    FILE *fp = fopen(file_path, "rb");
    fread(buffer, 1, stat_.st_size, fp);
    ::std::string origin(buffer, buffer + stat_.st_size);
    free(buffer);
    return XMLParser(origin);
}

}

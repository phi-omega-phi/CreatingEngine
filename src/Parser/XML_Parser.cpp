/**
  * @file   XML_Parser.cpp
  * @author 0And1Story
  * @date   2023-09-23
  * @brief  
  */
#include "XML_Parser.h"

namespace DOM {

Node::Node(::std::string& tag): tagName(::std::move(tag)), attributes(), childNodes() {}
Node::Node(::std::string&& tag): tagName(tag), attributes(), childNodes() {}

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

Node XMLParser(::std::string_view origin) {
    NodeList nodes;
    bool is_tag = false;
    for (::std::string_view::const_iterator i = origin.begin(), i_end = origin.end(); i != i_end; ++i) {
        if (*i == '<') {
            if (*(i + 1) == '/') {
                ::std::string_view::const_iterator j;
                for (j = i + 2; is_identifier(*j); ++j);
                if (nodes.size() == 1) return nodes[0];
                (nodes.end() - 2)->append(*(nodes.end() - 1));
                nodes.pop_back();
                i = j;
                continue;
            }
            is_tag = true;
            ::std::string_view::const_iterator j;
            for (j = i + 1; is_identifier(*j); ++j);
            Node node(::std::string(i + 1, j));
            nodes.push_back(node);
            i = j - 1;
            continue;
        }
        if (*i == '>') {
            is_tag = false;
            if (*(i - 1) == '/') {
                (nodes.end() - 2)->append(*(nodes.end() - 1));
                nodes.pop_back();
            }
            continue;
        }
        if (is_tag && is_identifier(*i)) {
            ::std::string_view::const_iterator j;
            for (j = i; is_identifier(*j); ++j);
            if (*j != '=' || *(j + 1) != '"') {
                (nodes.end() - 1)->attributes[::std::string(i, j)] = "";
                i = j;
                continue;
            }
            ::std::string_view::const_iterator k;
            for (k = j + 2; *k != '"' || *(k - 1) == '\\'; ++k);
            (nodes.end() - 1)->attributes[::std::string(i, j)] = ::std::string(j + 2, k);
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
    fclose(fp);
    ::std::string origin(buffer, buffer + stat_.st_size);
    free(buffer);
    return XMLParser(origin);
}

}

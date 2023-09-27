/**
  * @file   XML_Parser.h
  * @author 0And1Story
  * @date   2023-09-17
  * @brief  
  */

#ifndef _XML_PARSER_H_
#define _XML_PARSER_H_

#include <string>
#include <vector>
#include <map>
#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>

#define is_identifier(x) (isalpha(x) || (x) == '_' || (x) == '-')

namespace DOM {

class Node {
public:
    typedef ::std::vector<Node> NodeList;
    typedef ::std::map<::std::string, ::std::string> NamedNodeMap;

    ::std::string tagName;
    NamedNodeMap attributes;
    NodeList childNodes;

    Node() = default;

    ~Node() = default;

    explicit Node(::std::string tag);

    void append(Node& child);
    void append(Node&& child);

    void setAttribute(const ::std::string& key, const ::std::string& value);
    ::std::string getAttribute(const ::std::string& key);
};

typedef Node::NodeList NodeList;
typedef Node::NamedNodeMap NamedNodeMap;

Node XMLParser(const ::std::string& origin);

Node XMLParserFromFile(const char* file_path);

}

#endif //_XML_PARSER_H_

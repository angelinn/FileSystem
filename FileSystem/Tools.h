#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <utility>

typedef std::pair<std::string, std::string> stringPair;

stringPair splitPath(const std::string &);
std::string getSecondPart(const std::string &);
const char BACKSLASH_CHAR = '/';
const int BYTE_SIZE = 4;



#endif // TOOLS_H

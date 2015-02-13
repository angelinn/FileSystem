#ifndef TOOLS_H
#define TOOLS_H


#include <string>
#include <utility>
#include "TNode.h"
// --------------------------------------------------------------------------------------------------------------

typedef std::pair<std::string, std::string> stringPair;
typedef DLList<TNode*>::Iterator ListIterator;

// --------------------------------------------------------------------------------------------------------------

stringPair splitPath(const std::string &);
std::string getSecondPart(const std::string &);
std::string buildPath(const std::string &, const std::string &);

template <typename T>
void allocate(T *&, size_t);

// --------------------------------------------------------------------------------------------------------------

const char BACKSLASH_CHAR = '/';
const char* const BACKSLASH_STR = "/";
const int BYTE_SIZE = 4;
const int KILO_BYTE = 1024;
const int MEGA_BYTE = 1024 * KILO_BYTE;
const int BUFFER_SIZE = 64 * KILO_BYTE;
const unsigned char NULL_BYTE = 0x00;

// --------------------------------------------------------------------------------------------------------------

template void allocate<unsigned char>(unsigned char *&, size_t);

#endif // TOOLS_H

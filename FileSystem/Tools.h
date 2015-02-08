#ifndef TOOLS_H
#define TOOLS_H


#include <string>
#include <utility>

// --------------------------------------------------------------------------------------------------------------

typedef std::pair<std::string, std::string> stringPair;

// --------------------------------------------------------------------------------------------------------------

stringPair splitPath(const std::string &);
std::string getSecondPart(const std::string &);

template <typename T>
void allocate(T *&, size_t);


// --------------------------------------------------------------------------------------------------------------

const char BACKSLASH_CHAR = '/';
const int BYTE_SIZE = 4;
const int KILO_BYTE = 1024;
const int MEGA_BYTE = 1024 * KILO_BYTE;
const int BUFFER_SIZE = 64 * KILO_BYTE;

// --------------------------------------------------------------------------------------------------------------

template void allocate<unsigned char>(unsigned char *&, size_t);

#endif // TOOLS_H

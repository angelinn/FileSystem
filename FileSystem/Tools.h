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
// CLI Constants

const char RESPONSE_NEW = 'n';
const char SOUND_CHAR = '\a';
const char* const PROMPT = "> ";
const char* const LOADING_MESSAGE = "loading ..";
const char* const HELP_MESSAGE = "\nHello!\nYou can use the following commands:\n"
				"mkdir <path>\nimport-file <from> <to>\nimport-dir <from> <to>\nexport-dir <from> <to>\nexport-file <from> <to>\n"
				"move <from> <to>\ndir <path>\ndelete-file <path>\ndelete-dir<path>copy-file <from> <to>\ncopy-dir <from> <to>\n"
				"rename <path> <name>\nappend <path> <text>\nexit\nhelp";

const char* const FILE_NAME_REQUEST = "\nType in the name of the File\n> ";
const char* const PROMPT_ON_CREATE = "If you want to create a new file system, type 'n'!\n"
									 "Else if you want to create an existing one type 'e'!\n";

// --------------------------------------------------------------------------------------------------------------

template void allocate<unsigned char>(unsigned char *&, size_t);

#endif // TOOLS_H

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

//#include "FileSystem.h"

#include <utility>
#include <string>
#include "DLList.h"

class FileSystem;

class CommandParser
{
	typedef void(FileSystem::*FileAction)();
	typedef std::pair<std::string, FileAction> cmdPair;

public:
	void registerCommand(const std::string &, FileAction);
	void parse(const std::string);

private:
	FileSystem* fs;
	void fill();
	DLList<cmdPair> list;
};


#endif // COMMAND_PARSER_H

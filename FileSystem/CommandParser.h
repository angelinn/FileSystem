#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H


#include <utility>
#include <string>
#include "DLList.h"

class CLI;

typedef void(CLI::*FileAction)(DLList<std::string> &);

class CommandParser
{
	typedef std::pair<std::string, FileAction> cmdPair;

public:
	void registerCommand(const std::string &, FileAction);
	FileAction getMethod(const std::string &);

private:
	DLList<cmdPair> list;
};


#endif // COMMAND_PARSER_H
